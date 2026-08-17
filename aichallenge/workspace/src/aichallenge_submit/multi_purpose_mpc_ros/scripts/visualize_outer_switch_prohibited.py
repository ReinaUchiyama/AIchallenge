#!/usr/bin/env python3
"""
L0↔L2 切り替え禁止区間の可視化スクリプト

禁止要因:
  1. outer_switch_prohibited_zones: config.yaml で直接指定されたWP区間
  2. 曲率ペナルティ: center軌道の|kappa| >= outer_lane_curve_penalty_high (0.08/m) の区間
     -> コーナー外側になる場合にアウターレーン選択を実質禁止
  3. 壁面余裕不足: outer_lane_wall_clearance_reject_m (0.7m) を下回る区間
"""

import math
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.collections import LineCollection
from matplotlib.ticker import MultipleLocator

# ─── パス設定 ───────────────────────────────────────────────────────────────
BASE = os.path.dirname(os.path.abspath(__file__))
PKG = os.path.join(BASE, "..")

CENTER_TRAJ = os.path.join(PKG, "env/centerline/traj_center_mincurv_capped.csv")
CENTER_BOUNDS = os.path.join(PKG, "env/centerline/waypoint_bounds_center_mincurv_capped.csv")

# ─── Config値 ────────────────────────────────────────────────────────────────
# config.yaml の outer_switch_prohibited_zones
PROHIBITED_ZONES = [
    (130, 150),
    (245, 275),
]

# 曲率閾値 (outer_lane_curve_penalty_high)
KAPPA_REJECT = 0.19   # [1/m] これ以上の|kappa|を持つ区間はアウターペナルティ最大 → 実質禁止
KAPPA_WARN   = 0.15   # [1/m] ペナルティ開始

# 壁面余裕拒否閾値 (outer_lane_wall_clearance_reject_m)
WALL_REJECT_M = 0.7   # [m]

# MPC本体はN=25のまま。曲率による外側車線スコアだけ短い先読みを使う。
# waypoint間隔0.6mなら10点で約6m。
MPC_N = 25
CURVE_SCORE_LOOKAHEAD_WPS = 10

# 5点刻みでラベルを付ける
LABEL_STEP = 5

# ─── データ読み込み ──────────────────────────────────────────────────────────
traj = pd.read_csv(CENTER_TRAJ)
bounds = pd.read_csv(CENTER_BOUNDS)

# センタートラジェクトリは逆順(降順)で並んでいることがある → sort
# waypointインデックスはboundsのidxに対応
n_wp = len(bounds)
print(f"Waypoints: {n_wp}")
print(f"Traj rows: {len(traj)}")

# traj は周回方向逆順(s_m降順)のため、wp_id=0 が末尾付近
# boundsのidx順でwaypointを使う
# boundsのub/lbはCenter軌道の横幅 (center軌道上の符号付き距離)
# traj の x_m,y_m,kappa_radpm をboundsのidxに対応付ける
# トラジェクトリは一周するので、boundsとほぼ同じ本数のはず
assert len(traj) == n_wp or abs(len(traj) - n_wp) <= 1, \
    f"Traj({len(traj)}) vs bounds({n_wp}) length mismatch!"

# boundsのidxでアクセスするため、traj側は逆順でリセット
# trajはs_m降順 → idx=0がs_m最大 → bounds idx=0 と対応させる
traj_arr = traj.values  # rows in s_m descending order

xs = traj_arr[:n_wp, 1]        # x_m
ys = traj_arr[:n_wp, 2]        # y_m
kappas = traj_arr[:n_wp, 4]    # kappa_radpm (signed)
psis = traj_arr[:n_wp, 3]      # psi_rad

ubs = bounds["ub"].values[:n_wp]   # 左境界 (正値)
lbs = bounds["lb"].values[:n_wp]   # 右境界 (負値)

# bounds内の各車線の左右幅 (lane_boundsに相当する簡易近似)
# ub~(ub+lb)/3 を L2中心、(ub+lb)/3~0 をL1、0~(ub+lb)*2/3 をL0と仮定
# 実際にはget_lane_boundsが3分割するがここでは近似で算出
# ub = left wall, lb = right wall
# lane_bounds: L0(内側=lb側), L1(中央), L2(外側=ub側) → config依存
# Center軌道の場合 ub > 0 (左), lb < 0 (右)
# L0(最内) = right side → center ≈ lb*2/3
# L1(中央) = 0付近     → center ≈ 0
# L2(最外) = left side  → center ≈ ub*2/3
lane_width_total = ubs - lbs  # 全幅 [m]
# 各レーン中心(center軌道からの横方向オフセット)
L0_center = lbs * (2.0 / 3.0)   # 右寄り (負)
L2_center = ubs * (2.0 / 3.0)   # 左寄り (正)

# 壁面余裕: L0はlb側の壁まで(lane_center - lb = lb*2/3 - lb = -lb/3)
wall_clear_L0 = -lbs / 3.0
wall_clear_L2 = ubs / 3.0

# ─── 禁止区間の計算 ──────────────────────────────────────────────────────────
def kappa_in_horizon(
    wp_id, n_wp, kappas, N=CURVE_SCORE_LOOKAHEAD_WPS
):
    """wp_id前方N+1点の最大|kappa|を計算 (circular)"""
    return max(abs(kappas[(wp_id + k) % n_wp]) for k in range(N + 1))

# 各waypointで禁止フラグを計算
prohibited_config   = np.zeros(n_wp, dtype=bool)  # config指定ゾーン
prohibited_kappa_hi = np.zeros(n_wp, dtype=bool)  # kappa >= KAPPA_REJECT
prohibited_kappa_lo = np.zeros(n_wp, dtype=bool)  # kappa >= KAPPA_WARN
prohibited_wall_L0  = np.zeros(n_wp, dtype=bool)  # L0 壁面余裕不足
prohibited_wall_L2  = np.zeros(n_wp, dtype=bool)  # L2 壁面余裕不足

for z_start, z_end in PROHIBITED_ZONES:
    for idx in range(z_start, z_end + 1):
        if 0 <= idx < n_wp:
            prohibited_config[idx] = True

for idx in range(n_wp):
    # kappa check: コーナー外側かどうかもチェックするのが本来だが、
    # 可視化目的なので |kappa| だけで判定
    max_kappa = kappa_in_horizon(idx, n_wp, kappas)
    if max_kappa >= KAPPA_REJECT:
        prohibited_kappa_hi[idx] = True
    elif max_kappa >= KAPPA_WARN:
        prohibited_kappa_lo[idx] = True

    # 壁面余裕チェック
    if wall_clear_L0[idx] < WALL_REJECT_M:
        prohibited_wall_L0[idx] = True
    if wall_clear_L2[idx] < WALL_REJECT_M:
        prohibited_wall_L2[idx] = True

# ─── プロット ─────────────────────────────────────────────────────────────────
fig, (ax_map, ax_kappa) = plt.subplots(
    2, 1, figsize=(14, 14),
    gridspec_kw={"height_ratios": [3, 1]},
)
fig.suptitle("L0↔L2 切り替え禁止区間の可視化\n(Center Waypoint基準)", fontsize=13, fontweight="bold")

# ── 上段: 2D マップ ───────────────────────────────────────────────────────────
# 軌道ライン (グレー)
ax_map.plot(xs, ys, color="#aaaaaa", lw=1.2, zorder=1, label="Center軌道")

# 壁面ライン
normal_angles = psis + math.pi / 2.0
left_xs  = xs + ubs * np.cos(normal_angles)
left_ys  = ys + ubs * np.sin(normal_angles)
right_xs = xs + lbs * np.cos(normal_angles)
right_ys = ys + lbs * np.sin(normal_angles)
ax_map.plot(left_xs,  left_ys,  color="#444444", lw=0.8, zorder=1, label="コース境界")
ax_map.plot(right_xs, right_ys, color="#444444", lw=0.8, zorder=1)

# config禁止ゾーン (赤の太い帯)
def draw_zone_band(ax, idxs, color, alpha=0.35, zorder=5):
    if len(idxs) == 0:
        return
    # 各wpで左右の点から多角形を描く
    for i in idxs:
        ni = psis[i] + math.pi / 2.0
        lx = xs[i] + ubs[i] * math.cos(ni)
        ly = ys[i] + ubs[i] * math.sin(ni)
        rx = xs[i] + lbs[i] * math.cos(ni)
        ry = ys[i] + lbs[i] * math.sin(ni)
        ax.plot([rx, lx], [ry, ly], color=color, alpha=alpha, lw=3.5, zorder=zorder)

config_idxs   = np.where(prohibited_config)[0]
kappa_hi_idxs = np.where(prohibited_kappa_hi & ~prohibited_config)[0]
kappa_lo_idxs = np.where(prohibited_kappa_lo & ~prohibited_config & ~prohibited_kappa_hi)[0]

draw_zone_band(ax_map, config_idxs,   color="red",    alpha=0.55, zorder=6)
draw_zone_band(ax_map, kappa_hi_idxs, color="orange", alpha=0.50, zorder=5)
draw_zone_band(ax_map, kappa_lo_idxs, color="yellow", alpha=0.40, zorder=4)

# Waypoint番号ラベル (5点刻み)
for idx in range(0, n_wp, LABEL_STEP):
    ax_map.annotate(
        str(idx),
        xy=(xs[idx], ys[idx]),
        fontsize=5.5,
        color="#333333",
        ha="center", va="center",
        zorder=10,
        bbox=dict(boxstyle="round,pad=0.1", fc="white", ec="none", alpha=0.7),
    )

# 禁止区間の始終点ラベル
def label_zone_boundary(ax, zone_idxs, color):
    if len(zone_idxs) == 0:
        return
    # 連続ブロックを検出
    breaks = np.where(np.diff(zone_idxs) > 1)[0]
    starts = [zone_idxs[0]] + list(zone_idxs[breaks + 1])
    ends   = list(zone_idxs[breaks]) + [zone_idxs[-1]]
    for s, e in zip(starts, ends):
        for i, label in ((s, f"WP{s}→"), (e, f"←WP{e}")):
            ax_map.annotate(
                label,
                xy=(xs[i], ys[i]),
                fontsize=7.5, fontweight="bold",
                color=color,
                ha="center", va="bottom",
                zorder=12,
                bbox=dict(boxstyle="round,pad=0.2", fc="white", ec=color, alpha=0.85),
            )

label_zone_boundary(ax_map, config_idxs,   "red")
label_zone_boundary(ax_map, kappa_hi_idxs, "darkorange")

ax_map.set_aspect("equal")
ax_map.set_xlabel("X [m]")
ax_map.set_ylabel("Y [m]")
ax_map.legend(
    handles=[
        mpatches.Patch(color="red",        label="prohibited_zones"),
        mpatches.Patch(color="orange",     label=f" |κ|≥{KAPPA_REJECT}/m (penalty_high)"),
        mpatches.Patch(color="yellow",     label=f"|κ|≥{KAPPA_WARN}/m (penalty_start)"),
        mpatches.Patch(color="#aaaaaa",    label="normal"),
    ],
    loc="upper right", fontsize=8,
)
ax_map.grid(True, alpha=0.2)

# ── 下段: 曲率グラフ ─────────────────────────────────────────────────────────
wp_ids = np.arange(n_wp)
ax_kappa.fill_between(wp_ids,  np.abs(kappas), 0, alpha=0.25, color="steelblue", label="|κ| (絶対値)")
ax_kappa.plot(wp_ids, np.abs(kappas), color="steelblue", lw=1.0)
ax_kappa.axhline(KAPPA_REJECT, color="red",    ls="--", lw=1.2, label=f"禁止閾値 {KAPPA_REJECT}/m")
ax_kappa.axhline(KAPPA_WARN,   color="orange", ls="--", lw=1.2, label=f"注意閾値 {KAPPA_WARN}/m")

# 禁止ゾーンのシェード
for z_start, z_end in PROHIBITED_ZONES:
    ax_kappa.axvspan(z_start, z_end, alpha=0.18, color="red", label=f"config禁止 WP{z_start}~{z_end}")

ax_kappa.set_xlabel("Waypoint ID")
ax_kappa.set_ylabel("|κ| [1/m]")
ax_kappa.set_title("曲率プロファイルと禁止閾値")
ax_kappa.legend(fontsize=8, loc="upper right")
ax_kappa.xaxis.set_major_locator(MultipleLocator(10))
ax_kappa.xaxis.set_minor_locator(MultipleLocator(5))
ax_kappa.grid(True, which="major", alpha=0.3)
ax_kappa.grid(True, which="minor", alpha=0.12)
ax_kappa.set_xlim(0, n_wp - 1)
ax_kappa.set_ylim(bottom=0)

plt.tight_layout()
out_path = os.path.join(BASE, "outer_switch_prohibited_zones.png")
plt.savefig(out_path, dpi=150)
print(f"\nSaved: {out_path}")

# ─── テキスト出力 ─────────────────────────────────────────────────────────────
print("\n=== L0↔L2 切り替え禁止区間一覧 ===")
print("\n[1] config.yaml直接指定 (outer_switch_prohibited_zones)")
for z_s, z_e in PROHIBITED_ZONES:
    print(f"  WP {z_s:3d} 〜 {z_e:3d}  ({z_e - z_s + 1}点)")

print(
    f"\n[2] 曲率禁止 |κ| ≥ {KAPPA_REJECT}/m "
    f"(score lookahead={CURVE_SCORE_LOOKAHEAD_WPS} WPs; MPC N={MPC_N})"
)
def print_zones(mask, label):
    idxs = np.where(mask)[0]
    if len(idxs) == 0:
        print(f"  {label}: なし")
        return
    breaks = np.where(np.diff(idxs) > 1)[0]
    starts = [idxs[0]] + list(idxs[breaks + 1])
    ends   = list(idxs[breaks]) + [idxs[-1]]
    for s, e in zip(starts, ends):
        print(f"  WP {s:3d} 〜 {e:3d}  ({e - s + 1}点)  max|κ|={max(abs(kappas[s:e+1])):.4f}")

print_zones(prohibited_kappa_hi, "高曲率禁止")

print(f"\n[3] 曲率注意 |κ| ≥ {KAPPA_WARN}/m (outer_lane_curve_penalty_start, 禁止ではなくペナルティ)")
print_zones(prohibited_kappa_lo & ~prohibited_kappa_hi, "中曲率ペナルティ")

print(f"\n[4] 壁面余裕不足 < {WALL_REJECT_M}m (outer_lane_wall_clearance_reject_m)")
print("  L0 (右壁):")
print_zones(prohibited_wall_L0, "L0壁面不足")
print("  L2 (左壁):")
print_zones(prohibited_wall_L2, "L2壁面不足")

plt.show()

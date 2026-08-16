"""center_converted.csv (実測 w_tr_right/left) から、mincurv_iqp 入力用の
center_converted_capped.csv を作る。ただし特定区間だけ CAP を引き上げ、
前後はコサインカーブでランプさせて滑らかに繋ぐ。

背景:
  従来の center_converted_capped.csv は全周一律 CAP=1.3m でクリップされている。
  waypoint idx513-629 (env/centerline/traj_center_mincurv_capped.csv の idx245-265,
  s_m≈92-112m) 付近は実測コース幅が片側3.0-5.4mあるのに 1.3m に制限されていたため、
  mincurv_iqp がこの余裕を使えず、不要にきついS字(切り返し)を生成していた。
  この区間だけ CAP を引き上げて、オプティマイザにセンターラインを
  素直な(低曲率な)形へ均してもらう。

使い方:
  python3 make_capped_center_local_ramp.py
  出力: center_converted_capped_local_ramp.csv
  (既存の center_converted_capped.csv は上書きしない。
   問題なければ手動でリネーム/差し替えてから mincurv_iqp を実行してください)
"""
import os
import numpy as np
import pandas as pd

TRACKS_DIR = "/home/takenoyama/Documents/AI_challenge/global_racetrajectory_optimization/inputs/tracks"
IN_CSV = os.path.join(TRACKS_DIR, "center_converted.csv")
OUT_CSV = os.path.join(TRACKS_DIR, "center_converted_capped_local_ramp.csv")

# 全周デフォルトのCAP (従来通り)
BASE_CAP = 1.3

# CAPを引き上げる区間 (center_converted.csv の行インデックス, 0-origin, 閉区間)
# env/centerline/traj_center_mincurv_capped.csv の idx245-265 (S字本体) に対応する
# center_converted.csv 側の範囲が 513-629 だったため、それを核として指定。
CORE_LO = 513
CORE_HI = 629

# 核の前後に設けるランプ(遷移)区間の長さ [点数]。ここでBASE_CAPから
# TARGET_CAPまでコサインカーブで滑らかに立ち上げ/立ち下げる。
RAMP_POINTS = 30

# 核区間で目指すCAP。実測最小幅(右3.02m/左3.33m)を下回る安全マージンを取る。
TARGET_CAP = 2.5

# 安全マージン: 実測幅ぎりぎりまでは使わせない (壁からのクリアランス確保)
SAFETY_MARGIN = 0.3


def ramp_weight(i: int, n: int) -> float:
    """行インデックス i (0-origin, 周回mod n) における昇圧の重み [0,1] を返す。
    CORE区間内は1.0、その前後RAMP_POINTS区間はコサインで0→1→0に遷移、
    それ以外は0 (=BASE_CAPのまま)。周回(先頭/末尾接続)を考慮する。
    """
    def circ_dist(a, b):
        d = abs(a - b) % n
        return min(d, n - d)

    if CORE_LO <= i <= CORE_HI:
        return 1.0

    if i < CORE_LO:
        d = CORE_LO - i
    else:
        d = i - CORE_HI

    # 周回をまたぐ側からの距離も考慮 (核区間がファイル境界付近にある場合の保険)
    d = min(d, circ_dist(i, CORE_LO), circ_dist(i, CORE_HI))

    if d > RAMP_POINTS:
        return 0.0
    # d=0(核の端) -> weight=1, d=RAMP_POINTS(遷移終端) -> weight=0
    return 0.5 * (1.0 + np.cos(np.pi * d / RAMP_POINTS))


def main():
    tc = pd.read_csv(IN_CSV, comment='#', header=None,
                      names=['x_m', 'y_m', 'w_tr_right_m', 'w_tr_left_m'])
    n = len(tc)

    weights = np.array([ramp_weight(i, n) for i in range(n)])
    ramped_cap = BASE_CAP + weights * (TARGET_CAP - BASE_CAP)

    real_right = tc['w_tr_right_m'].to_numpy()
    real_left = tc['w_tr_left_m'].to_numpy()

    out_right = np.minimum(ramped_cap, real_right - SAFETY_MARGIN)
    out_left = np.minimum(ramped_cap, real_left - SAFETY_MARGIN)
    # 実測幅がSAFETY_MARGIN未満で負になるケースの保険 (通常は発生しない想定)
    out_right = np.maximum(out_right, 0.3)
    out_left = np.maximum(out_left, 0.3)
    # 核・ランプ区間外は従来通りBASE_CAP (実測がBASE_CAP未満ならそちらを優先)
    out_right = np.where(weights > 0, out_right, np.minimum(BASE_CAP, real_right))
    out_left = np.where(weights > 0, out_left, np.minimum(BASE_CAP, real_left))

    out = pd.DataFrame({
        'x_m': tc['x_m'],
        'y_m': tc['y_m'],
        'w_tr_right_m': out_right,
        'w_tr_left_m': out_left,
    })

    header = "# x_m,y_m,w_tr_right_m,w_tr_left_m"
    with open(OUT_CSV, 'w') as f:
        f.write(header + "\n")
        out.to_csv(f, index=False, header=False)

    changed = weights > 0
    print(f"[done] {OUT_CSV} ({n} 行)")
    print(f"CAP引き上げ対象: {changed.sum()} 点 "
          f"(核 idx{CORE_LO}-{CORE_HI}, ランプ±{RAMP_POINTS}点)")
    print(f"核区間でのCAP最大値: right={out_right[CORE_LO:CORE_HI+1].max():.3f}m "
          f"left={out_left[CORE_LO:CORE_HI+1].max():.3f}m (目標TARGET_CAP={TARGET_CAP}m)")
    print(f"核区間の遷移端(idx{CORE_LO},{CORE_HI})でのCAP: "
          f"right={out_right[CORE_LO]:.3f}/{out_right[CORE_HI]:.3f}m")


if __name__ == "__main__":
    main()

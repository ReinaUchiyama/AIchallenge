#!/usr/bin/env python3
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as colors

def main():
    base_dir = "/home/takenoyama/aichallenge-racingkart/aichallenge/workspace/src/aichallenge_submit/multi_purpose_mpc_ros/env/centerline"
    bounds_csv = os.path.join(base_dir, "waypoint_bounds_center_mincurv_capped.csv")
    traj_csv = os.path.join(base_dir, "traj_center_mincurv_capped.csv")
    
    if not os.path.exists(bounds_csv) or not os.path.exists(traj_csv):
        print("Error: CSV files not found.")
        return

    df_bounds = pd.read_csv(bounds_csv)
    df_traj = pd.read_csv(traj_csv)

    # Calculate absolute curvature
    df_traj['abs_kappa'] = df_traj['kappa_radpm'].abs()
    
    # Thresholds for visual analysis
    thresh_mid = 0.04
    thresh_high = 0.10

    # Determine fallback lookahead wps based on thresholds
    # Straight/Mild (<0.04) -> 3 wp
    # Mid (0.04 ~ 0.10) -> 5 wp
    # High (>0.10) -> 7 wp
    lookahead_list = []
    color_list = []
    for k in df_traj['abs_kappa']:
        if k > thresh_high:
            lookahead_list.append(7)
            color_list.append('red') # High Curvature
        elif k > thresh_mid:
            lookahead_list.append(5)
            color_list.append('orange') # Mid Curvature
        else:
            lookahead_list.append(3)
            color_list.append('blue') # Straight / Mild

    df_traj['lookahead_wps'] = lookahead_list
    df_traj['color'] = color_list

    # Setup matplotlib figure
    plt.figure(figsize=(16, 12))

    # 1. 2D Track Curvature Map (Subplot 1)
    ax1 = plt.subplot(2, 1, 1)
    # Draw walls
    ax1.plot(df_bounds['left_x'], df_bounds['left_y'], 'k-', alpha=0.3, label='Left Wall')
    ax1.plot(df_bounds['right_x'], df_bounds['right_y'], 'k-', alpha=0.3, label='Right Wall')
    
    # Scatter plot of waypoints colored by curvature
    sc = ax1.scatter(df_traj['x_m'], df_traj['y_m'], c=df_traj['abs_kappa'], 
                     cmap='YlOrRd', norm=colors.LogNorm(vmin=0.005, vmax=0.25), s=35, edgecolor='none', zorder=3,
                     label='Centerline Waypoints')
    cbar = plt.colorbar(sc, ax=ax1, orientation='vertical', pad=0.01)
    cbar.set_label('Absolute Curvature |kappa| [rad/m]', fontsize=10)
    
    # Annotate critical zones
    # WP 35-60 (S-Curve & Bottleneck)
    wp53 = df_traj.iloc[53]
    ax1.annotate("S-Curve Bottleneck\n(WP35-60)\n|kappa| ~ 0.20", 
                 xy=(wp53['x_m'], wp53['y_m']), xytext=(wp53['x_m'] - 10, wp53['y_m'] - 8),
                 arrowprops=dict(facecolor='darkred', shrink=0.08, width=1, headwidth=5), fontsize=9, fontweight='bold')
                 
    # WP 86-100 (Lap 5 Stall & Contact Zone)
    wp90 = df_traj.iloc[90]
    ax1.annotate("Lap 5 Stall Zone\n(WP89-90)\n|kappa| ~ 0.14", 
                 xy=(wp90['x_m'], wp90['y_m']), xytext=(wp90['x_m'] + 8, wp90['y_m'] - 6),
                 arrowprops=dict(facecolor='red', shrink=0.08, width=1, headwidth=5), fontsize=9, fontweight='bold')

    # WP 143-165 (Hairpin turn)
    wp154 = df_traj.iloc[154]
    ax1.annotate("Hairpin Corner\n(WP143-165)\n|kappa| ~ 0.23", 
                 xy=(wp154['x_m'], wp154['y_m']), xytext=(wp154['x_m'] - 12, wp154['y_m'] + 10),
                 arrowprops=dict(facecolor='darkred', shrink=0.08, width=1, headwidth=5), fontsize=9, fontweight='bold')

    ax1.set_title("Track Curvature Distribution & Critical Zones Map", fontsize=14, fontweight='bold')
    ax1.set_xlabel("X [m]")
    ax1.set_ylabel("Y [m]")
    ax1.set_aspect('equal', 'datalim')
    ax1.grid(True, linestyle=':', alpha=0.5)

    # 2. Curvature Profile & Lookahead Window Allocation (Subplot 2)
    ax2 = plt.subplot(2, 1, 2)
    ax2.plot(df_traj.index, df_traj['abs_kappa'], 'k-', linewidth=1.5, label='Curvature Magnitude |kappa|')
    
    # Highlight zones with background shading
    ax2.axhspan(0, thresh_mid, color='blue', alpha=0.08, label='Straight / Mild Zone (Lookahead: 3 wp)')
    ax2.axhspan(thresh_mid, thresh_high, color='orange', alpha=0.08, label='Mid-Curvature Zone (Lookahead: 5 wp)')
    ax2.axhspan(thresh_high, df_traj['abs_kappa'].max() + 0.05, color='red', alpha=0.08, label='High-Curvature Zone (Lookahead: 7 wp)')
    
    # Draw threshold lines
    ax2.axhline(y=thresh_mid, color='blue', linestyle='--', alpha=0.5)
    ax2.axhline(y=thresh_high, color='red', linestyle='--', alpha=0.5)

    # Draw lookup line
    ax2_twin = ax2.twinx()
    ax2_twin.step(df_traj.index, df_traj['lookahead_wps'], where='mid', color='purple', linewidth=2.0, alpha=0.7,
                  label='Assigned Lookahead [waypoints]')
    ax2_twin.set_ylabel('Lookahead WP Window Size', color='purple', fontsize=11, fontweight='bold')
    ax2_twin.tick_params(axis='y', labelcolor='purple')
    ax2_twin.set_ylim(2, 9)

    ax2.set_title("Curvature Profile by Waypoint and Assigned Fallback Lookahead Window Size", fontsize=12, fontweight='bold')
    ax2.set_xlabel("Waypoint Index")
    ax2.set_ylabel("Curvature |kappa| [rad/m]")
    ax2.set_xlim(0, len(df_traj) - 1)
    ax2.set_ylim(0, df_traj['abs_kappa'].max() + 0.02)
    
    # Put both legends together
    lines1, labels1 = ax2.get_legend_handles_labels()
    lines2, labels2 = ax2_twin.get_legend_handles_labels()
    ax2.legend(lines1 + lines2, labels1 + labels2, loc='upper right', fontsize=9)
    ax2.grid(True, linestyle=':', alpha=0.5)

    plt.tight_layout()
    output_path = "/home/takenoyama/.gemini/antigravity/artifacts/track_curvature_analysis.png"
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    plt.savefig(output_path, dpi=200)
    print(f"Curvature visualization saved to {output_path}")

if __name__ == "__main__":
    main()

"""
linkage_optimize_v6_pureHardConstraints.py
在 v5_hardRange 基礎上修改：
  1. 把「角度中點變動範圍 avgRange (=max(avgList)-min(avgList))」也
     改成【可調硬性範圍】：avgRange 必須 <= avgRange_max (硬性上限，
     下限本來就是0，故只需設上限)。
  2. 拿掉之前所有「懲罰/獎勵」評分機制：
       - w_inv (中點變動範圍的平方懲罰)
       - w_size (尺寸越小獎勵)
       - w_close (擺角逼近上限的獎勵)
       - 以及原本用 1e7*(超出量+1) 手刻的漸進式罰分
     全部移除。現在死點餘裕、角度中點變動範圍、swing(b_min)、
     swing(b_max) 四項，全部改用 非線性不等式限制式 (c(x) <= 0)
     來硬性要求，不再有任何「越接近越好」的連續評分。
  3. 因為不再有任何評分/獎勵，目標函式改成常數 0（純可行性問題）：
     只要找到「同時滿足全部硬性限制」的一組 (G, rG, B, rd, rk)
     即為解，不再追求「越小」或「越逼近邊界越好」。
     multistart 找到第一組可行解就停止（結果由隨機種子決定，具重現性）。

依賴套件：
  numpy, scipy, matplotlib (可選繪圖)
"""

import sys
import numpy as np
from scipy.optimize import minimize


def IfromA(A, G, rG):
    """計算由 A 點經 G 點向外延伸至圓 e 上的交點 I"""
    v = G - A
    norm_v = np.linalg.norm(v)
    if norm_v < 1e-12:
        return G.copy()
    return G + rG * v / norm_v


def circleIntersect(I, rk, B, rd):
    """計算以 I 為圓心半徑 rk，與以 B 為圓心半徑 rd 的兩圓交點 K"""
    d = B - I
    D = np.linalg.norm(d)
    if D > rk + rd or D < abs(rk - rd) or D < 1e-9:
        return np.array([np.nan, np.nan])
    a_ = (rk**2 - rd**2 + D**2) / (2.0 * D)
    h2 = rk**2 - a_**2
    if h2 < 0.0:
        return np.array([np.nan, np.nan])
    h = np.sqrt(h2)
    P2 = I + a_ * d / D
    perp = np.array([-d[1], d[0]]) / D * h
    K = P2 - perp
    return K


def minMarginOverRange(G, rG, B, rd, rk, a_min, a_max, b_min, b_max, na, nb):
    """在 (a, b) 網格範圍內計算全程最小死點餘裕 (向量化加速)"""
    aa = np.linspace(a_min, a_max, na)
    bb = np.linspace(b_min, b_max, nb)
    grid_b, grid_a = np.meshgrid(bb, aa)
    A_grid = np.column_stack([grid_b.ravel(), grid_a.ravel()])  # shape: (na*nb, 2)

    v = G - A_grid
    norm_v = np.linalg.norm(v, axis=1, keepdims=True)
    norm_v[norm_v < 1e-12] = 1e-12
    I_grid = G + rG * v / norm_v

    d_grid = B - I_grid
    D = np.linalg.norm(d_grid, axis=1)

    margin = np.minimum((rk + rd) - D, D - np.abs(rk - rd))
    return float(np.min(margin))


def swingInfo(G, rG, B, rd, rk, b, a_min, a_max, n):
    """針對特定 b，掃描 a_min 到 a_max 計算擺角資訊與單調性"""
    aa = np.linspace(a_min, a_max, n)
    th = np.empty(n)
    for i in range(n):
        A = np.array([b, aa[i]])
        I = IfromA(A, G, rG)
        K = circleIntersect(I, rk, B, rd)
        if np.isnan(K[0]):
            return {
                's': np.nan,
                'monotonic': False,
                'theta_lo': np.nan,
                'theta_hi': np.nan,
                'theta_a0': np.nan
            }
        th[i] = np.arctan2(K[1] - B[1], K[0] - B[0])

    th = np.unwrap(th)
    dth = np.diff(th)
    monotonic = (bool(np.all(dth >= 0)) or bool(np.all(dth <= 0))) and bool(np.max(np.abs(dth)) >= 1e-6)
    idx0 = int(np.argmin(np.abs(aa - 0.0)))

    return {
        's': float(np.rad2deg(np.max(th) - np.min(th))),
        'monotonic': monotonic,
        'theta_lo': float(np.rad2deg(th[0])),
        'theta_hi': float(np.rad2deg(th[-1])),
        'theta_a0': float(np.rad2deg(th[idx0]))
    }


def hardConstraints(x, a_min, a_max, b_min, b_max, b_samples,
                    req_margin, avgRange_max, swingBmin_range, swingBmax_range,
                    na, nb, nSwing):
    """
    純硬性不等式限制式：c(x) <= 0 才算滿足。
    沒有任何評分/獎勵/漸進式罰分，只回報「超出量」供 SQP / SLSQP 演算法求解。
    回傳形狀為 (6,) 的數組。
    """
    Gx, Gy, rG, Bx, By, rd, rk = x
    G = np.array([Gx, Gy])
    B = np.array([Bx, By])

    BIG = 1e6  # 幾何無解時回傳大數

    if rd <= 0.05 or rk <= 0.05 or rG <= 0.5:
        return np.full(6, BIG)

    m = minMarginOverRange(G, rG, B, rd, rk, a_min, a_max, b_min, b_max, na, nb)
    c1 = req_margin - m   # 要求 <= 0，即 m >= req_margin

    n_samples = len(b_samples)
    avgs = np.empty(n_samples)
    swings = np.empty(n_samples)

    for i in range(n_samples):
        info_i = swingInfo(G, rG, B, rd, rk, b_samples[i], a_min, a_max, nSwing)
        if np.isnan(info_i['s']) or not info_i['monotonic']:
            return np.array([c1, BIG, BIG, BIG, BIG, BIG])
        avgs[i] = (info_i['theta_lo'] + info_i['theta_hi']) / 2.0
        swings[i] = info_i['s']

    rangeAvg = np.max(avgs) - np.min(avgs)
    swing_bmin = swings[0]
    swing_bmax = swings[-1]

    c2 = rangeAvg - avgRange_max                 # 要求 <= 0
    c3 = swingBmin_range[0] - swing_bmin          # 要求 <= 0 (下限)
    c4 = swing_bmin - swingBmin_range[1]          # 要求 <= 0 (上限)
    c5 = swingBmax_range[0] - swing_bmax          # 要求 <= 0 (下限)
    c6 = swing_bmax - swingBmax_range[1]          # 要求 <= 0 (上限)

    return np.array([c1, c2, c3, c4, c5, c6])


def main():
    np.random.seed(1)

    # ---------- 1. 已知固定參數 ----------
    a_min = -5.0;  a_max =  5.0       # A_y 範圍 (已知)
    b_min = -3.5;  b_max =  3.5       # A_x 範圍 (已知；對稱範圍)

    # ---------- 2. 未知數搜尋範圍 (共7個：Gx,Gy,rG,Bx,By,rd,rk) ----------
    Gx_range = [5.0, 20.0]
    Gy_range = [-1.0, 1.0]
    rG_range = [6.0, 30.0]

    Bx_range = [10.0, 20.0]
    By_range = [-1.0, 1.0]

    rd_range = [6.0, 30.0]
    rk_range = [6.0, 30.0]

    # --- 邊界向量 (lb/ub) ---
    lb = np.array([Gx_range[0], Gy_range[0], rG_range[0], Bx_range[0], By_range[0], rd_range[0], rk_range[0]])
    ub = np.array([Gx_range[1], Gy_range[1], rG_range[1], Bx_range[1], By_range[1], rd_range[1], rk_range[1]])
    bounds = list(zip(lb, ub))

    req_margin = 0.05     # 死點安全餘裕 (硬性)
    nTrials    = 2000     # multistart 起始點數量上限（找到第一組可行解就停止）
    nBSamples  = 5        # 用幾個 b 代表點檢查「角度中點」與擺幅

    # ======================= 硬性範圍設定 (全部可調) =======================
    avgRange_max    = 0.5           # 角度中點在整個 b 範圍內的變動幅度上限 (deg)
    swingBmin_range = [60.0, 80.0]  # b=b_min 時，擺角必須落在此範圍 (deg)
    swingBmax_range = [180.0, 198.0]# b=b_max 時，擺角必須落在此範圍 (deg)
    # =======================================================================

    if avgRange_max <= 0:
        raise ValueError('avgRange_max 必須為正值。')
    if swingBmin_range[0] < 0 or swingBmax_range[0] < 0:
        raise ValueError('swingBmin_range / swingBmax_range 下限不可為負值。')

    b_samples = np.linspace(b_min, b_max, nBSamples)

    print('=========== 機構可行解搜尋開始（純硬性限制，無評分機制）===========')
    print(f'  死點餘裕 >= {req_margin:.2f}')
    print(f'  中點變動範圍 <= {avgRange_max:.2f} deg')
    print(f'  swing(b_min) in [{swingBmin_range[0]:.1f}, {swingBmin_range[1]:.1f}] deg')
    print(f'  swing(b_max) in [{swingBmax_range[0]:.1f}, {swingBmax_range[1]:.1f}] deg')

    # ---------- 3. 目標函式與限制式包裝 ----------
    objFun = lambda x: 0.0

    def nonlconFun(x):
        return hardConstraints(x, a_min, a_max, b_min, b_max, b_samples,
                               req_margin, avgRange_max, swingBmin_range, swingBmax_range,
                               9, 7, 31)

    def nonlconFunFine(x):
        return hardConstraints(x, a_min, a_max, b_min, b_max, b_samples,
                               req_margin, avgRange_max, swingBmin_range, swingBmax_range,
                               25, 17, 121)

    # SciPy SLSQP 限制式要求 fun(x) >= 0，因此用 -c(x) >= 0 代表 c(x) <= 0
    cons = ({'type': 'ineq', 'fun': lambda x: -nonlconFun(x)})
    consFine = ({'type': 'ineq', 'fun': lambda x: -nonlconFunFine(x)})

    # ---------- 4. multistart：找到第一組可行解就停止 ----------
    feasTol = 1e-4   # 判定「c(x) <= 0」是否成立的容許誤差
    bestX = None

    opts = {'maxiter': 1000, 'ftol': 1e-4, 'disp': False}

    for t in range(1, nTrials + 1):
        x0 = lb + np.random.rand(7) * (ub - lb)

        # 優先快篩：若起點已直接可行，無需耗時最佳化
        c0 = nonlconFun(x0)
        if np.all(c0 <= feasTol):
            bestX = x0
            print(f'第 {t} 次起始點自身即滿足全部限制式，停止 multistart。')
            break

        try:
            res = minimize(objFun, x0, method='SLSQP', bounds=bounds, constraints=cons, options=opts)
            if res.success or np.all(nonlconFun(res.x) <= feasTol):
                c = nonlconFun(res.x)
                if np.all(c <= feasTol):
                    bestX = res.x
                    print(f'第 {t} 次起始點經最佳化找到可行解，停止 multistart。')
                    break
        except Exception:
            continue

    if bestX is None:
        raise RuntimeError(
            f'{nTrials} 次 multistart 起點都沒找到同時滿足所有硬性限制的解，'
            f'請放寬 req_margin / avgRange_max / swingBmin_range / swingBmax_range，或擴大搜尋範圍再試一次。'
        )

    # ---------- 5. 局部精修 (用更高解析度的限制式重新確認/微調) ----------
    try:
        resFine = minimize(objFun, bestX, method='SLSQP', bounds=bounds, constraints=consFine, options=opts)
        if resFine.success or np.all(nonlconFunFine(resFine.x) <= feasTol):
            cFine = nonlconFunFine(resFine.x)
            if np.all(cFine <= feasTol):
                bestX = resFine.x
    except Exception:
        pass

    bestX = np.clip(bestX, lb, ub)

    Gx_opt, Gy_opt, rG_opt, Bx_opt, By_opt, rd_opt, rk_opt = bestX
    G_opt = np.array([Gx_opt, Gy_opt])
    B_opt = np.array([Bx_opt, By_opt])

    # ---------- 6. 最終高解析度驗證 ----------
    minMarginFinal = minMarginOverRange(G_opt, rG_opt, B_opt, rd_opt, rk_opt,
                                        a_min, a_max, b_min, b_max, 61, 41)

    infoFinal = swingInfo(G_opt, rG_opt, B_opt, rd_opt, rk_opt, b_max, a_min, a_max, 401)

    avgList = np.full(nBSamples, np.nan)
    swingList = np.full(nBSamples, np.nan)
    allOkForSamples = True

    for i in range(nBSamples):
        info_i = swingInfo(G_opt, rG_opt, B_opt, rd_opt, rk_opt, b_samples[i], a_min, a_max, 201)
        if np.isnan(info_i['s']) or not info_i['monotonic']:
            allOkForSamples = False
        avgList[i]   = (info_i['theta_lo'] + info_i['theta_hi']) / 2.0
        swingList[i] = info_i['s']

    avgRange = float(np.max(avgList) - np.min(avgList))
    swing_bmin_final = float(swingList[0])
    swing_bmax_final = float(swingList[-1])

    if minMarginFinal < req_margin - feasTol or np.isnan(infoFinal['s']) or not infoFinal['monotonic'] or not allOkForSamples:
        raise RuntimeError('最終高解析度驗證失敗，請重跑或調整搜尋範圍/req_margin。')

    if avgRange > avgRange_max + feasTol:
        raise RuntimeError(f'最終中點變動範圍 = {avgRange:.4f} deg 超出硬性上限 {avgRange_max:.2f} deg，請重跑或放寬 avgRange_max。')

    if swing_bmin_final < swingBmin_range[0] - feasTol or swing_bmin_final > swingBmin_range[1] + feasTol:
        raise RuntimeError(
            f'最終 swing(b_min) = {swing_bmin_final:.4f} deg 超出硬性範圍 [{swingBmin_range[0]:.1f}, {swingBmin_range[1]:.1f}]，'
            f'請重跑或調整搜尋範圍。'
        )

    if swing_bmax_final < swingBmax_range[0] - feasTol or swing_bmax_final > swingBmax_range[1] + feasTol:
        raise RuntimeError(
            f'最終 swing(b_max) = {swing_bmax_final:.4f} deg 超出硬性範圍 [{swingBmax_range[0]:.1f}, {swingBmax_range[1]:.1f}]，'
            f'請重跑或調整搜尋範圍。'
        )

    tolBound = 1e-6
    if np.any(bestX < lb - tolBound) or np.any(bestX > ub + tolBound):
        raise RuntimeError('最終解超出指定邊界範圍，請檢查邊界設定。')

    swing_opt   = infoFinal['s']
    theta_lo_u  = infoFinal['theta_lo']
    theta_hi_u  = infoFinal['theta_hi']
    theta_a0_u  = infoFinal['theta_a0']
    alpha_total = theta_hi_u - theta_lo_u
    sizeMetric  = rG_opt + rd_opt + rk_opt

    print('\n---------- 最終可行解 ----------')
    print(f'G 點座標      = ({Gx_opt:.4f}, {Gy_opt:.4f})')
    print(f'e 圓半徑 rG   = {rG_opt:.4f}')
    print(f'B 點座標      = ({Bx_opt:.4f}, {By_opt:.4f})')
    print(f'圓 d 半徑 rd  = {rd_opt:.4f}')
    print(f'圓 k 半徑 rk  = {rk_opt:.4f}')
    print(f'尺寸指標 (rG+rd+rk) = {sizeMetric:.4f}  (僅供參考，未參與求解)')
    print(f'全程最小死點餘裕 = {minMarginFinal:.4f} (需求 >= {req_margin:.2f})')
    print(f'A 最右側(b={b_max:.2f})時 BK 擺角 = {swing_opt:.4f} deg')
    print(f'真實總擺角 = {alpha_total:.4f} deg')

    print('\n【硬性限制檢查】')
    print(f'  中點變動範圍 = {avgRange:.4f} deg  (硬性上限 {avgRange_max:.2f} deg)')
    print(f'  swing(b_min={b_min:.2f}) = {swing_bmin_final:.4f} deg  (硬性範圍 [{swingBmin_range[0]:.1f}, {swingBmin_range[1]:.1f}])')
    print(f'  swing(b_max={b_max:.2f}) = {swing_bmax_final:.4f} deg  (硬性範圍 [{swingBmax_range[0]:.1f}, {swingBmax_range[1]:.1f}])')

    print(f'\n【角度中點(兩端平均) 各 b 樣本點數值，共 {nBSamples} 點】')
    for i in range(nBSamples):
        print(f'  b={b_samples[i]:.3f}  中點平均角度 = {avgList[i]:.4f} deg  |  擺角 = {swingList[i]:.4f} deg')

    print('\n【邊界確認】')
    print(f'  Gx={Gx_opt:.3f} in [{Gx_range[0]:.1f},{Gx_range[1]:.1f}] | '
          f'Gy={Gy_opt:.3f} in [{Gy_range[0]:.1f},{Gy_range[1]:.1f}] | '
          f'rG={rG_opt:.3f} in [{rG_range[0]:.1f},{rG_range[1]:.1f}]')
    print(f'  Bx={Bx_opt:.3f} in [{Bx_range[0]:.1f},{Bx_range[1]:.1f}] | '
          f'By={By_opt:.3f} in [{By_range[0]:.1f},{By_range[1]:.1f}]')
    print(f'  rd={rd_opt:.3f} in [{rd_range[0]:.1f},{rd_range[1]:.1f}] | '
          f'rk={rk_opt:.3f} in [{rk_range[0]:.1f},{rk_range[1]:.1f}]')

    # ---------- 7. 繪圖 ----------
    try:
        import matplotlib.pyplot as plt
        from matplotlib.patches import Circle

        # 中文字體支援設定
        plt.rcParams['font.sans-serif'] = ['Microsoft JhengHei', 'SimHei', 'Arial Unicode MS', 'DejaVu Sans']
        plt.rcParams['axes.unicode_minus'] = False

        # 圖 1: 角度中點 vs b
        plt.figure('角度中點 vs A_x (b)')
        plt.plot(b_samples, avgList, 'o-', linewidth=1.5, markerfacecolor='blue')
        plt.xlabel('b (A_x)')
        plt.ylabel('兩端角度平均值 (deg)')
        plt.title(f'角度中點 vs b (變動範圍 = {avgRange:.3f} deg，硬性上限 = {avgRange_max:.2f} deg)')
        plt.grid(True)

        # 圖 2: 擺角 vs b
        plt.figure('擺角 vs A_x (b)，檢查硬性範圍')
        plt.plot(b_samples, swingList, 'o-', linewidth=1.5, color=[0.85, 0.2, 0.2], markerfacecolor='red')
        plt.axhline(swingBmin_range[0], linestyle='--', color=[0.2, 0.2, 0.85], label='b_min 下限')
        plt.axhline(swingBmin_range[1], linestyle='--', color=[0.2, 0.2, 0.85], label='b_min 上限')
        plt.axhline(swingBmax_range[0], linestyle='--', color=[0.2, 0.6, 0.2], label='b_max 下限')
        plt.axhline(swingBmax_range[1], linestyle='--', color=[0.2, 0.6, 0.2], label='b_max 上限')
        plt.xlabel('b (A_x)')
        plt.ylabel('擺角 (deg)')
        plt.title(f'擺角 vs b (b_min={swing_bmin_final:.2f} deg in [{swingBmin_range[0]:.1f},{swingBmin_range[1]:.1f}], '
                  f'b_max={swing_bmax_final:.2f} deg in [{swingBmax_range[0]:.1f},{swingBmax_range[1]:.1f}])')
        plt.legend(loc='best')
        plt.grid(True)

        # 圖 3: 機構示意圖
        fig, ax = plt.subplots(num='機構示意圖 (a = -5, 0, 5，b 在最右側)')
        ax.set_aspect('equal')
        ax.grid(True)

        # 畫 G 圓與 B 圓
        circ_G = Circle((G_opt[0], G_opt[1]), rG_opt, color=[0.7, 0.7, 0.7], fill=False, linestyle=':')
        circ_B = Circle((B_opt[0], B_opt[1]), rd_opt, color=[0.3, 0.6, 1.0], fill=False, linestyle='--')
        ax.add_patch(circ_G)
        ax.add_patch(circ_B)

        ax.plot(G_opt[0], G_opt[1], 'ks', markerfacecolor='k')
        ax.text(G_opt[0], G_opt[1] - 1.0, 'G')
        ax.plot(B_opt[0], B_opt[1], 'ks', markerfacecolor='k')
        ax.text(B_opt[0], B_opt[1] - 1.0, 'B')

        colors = [[0.85, 0.2, 0.2], [0.2, 0.6, 0.2], [0.2, 0.2, 0.85]]
        labels = [f'a={a_min:.0f} (下端)', 'a=0 (中點)', f'a={a_max:.0f} (上端)']
        aVals = [a_min, 0.0, a_max]

        for t in range(3):
            A_t = np.array([b_max, aVals[t]])
            I_t = IfromA(A_t, G_opt, rG_opt)
            K_t = circleIntersect(I_t, rk_opt, B_opt, rd_opt)

            col = np.array(colors[t])
            light_col = col * 0.5 + 0.5

            ax.plot([A_t[0], G_opt[0]], [A_t[1], G_opt[1]], '-', color=light_col)
            ax.plot(A_t[0], A_t[1], 'o', color=col, markerfacecolor=col)
            ax.plot(I_t[0], I_t[1], '^', color=col, markerfacecolor=col)
            ax.plot([I_t[0], K_t[0]], [I_t[1], K_t[1]], '-', color=col, linewidth=1.5)
            ax.plot([B_opt[0], K_t[0]], [B_opt[1], K_t[1]], '-', color=col, linewidth=2.5, label=labels[t])
            ax.plot(K_t[0], K_t[1], '*', color=col, markerfacecolor=col, markersize=10)

        ax.legend(loc='upper left', bbox_to_anchor=(1, 1))
        ax.set_title(f'rd={rd_opt:.3f}, rk={rk_opt:.3f}, 總擺角={alpha_total:.2f} deg, 中點變動={avgRange:.2f} deg')
        ax.set_xlabel('x')
        ax.set_ylabel('y')

        plt.tight_layout()
        plt.show()

    except ImportError:
        print('\n[提醒] 未安裝 matplotlib，跳過繪圖顯示。若需繪圖請執行: pip install matplotlib')

    print('\n=========== 完成 ===========')


if __name__ == '__main__':
    main()

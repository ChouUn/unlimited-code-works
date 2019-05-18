//@ Including Header
#include <cul/std>

/**
 *  Name : cf1137a.cpp.cpp
 *  Date : 2019/3/16 16:28
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 1000;
int a[N][N], h[N][N], hr[N][N], v[N][N], vr[N][N];

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    rep(i, 0, n) rep(j, 0, m) cin >> a[i][j];

    int b[N];
    rep(i, 0, n) {
        rep(j, 0, m) b[j] = j;
        sort(b, b + m, [i](int p, int q) { return a[i][p] < a[i][q]; });
        rep(j, 0, m) h[i][b[j]] = j ? h[i][b[j - 1]] + (a[i][b[j - 1]] != a[i][b[j]]) : 0;
        reverse(b, b + m);
        rep(j, 0, m) hr[i][b[j]] = j ? hr[i][b[j - 1]] + (a[i][b[j - 1]] != a[i][b[j]]) : 0;
    }
    rep(j, 0, m) {
        rep(i, 0, n) b[i] = i;
        sort(b, b + n, [j](int p, int q) { return a[p][j] < a[q][j]; });
        rep(i, 0, n) v[b[i]][j] = i ? v[b[i - 1]][j] + (a[b[i - 1]][j] != a[b[i]][j]) : 0;
        reverse(b, b + n);
        rep(i, 0, n) vr[b[i]][j] = i ? vr[b[i - 1]][j] + (a[b[i - 1]][j] != a[b[i]][j]) : 0;
    }
    rep(i, 0, n) rep(j, 0, m) cout << max(h[i][j], v[i][j]) + max(hr[i][j], vr[i][j]) + 1 << (j == m - 1 ? '\n' : ' ');
    return 0;
}

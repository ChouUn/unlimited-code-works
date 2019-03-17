//@ Including Header
#include <csl_std.h>

/**
 *  Name : cf1137a.cpp.cpp
 *  Date : 2019/3/16 16:28
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 1000;
int a[N][N], h[N][N], hr[N][N], v[N][N], vr[N][N];

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m; cin >> n >> m;
    rep(i, 0, n) rep(j, 0, m) cin >> a[i][j];

    int b[N];
    rep(i, 0, n) {
        rep(j, 0, m) b[j] = j;
        sort(b, b + m, [i](int p, int q) {
           return a[i][p] < a[i][q];
        });
        rep(j, 0, m) h[i][b[j]] = j ? h[i][b[j - 1]] + (a[i][b[j - 1]] != a[i][b[j]]): 0;
        reverse(b, b + m);
        rep(j, 0, m) hr[i][b[j]] = j ? hr[i][b[j - 1]] + (a[i][b[j - 1]] != a[i][b[j]]) : 0;
    }
    rep(j, 0, m) {
        rep(i, 0, n) b[i] = i;
        sort(b, b + n, [j](int p, int q) {
            return a[p][j] < a[q][j];
        });
        rep(i, 0, n) v[b[i]][j] = i ? v[b[i - 1]][j] + (a[b[i - 1]][j] != a[b[i]][j]) : 0;
        reverse(b, b + n);
        rep(i, 0, n) vr[b[i]][j] = i ? vr[b[i - 1]][j]  + (a[b[i - 1]][j] != a[b[i]][j]) : 0;
    }
//    rep(i, 0, n) { rep(j, 0, m) cout << h[i][j] << " "; cout << endl; }
//    rep(i, 0, n) { rep(j, 0, m) cout << v[i][j] << " "; cout << endl; }
//    rep(i, 0, n) { rep(j, 0, m) cout << hr[i][j] << " "; cout << endl; }
//    rep(i, 0, n) { rep(j, 0, m) cout << vr[i][j] << " "; cout << endl; }
    rep(i, 0, n) rep(j, 0, m)
        cout << max(h[i][j], v[i][j]) + max(hr[i][j], vr[i][j]) + 1<< (j == m - 1 ? '\n' : ' ');
    return 0;
}

//@ Anti Stack Overflow
// #define ANTI_STACK_OVERFLOW
int main() {
#ifdef ANTI_STACK_OVERFLOW
    std::size_t size = 16 << 20; // KB(<<10), MB(<<20).
    char* data = (char*)malloc(size) + size;
#if __x86_64__ || __ppc64__ || _WIN64
    __asm__ __volatile__("movq %0, %%rsp \n pushq $_exit \n" ::"r"(data));
#else
    __asm__ __volatile__("movl %0, %%esp \n pushl $_exit \n" ::"r"(data));
#endif
#endif
    exit(Main());
}

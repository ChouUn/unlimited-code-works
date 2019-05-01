//@ Including Header
#include <csl_std.h>

/**
 *  Name : c.cpp
 *  Date : 2019/3/24 13:32
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int M = 110;
int a[M];
int dp[M][M];

int dfs(int p, int q) {
    if (dp[p][q] != -1) return dp[p][q];
    if (p + 2 > q) return 0;

    int res = -1;
    rep(i, p + 1, q) {
        int tmp = dfs(p, i) + dfs(i, q);
        if (res == -1 || tmp < res) res = tmp;
    }
    return dp[p][q] = res + a[q] - a[p] - 2;
}

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        int n, m; cin >> n >> m;
        a[0] = 0, a[m + 1] = n + 1;
        rep(i, 1, m + 1) cin >> a[i];

        memset(dp, 0xff, sizeof(dp));
        cout << dfs(0, m + 1) << endl;
    }
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

//@ Including Header
#include <csl_std.h>

/**
 *  Name : f.cpp
 *  Date : 2019/3/24 15:00
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = static_cast<const int>(2e5 + 10);
int w[N];
vector<int> g[N];
ll dp[N][2];

void dfs(int u, int from) {
    dp[u][0] = w[u];
    for (auto v : g[u]) {
        if (v == from) continue;
        dfs(v, u);
        if (dp[v][0] > 0) dp[u][0] += dp[v][0];
    }

    dp[u][1] = max(dp[u][0], 0ll);
    for (auto v : g[u]) {
        if (v == from) continue;
        dp[u][1] = max(dp[u][1], dp[v][1]);
    }
}

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        int n; cin >> n;
        rep(i, 0, n) g[i].clear();
        rep(i, 0, n) cin >> w[i];
        rep(i, 1, n) {
            int u, v; cin>> u >> v; u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(0, -1);
        cout << max(dp[0][0], dp[0][1]) << endl;
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

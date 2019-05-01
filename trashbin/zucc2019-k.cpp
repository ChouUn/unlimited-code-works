//@ Including Header
#include <csl_std.h>

/**
 *  Name : k.cpp
 *  Date : 2019/3/24 16:30
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = static_cast<const int>(1e6 + 10);
vector<int> g[N];
int deg[N];

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        ++deg[v];
    }

    queue<int> q;
    rep(i, 0, n) if (deg[i] == 0) q.push(i);

    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); ++ans;
        for (auto v : g[u]) if (--deg[v] == 0) q.push(v);
    }
    cout << (ans == n ? "Keadin NB!" : "Oh, it's too messy!") << endl;

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

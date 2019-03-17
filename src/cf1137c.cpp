//@ Including Header
#include <csl_std.h>
#include <graph.h>

/**
 *  Name : cf1137c.cpp
 *  Date : 2019/3/16 18:27
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = static_cast<const int>(1e5);
int u[N], v[N];
string w[N];

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, d;
    cin >> n >> m >> d;
    rep(i, 0, m) cin >> u[i] >> v[i], --u[i], --v[i];
    rep(i, 0, n) cin >> w[i];

    csl::graph<int> g;
    g.build(static_cast<unsigned int>(n * d), static_cast<unsigned int>(m * d));
    rep(i, 0, m) {
        rep(j, 0, d) {
            auto ua = static_cast<unsigned int>(u[i] * d + j);
            auto va = static_cast<unsigned int>(v[i] * d + (j + 1) % d);
            g.add_edge(ua, va, 1);
        }
    }

    csl::tarjan<int> tar;
    tar.scc(g);
    int l = tar.size();

    vector<int> a(static_cast<unsigned int>(l));
    {
        vector<set<int>> vs(static_cast<unsigned int>(l));
        rep(u, 0, n) {
            rep(j, 0, d) {
                if (w[u][j] == '0') continue;
                auto ua = u * d + j;
                int k = tar[ua];
                vs[k].insert(u);
            }
        }
        rep(i, 0, l) a[i] = vs[i].size();
    }

    csl::graph<int> ga;
    ga.build(static_cast<unsigned int>(l), static_cast<unsigned int>(m * d));
    vector<int> deg(static_cast<unsigned int>(l), 0);
    rep(i, 0, m) {
        rep(j, 0, d) {
            auto ua = static_cast<unsigned int>(u[i] * d + j);
            auto va = static_cast<unsigned int>(v[i] * d + (j + 1) % d);
            auto uaa = tar[ua];
            auto vaa = tar[va];
            if (uaa == vaa) continue;
            ga.add_edge(uaa, vaa, 1);
            deg[vaa]++;
        }
    }

    int s = tar[0 * d + 0];
    vector<int> dp(l, INT_MIN);
    queue<int> q;
    q.push(s);
    dp[s] = a[s];
    rep(i, 0, l) {
        if (deg[i] == 0 && i != s) {
            q.push(i);
            dp[i] = INT_MIN;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto it = ga.getHead(static_cast<unsigned int>(u)); it; it = it->next) {
            int v = it->to;
            dp[v] = max(dp[v], dp[u] + a[v]);
            if (--deg[v] == 0) q.push(v);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
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

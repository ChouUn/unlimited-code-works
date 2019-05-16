//@ Including Header
#include <cul/std>
#include <ds/graph>
#include <graph/scc>

/**
 *  Name : cf1137c.cpp
 *  Date : 2019/3/16 18:27
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = (int) 1e5;
const int D = 50;
int eu[N], ev[N];
string w[N];

int dp[N][D];

cul::graph<> G;
cul::kosaraju<std::tuple<>, std::tuple<>> K;

int p; // duration in one component
int ts[N]; // timestamp for vertices in a component

void dfs(int u, int current_ts) {
    if (ts[u]) {
        p = __gcd(p, std::abs(current_ts - ts[u]));
        return;
    }

    ts[u] = current_ts;
    for (auto &edge : G.edges(u)) {
        auto v = edge.first;
        if (K.inverse(v) == K.inverse(u)) dfs(v, current_ts + 1);
    }
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, d;
    cin >> n >> m >> d;
    rep(i, 0, m) cin >> eu[i] >> ev[i], --eu[i], --ev[i];
    rep(i, 0, n) cin >> w[i];

    G.build(n, m);
    rep(i, 0, m) G.add_edge(eu[i], ev[i]);

    K = cul::make_kosaraju(G, true);

    for (auto &compo : cul::backwards(K.compos)) {
        p = d;
        dfs(compo.front(), 1);
        int q = d / p;

        vi f(p);
        for (auto u : compo) {
            rep(i, 0, p) {
                rep(j, 0, q) {
                    int up = (ts[u] + i + j * p) % d;
                    if (w[u][up] == '1') {
                        ++f[i];
                        break;
                    }
                }
            }
        }

        vi g = f;
        for (auto u : compo) {
            for (auto edge : G.edges(u)) {
                auto v = edge.first;
                if (K.inverse(v) == K.inverse(u)) continue;
                rep(i, 0, p) {
                    rep(j, 0, q) {
                        int vp = (ts[u] + 1 + i + j * p) % d;
                        g[i] = max(g[i], f[i] + dp[v][vp]);
                    }
                }
            }
        }

        for (auto u : compo) {
            rep(i, 0, p) {
                rep(j, 0, q) {
                    int up = (ts[u] + i + j * p) % d;
                    dp[u][up] = g[i];
                }
            }
        }
    }

    cout << dp[0][0] << endl;

    return 0;
}

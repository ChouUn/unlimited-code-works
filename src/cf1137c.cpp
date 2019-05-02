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

const int N = (int)1e5;
int eu[N], ev[N];
string w[N];

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, d;
    cin >> n >> m >> d;
    rep(i, 0, m) cin >> eu[i] >> ev[i], --eu[i], --ev[i];
    rep(i, 0, n) cin >> w[i];

    auto G = new cul::graph<>;
    G->build((size_t)(n * d), (size_t)(m * d));
    rep(i, 0, m) {
        rep(j, 0, d) {
            size_t up = eu[i] * d + j;
            size_t vp = ev[i] * d + (j + 1) % d;
            G->add_edge(up, vp);
        }
    }
    auto K = cul::make_kosaraju(*G, true);
    delete G;
    size_t l = K.size();

    vector<int> a(l);
    {
        vector<vector<int>> vs(l);
        rep(u, 0, n) {
            rep(j, 0, d) {
                if (w[u][j] == '0') continue;
                auto up = u * d + j;
                int upp = K[up];
                vs[upp].push_back(u);
            }
        }
        rep(i, 0, (int)l) {
            sort(vs[i].begin(), vs[i].end());
            a[i] = unique(vs[i].begin(), vs[i].end()) - vs[i].begin();
        }
    }

    cul::graph<> ga;
    ga.build(l, (size_t)(m * d));
    vector<int> deg(l, 0);
    rep(i, 0, m) {
        rep(j, 0, d) {
            auto up = (size_t)(eu[i] * d + j);
            auto vp = (size_t)(ev[i] * d + (j + 1) % d);
            auto upp = K[up];
            auto vpp = K[vp];
            if (upp == vpp) continue;
            ga.add_edge(upp, vpp);
            deg[vpp]++;
        }
    }

    int s = K[0 * d + 0];
    vector<int> dp(l, INT_MIN);
    queue<int> q;
    q.push(s);
    dp[s] = a[s];
    rep(i, 0, (int)l) {
        if (deg[i] == 0 && i != s) {
            q.push(i);
            dp[i] = INT_MIN;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &it : ga.edges(u)) {
            int v = it.first;
            dp[v] = max(dp[v], dp[u] + a[v]);
            if (--deg[v] == 0) q.push(v);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
    return 0;
}

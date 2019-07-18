//@ Including Header
#include <csl_std.h>

const int N = 60;
const int M = 60;

#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <algorithm>

namespace zkw_cost {
    const int V = N * 2 + M + 2;
    const int E = (N * 4 + M * N + 10) * 2;
    const int oo = INT_MAX / 2;

    struct edge {
        edge *next, *pair;
        int cost, rest, to;
    };

    edge e[E], *head[V]; bool vis[V];
    int en, S, T, cost, p;

    inline void clear() {
        memset(head, 0x00, sizeof head), en = 0;
    }

    inline edge* add_edge(int from, int to, int cost, int rest) {
        edge* res = e + en++;
        res->to = to, res->cost = cost, res->rest = rest;
        return res->next = head[from], head[from] = res, res;
    }

    inline void add_couple_edge(int from, int to, int cost, int rest) {
        edge* x = add_edge(from, to, +cost, rest);
        edge* y = add_edge(to, from, -cost, 0);
        x->pair = y, y->pair = x;
    }

    int aug(int u, int ma) {
        if (u == T) return cost += p * ma, ma;
        vis[u] = true; int mi = ma;
        for (edge* i = head[u]; i; i = i->next)
            if (i->rest && !i->cost && !vis[i->to]) {
                int d = aug(i->to, std::min(mi, i->rest));
                i->rest -= d, i->pair->rest += d, mi -= d;
                if (!mi) break;
            }
        return ma - mi;
    }

    bool relabel(int n) {
        static int d[V]; std::fill_n(d, n, oo); d[T] = 0;
        std::deque<int> Q; Q.push_back(T);
        while(!Q.empty()) {
            int dt, u = Q.front(); Q.pop_front();
            for(edge* i = head[u]; i; i = i->next)
                if(i->pair->rest && (dt = d[u] - i->cost) < d[i->to])
                    ((d[i->to] = dt) <= d[Q.size() ? Q.front() : S]) ?
                    Q.push_front(i->to) : Q.push_back(i->to);
        }
        for(int u = 0; u < n; ++u)
            for(edge* i = head[u]; i; i = i->next) i->cost += d[i->to] - d[u];
        return p += d[S], d[S] < oo;
    }

    void solve(int s, int t, int n) {
        S = s, T = t, cost = 0, p = 0;
        while(relabel(n)) do memset(vis, 0x00, sizeof vis); while(aug(S, oo));
    }
}

/**
 *  Name : i.cpp
 *  Date : 2019/3/24 16:11
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

int u[N], v[N];

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m; cin >> n >> m;
    rep(i, 0, n) cin >> u[i] >> v[i], --u[i], --v[i];

    const int n_offset = 0;
    const int m_offset = n_offset + n;
    const int fee_offset = m_offset + m;
    const int st_offset = fee_offset + n;
    const int S = st_offset + 0;
    const int T = st_offset + 1;
    const int nn = T + 1;

    rep(i, 0, n) zkw_cost::add_couple_edge(S, n_offset + i, 0, 1);
    rep(i, 0, n) {
        zkw_cost::add_couple_edge(n_offset + i, m_offset + u[i], 0, 1);
        zkw_cost::add_couple_edge(n_offset + i, m_offset + v[i], 0, 1);
    }
    rep(i, 0, m) rep(j, 0, n) {
        int cost = (j + 1) * (j + 1) - j * j;
        zkw_cost::add_couple_edge(m_offset + i, fee_offset + j, cost, 1);
    }
    rep(i, 0, n) zkw_cost::add_couple_edge(fee_offset + i, T, 0, n);
    zkw_cost::solve(S, T, nn);
    cout << zkw_cost::cost << endl;

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

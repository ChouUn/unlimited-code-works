//@ Including Header
//
// Created by ChouUn on 2019/4/3.
//

#ifndef UNLIMITED_CODE_WORKS_STD
#define UNLIMITED_CODE_WORKS_STD

#include <bits/stdc++.h>

using namespace std;

typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;

typedef long double ld;

typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<pii> vpii;

#define rep(i, a, b) for(auto i=a, i##_n=b; i<i##_n; ++i)
#define per(i, a, b) for(auto i=b, i##_n=a; i-->i##_n; )
#define endl '\n'

#endif //UNLIMITED_CODE_WORKS_STD


/**
 *  Name : gcj2019r1c.cpp
 *  Date : 2019/4/13 9:31
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 1000;
const int L = 51;
const int C = 26;

struct Node {
    int next[C];
    int cnt;

    Node(): next(), cnt(0) {
        rep(i, 0, C) next[i] = -1;
    }

};

Node nodes[N * L];
int n_nodes;

void add_node(const string &s) {
    int idx = 0;
    nodes[idx].cnt += 1;

    for (auto ch : s) {
        int c = ch - 'A';
        if (nodes[idx].next[c] == -1) {
            nodes[n_nodes] = {};
            nodes[idx].next[c] = n_nodes++;
        }
        idx = nodes[idx].next[c];
        nodes[idx].cnt += 1;
    }
}

int dfs(int idx) {
    if (idx == -1) {
        return 0;
    }

    int res = 0;
    rep(i, 0, C) {
        int sub = dfs(nodes[idx].next[i]);
        res += sub;
        nodes[idx].cnt -= sub;
    }
    if (nodes[idx].cnt >= 2) {
        res += 2;
        nodes[idx].cnt -= 2;
    }
    return res;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        std::cout << "Case #" << __ << ": ";

        int n;
        cin >> n;

        n_nodes = 1;
        nodes[0] = {};

        rep(i, 0, n) {
            string s;
            cin >> s;
            reverse(s.begin(), s.end());
            add_node(s);
        }

        int ans = 0;
        rep(i, 0, C) ans += dfs(nodes[0].next[i]);
        cout << ans << endl;
    }
    return 0;
}

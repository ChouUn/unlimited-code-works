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
 *  Name : cf1152b.cpp
 *  Date : 2019/4/24 22:41
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

int select_min_zero(u64 m) {
    int b = 32;
    while (b >= 0 && ((1ull << b) & ~m)) --b;
    while (b >= 0 && ((1ull << b) & m)) --b;
    return b;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u64 m; cin >> m;

    int ans = 0;
    vi seq;
    while (select_min_zero(m) != -1) {
        ++ans;
        if (ans % 2) {
            int b = select_min_zero(m) + 1;
            seq.push_back(b);
            m ^= (1ull << b) - 1;
        } else {
            m += 1;
        }
    }
    cout << ans << endl;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        if (it != seq.begin()) cout << ' ';
        cout << *it;
    }
    cout << endl;

    return 0;
}

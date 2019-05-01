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
 *  Name : cf1152a.cpp
 *  Date : 2019/4/24 22:37
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> u(2);
    rep(i, 0, n) {
        int a; cin >> a;
        ++u[a % 2];
    }
    vector<int> v(2);
    rep(i, 0, m) {
        int a; cin >> a;
        ++v[a % 2];
    }
    cout << min(u[0], v[1]) + min(u[1], v[0]) << endl;

    return 0;
}

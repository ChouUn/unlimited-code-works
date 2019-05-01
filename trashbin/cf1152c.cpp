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
 *  Name : cf1152c.cpp
 *  Date : 2019/4/24 23:05
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

i64 calc(i64 a, i64 b) {
    return a / __gcd(a, b) * b;
}

i64 solve(i64 a, i64 b) {
    if (a == b) return 0;

    i64 c = abs(a - b);
    vector<pair<i64, i64>> v;
    for (i64 i = 1; i * i <= c; ++i) {
        if (c % i) continue;
        i64 j = c / i;
        i64 d = (i - a % i) % i;
        i64 e = (j - a % j) % j;
        v.emplace_back(calc(a + d, b + d), d);
        v.emplace_back(calc(a + e, b + e), e);
    }
    sort(v.begin(), v.end());
    return v.begin()->second;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 a, b; cin >> a >> b;
    cout << solve(a, b) << endl;

    return 0;
}

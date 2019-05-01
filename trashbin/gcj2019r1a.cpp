//@ Including Header
// Name : ChouUn's Standard Library 纸农の标准库
// Copyright : fateud.com
#ifndef CSL_STD_H_
#define CSL_STD_H_ 20151122L
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair< int, int > pii;
typedef std::vector< int > vi;
typedef std::vector< vi > vvi;
typedef std::vector< pii > vpii;

#define rep(i,a,b) for(auto i=a,i##_n=b;i<i##_n;++i)
#define per(i,a,b) for(auto i=b,i##_n=a;i-->i##_n;)
#define endl '\n'

#endif /* CSL_STD_H_ */

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

/**
 *  Name : gcj2019r1a.cpp
 *  Date : 2019/4/13 11:12
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */



//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        int n, m; cin >> n >> m;

        bool rev = false;
        if (n > m) swap(n, m), rev = true;

        pii p;
        rep(i, 1, m) {
            if (gcd(i, m) != 1) continue;
            rep(j, 2, m) {
                if (gcd(j, m) != 1) continue;

                vi a, b;
                rep(k, 1, m + 1) {
                    a.push_back((k * i) % m);
                    b.push_back((k * j) % m);
                }
            }
        }
    }
    return 0;
}

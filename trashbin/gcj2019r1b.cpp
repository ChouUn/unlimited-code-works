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
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<pii> vpii;

#define rep(i, a, b) for(auto i=a,i##_n=b;i<i##_n;++i)
#define per(i, a, b) for(auto i=b,i##_n=a;i-->i##_n;)
#define endl '\n'

#endif /* CSL_STD_H_ */


/**
 *  Name : gcj2019r1b.cpp
 *  Date : 2019/4/13 10:26
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

typedef long long LL;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

void extend_Euclid(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    extend_Euclid(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

LL Inv(LL a, LL b) {
    LL d = gcd(a, b);
    if (d != 1) return -1;
    LL x, y;
    extend_Euclid(a, b, x, y);
    return (x % b + b) % b;
}

bool merge(LL R, LL M, LL ri, LL mi, LL &a3, LL &m3) {
    LL g = gcd(M, mi);
    LL c = ri - R;
    if (c % g) return false;
    c = (c % mi + mi) % mi;
    M /= g;
    mi /= g;
    c /= g;
    c *= Inv(M, mi);
    c %= mi;
    c *= M * g;
    c += R;
    m3 = M * mi * g;
    a3 = (c % m3 + m3) % m3;
    return true;
}

LL CRT(int n, const vector<int> &m, const vector<int> &a) {
    LL a1 = a[0];
    LL m1 = m[0];
    rep(i, 1, n) {
        LL a2 = a[i];
        LL m2 = m[i];
        LL m3, a3;
        if (!merge(a1, m1, a2, m2, a3, m3))
            return -1;
        a1 = a3;
        m1 = m3;
    }
    return (a1 % m1 + m1) % m1;
}

const int N = 18;

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    vector<int> prms = {2, 9, 5, 7, 11, 13, 17};
//    rep(i, 0, 1000000) {
//        vector<int> mods;
//        for (auto prm : prms) mods.push_back(i % prm);
//        if (i != CRT(prms.size(), prms, mods)) exit(1);
//    }

    int _, __ = 1;
    int n, m;
    for (std::cin >> _ >> n >> m; _; --_, ++__) {
        vector<int> mods;
        for (auto prm : prms) {
            rep(i, 0, N) cout << prm << (i == N - 1 ? '\n' : ' ');
            flush(cout);

            int e = 0;
            rep(i, 0, N) {
                int d;
                cin >> d;
                e += d;
            }
            mods.push_back(e);
        }

        int ans = CRT(7, prms, mods);
        cout << ans << endl;
        flush(cout);

        int ver;
        cin >> ver;
        if (ver == -1) exit(-1);
    }
    return 0;
}

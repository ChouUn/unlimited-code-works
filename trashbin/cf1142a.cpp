//@ Including Header
#include "../libs/cul/std"
#include "../libs/csl_math.h"

/**
 *  Name : cf1142a.cpp.cpp
 *  Date : 2019/4/3 1:42
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

ll calc(ll p, ll q) {
    q = q % p;
    ll r = csl::gcd(p, q);
    return p / r;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, k, a, b;
    cin >> n >> k >> a >> b;

    vector<ll> ans;
    ll p = n * k;
    if (a > b) swap(a, b);
    for (auto j : {-a, +a}) {
        rep(i, 0, (int) n + 1) {
            ll q = i * k + b + j;
            if (q <= 0) continue;
            ll res = calc(p, q);
            ans.push_back(res);
        }
    }

    const auto pr = minmax_element(ans.begin(), ans.end());
    cout << *pr.first << " " << *pr.second << endl;

    return 0;
}

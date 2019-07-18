//@ Including Header
#include <cul/std>

/**
 *  Name : jsk2019r13b.cpp
 *  Date : 2019/6/1 16:09
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const i32 N = 1000;
const i64 M = (i64)1e9 + 7;
i64 fac[N + 1], inv[N + 1];

i64 powll(i64 n, i64 k) {
    if (k == 0) return 1;
    i64 res = powll(n, k / 2);
    if (k % 2) return res * res % M * n % M;
    else return res * res % M;
}

i64 com(i64 n, i64 k) {
    return fac[n] * inv[k] % M * inv[n - k] % M;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    fac[0] = 1;
    rep(i, 1, N + 1) fac[i] = fac[i - 1] * i % M;
    inv[N] = powll(fac[N], M - 2);
    per(i, 0, N) inv[i] = inv[i + 1] * (i + 1) % M;

    for (int n; cin >> n && n != 0;) {
        i64 ans = 0;
        for (int i = 0; i <= n; i += 2) {
            i64 x = com(n, i);
            for (int j = 0; j <= n - i; j += 2) {
                i64 y = com(n - i, j);
                i64 z = powll(2, n - i - j);
                ans += x * y % M * z % M;
                ans %= M;
            }
        }
        cout << ans << endl;
    }

    return 0;
}

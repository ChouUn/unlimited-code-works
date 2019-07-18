//@ Including Header
#include <cul/std>

/**
 *  Name : jsk2019r13d.cpp
 *  Date : 2019/6/1 16:39
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const i64 M = (i64)1e9 + 7;

i64 powll(i64 n, i64 k) {
    if (k == 0) return 1;
    i64 res = powll(n, k / 2);
    if (k % 2) return res * res % M * n % M;
    else return res * res % M;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 phi = M - 1;
    for (string n; cin >> n && n != "0";) {
        i64 np;
        if (n > "1000000007") {
            np = 0;
            for (auto ch : n) {
                np = np * 10 + ch - '0';
                np %= phi;
            }
            np -= 1;
            if (np < phi) np += phi;
        } else {
            stringstream ss;
            ss << n;
            ss >> np;
            np -= 1;
        }

        i64 ans = powll(2, np) * (powll(2, np) + 1) % M;
        cout << ans << endl;
    }

    return 0;
}

//@ Including Header
#include <cul/std>

/**
 *  Name : cf1137b.cpp
 *  Date : 2019/3/16 17:27
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int B = 137;
const i64 MOD = (i64) 1e9 + 7;

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    set<int> p;
    i64 x = 0;
    for (char i : t) {
        x = (x * B + i) % MOD;
        p.insert(static_cast<int &&>(x));
    }
    i64 y = 1;
    x = 0;
    unsigned int z = 0;
    for (int i = t.size() - 1; i >= 1; i--) {
        x = (x + y * t[i]) % MOD;
        y = y * B % MOD;
        if (p.find(x) != p.end()) z = t.size() - i;
    }
    string r = t.substr(z);

    int s0 = 0, s1 = 0, t0 = 0, t1 = 0, r0 = 0, r1 = 0;
    for (auto ch : s) (ch == '0' ? s0 : s1)++;
    for (auto ch : t) (ch == '0' ? t0 : t1)++;
    for (auto ch : r) (ch == '0' ? r0 : r1)++;

    if (s0 >= t0 && s1 >= t1) {
        s0 -= t0, s1 -= t1;
        cout << t;
    }
    if (r0 && r1) {
        while (s0 >= r0 && s1 >= r1) {
            s0 -= r0, s1 -= r1;
            cout << r;
        }
    }
    while (s0--) cout << '0';
    while (s1--) cout << '1';
    return 0;
}

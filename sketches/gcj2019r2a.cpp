//@ Including Header
#include <cul/std>

/**
 *  Name : gcj2019r2a.cpp
 *  Date : 2019/5/18 22:04
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

struct fraction {
    i64 a, b;

    bool operator<(const fraction &other) const {
        bool neg = (b < 0) ^(other.b < 0);
        i64 t = a * other.b - b * other.a;
        return neg ? t > 0 : t < 0;
    }
};

std::ostream &operator<<(std::ostream &os, const fraction &p) {
    os << "(" << p.a << "," << p.b << ")";
    return os;
}

const i32 N = 300;
const i64 M = (i64)1e9;
i64 x[N], y[N];

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        i32 n;
        cin >> n;
        rep(i, 0, n) cin >> x[i] >> y[i];

        fraction bound = {M, M + 1};
        fraction left = {0, 1}, right = bound;

        int ans = 0;
        rep(i, 1, n) {
            auto a = x[i - 1];
            auto b = y[i - 1];
            auto c = x[i];
            auto d = y[i];
            if (b - d == 0) {
                if (a > c) break;
                ans = i;
            } else if (a - c == 0) {
                if (b > d) break;
                ans = i;
            } else {
                fraction frac = {c - a, b - d};
                cout << frac << " " << b - d << endl;
//                if (bound < frac) break;
                if (b - d < 0) {
                    if (left < frac) left = frac;
                } else {
                    if (frac < right) right = frac;
                }
                cout << left << " " << right << endl;
                if (right < left) break;
                ans = i;
            }
        }
        cout << ans + 1 << endl;
    }
    return 0;
}

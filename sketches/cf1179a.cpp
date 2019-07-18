//@ Including Header
#include <cul/std>

/**
 *  Name : cf1179a.cpp
 *  Date : 2019/6/22 1:04
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 1e5;
i32 a[N], b[N], c[N * 2];

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i32 n, q;
    cin >> n >> q;
    rep(i, 0, n) cin >> a[i];

    b[0] = a[0];
    rep(i, 1, n) b[i] = max(b[i - 1], a[i]);

    i32 max_index = max_element(a, a + n) - a;
    i32 max_value = a[max_index];

    rep(i, 0, n) c[i] = a[i];
    i32 l = 0, r = n;
    while (c[l] != max_value) {
        i32 mi = min(c[l], c[l + 1]);
        i32 ma = max(c[l], c[l + 1]);
        c[++l] = ma;
        c[r++] = mi;
    }

    while (q--) {
        i64 x;
        cin >> x;
        if (x <= max_index) {
            cout << b[x - 1] << " " << a[x] << endl;
        } else {
            x -= max_index + 1;
            x %= n - 1;
            cout << c[l] << " " << c[l + 1 + x] << endl;
        }
    }

    return 0;
}

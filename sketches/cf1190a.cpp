//@ Including Header
#include <cul/std>

/**
 *  Name : cf1190a.cpp
 *  Date : 2019/7/12 22:31
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 n; cin >> n;
    i32 m; cin >> m;
    i64 k; cin >> k;

    vector<i64> p; p.reserve(m);
    rep(i, 0, m) {
        i64 x; cin >> x;
        p.push_back(x - 1);
    }
    sort(p.begin(), p.end());

    i32 ans = 0;
    i32 l = 0;
    while (l < m) {
        i32 r = l;
        while (r < m - 1) {
            i32 q = r + 1;
            i64 rp = (p[r] - l) / k;
            i64 qp = (p[q] - l) / k;
            if (rp != qp) break;
            r = q;
        }
        ++ans;
        l = r + 1;
    }
    cout << ans << endl;

    return 0;
}

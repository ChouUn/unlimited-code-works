//@ Including Header
#include <cul/std>

/**
 *  Name : jsk2019r13a.cpp
 *  Date : 2019/6/1 15:59
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

int solve(const vi &a) {
    int n = a.size();
    vi dp(n, 1);
    rep(i, 1, n) {
        rep(j, 0, i) if (a[j] < a[i]) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;
    vi a;
    a.reserve(n);
    rep(i, 0, n) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    int tot = solve(a);

    int ans = 0;
    vi b;
    b.reserve(n - 1);
    rep(k, 0, n) {
        b.clear();
        rep(i, 0, n) if (i != k) b.push_back(a[i]);
        if (solve(b) < tot) ++ans;
    }
    cout << ans << endl;

    return 0;
}

//@ Including Header
#include <csl_std.h>

/**
 *  Name : d.cpp
 *  Date : 2019/3/24 13:49
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

namespace prime {
    std::vector< std::size_t > div, prm;
    void build(std::size_t n) {
        div.assign(n, 0), prm.clear(), prm.reserve(n >> 3);
        for (std::size_t i = 2; i < n; ++i) {
            if (!div[i]) div[i] = i, prm.push_back(i);
            for (std::size_t j = 0, m = prm.size(), k; j < m; ++j) {
                if ((double)i * prm[j] >= n) break;
                div[k = i * prm[j]] = prm[j];
                if (i % prm[j] == 0) {
                    break;
                }
            }
        }
    }
} // namespace prime

const int N = static_cast<const int>(sqrt(1e9) + 10);

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    prime::build((size_t) N);
    ll a, c; cin >> a >> c;
    int b = 1;
    per(i, 0, (int)prime::prm.size()) {
        ll p = prime::prm[i];

        ll q = 1;
        while (c % (q * p) == 0) q *= p;
        c /= q;

        ll r = 1;
        while (a % (r * p) == 0) r *= p;
        a /= r;

        if (q > r) b *= q;
        else if (q == r) continue;
        else { // q < r
            cout << "NO SOLUTION" << endl;
            exit(0);
        }
    }
    if (c > a) b *= c;
    else if (c == a);
    else { // c < a
        cout << "NO SOLUTION" << endl;
        exit(0);
    }
    cout << b << endl;

    return 0;
}

//@ Anti Stack Overflow
// #define ANTI_STACK_OVERFLOW
int main() {
#ifdef ANTI_STACK_OVERFLOW
    std::size_t size = 16 << 20; // KB(<<10), MB(<<20).
    char* data = (char*)malloc(size) + size;
#if __x86_64__ || __ppc64__ || _WIN64
    __asm__ __volatile__("movq %0, %%rsp \n pushq $_exit \n" ::"r"(data));
#else
    __asm__ __volatile__("movl %0, %%esp \n pushl $_exit \n" ::"r"(data));
#endif
#endif
    exit(Main());
}

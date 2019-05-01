//@ Including Header
#include <csl_std.h>
#include <csl_math.h>
#include <seg_tree.h>

/**
 *  Name : e.cpp
 *  Date : 2019/3/24 14:19
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int B = 32;
const ll M = static_cast<const ll>(1e9 + 7);

struct node {
    int bits[B] = {0};
};

struct add_node {
    node operator()(const node &p, const node &q) const {
        node res = node();
        rep(i, 0, B) res.bits[i] = p.bits[i] + q.bits[i];
        return res;
    }
};

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        int n, q;
        cin >> n >> q;
        vector<node> a(static_cast<unsigned int>(n));
        rep(i, 0, n) {
            int m;
            cin >> m;
            rep(j, 0, B) a[i].bits[j] = (m >> j) & 1;
        }

        csl::seg_tree<node, add_node> seg;
        seg.build(a.begin(), a.end());

        while (q--) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto res = seg.query(static_cast<size_t>(l), static_cast<size_t>(r));

            ll ans = 0;
            rep(j, 0, B) {
                ll m = res.bits[j];
                m = csl::pow(1ll, 2ll, m, M);
                m = (m - 1 + M) % M;
                m = (m << j) % M;
                ans = (ans + m) % M;
            }
            cout << ans << endl;
        }
    }
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

//@ Including Header
#include <csl_std.h>

/**
 *  Name : cf1137b.cpp
 *  Date : 2019/3/16 17:27
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int B = 137;
const ll MOD = static_cast<const ll>(1e9 + 7);

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    string s, t; cin >> s >> t;

    set<int> p;
    ll x = 0;
    for (char i : t) {
        x = (x * B + i) % MOD;
        p.insert(static_cast<int &&>(x));
    }
    ll y = 1; x = 0;
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

//@ Including Header
#include <csl_std.h>

/**
 *  Name : b.cpp.cpp
 *  Date : 2019/3/24 13:11
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 110;
string s[N];

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    rep(i, 0, n) cin >> s[i];

    while (m--) {
        string t; cin >> t;
        vector<string> vs;
        rep(i, 0, n) {
            if (s[i].find(t) != -1) {
                vs.push_back(s[i]);
            }
        }
        if (vs.empty()) {
            cout << "_NULL_" << endl;
        } else {
            for (const auto &vsi : vs) {
                cout << vsi << ";";
            }
            cout << endl;
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

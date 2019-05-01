//@ Including Header
#include <csl_std.h>

/**
 *  Name : a.cpp
 *  Date : 2019/3/24 13:00
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 1010;
bool a[N];

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    a[1] = true;
    rep(i, 2, N) if (!a[i]) {
        for (int j = i * i; j <= N; j += i) a[j] = true;
    }

    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        int n; cin >> n;
        int ans = 4;
        rep(i, 2, N) if (!a[i]) {
            int res = i * i;
            if (res > n) break;
            ans = res;
        }
        cout << ans << endl;
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

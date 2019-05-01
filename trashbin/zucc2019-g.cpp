//@ Including Header
#include <csl_std.h>

/**
 *  Name : g.cpp
 *  Date : 2019/3/24 15:18
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const int N = 14;
vector<vector<string>> l = {
        {"1w", "1w", "1w"},
        {"2w", "2w", "2w"},
        {"3w", "3w", "3w"},
        {"4w", "4w", "4w"},
        {"5w", "5w", "5w"},
        {"6w", "6w", "6w"},
        {"7w", "7w", "7w"},
        {"8w", "8w", "8w"},
        {"9w", "9w", "9w"},

        {"1t", "1t", "1t"},
        {"2t", "2t", "2t"},
        {"3t", "3t", "3t"},
        {"4t", "4t", "4t"},
        {"5t", "5t", "5t"},
        {"6t", "6t", "6t"},
        {"7t", "7t", "7t"},
        {"8t", "8t", "8t"},
        {"9t", "9t", "9t"},

        {"1s", "1s", "1s"},
        {"2s", "2s", "2s"},
        {"3s", "3s", "3s"},
        {"4s", "4s", "4s"},
        {"5s", "5s", "5s"},
        {"6s", "6s", "6s"},
        {"7s", "7s", "7s"},
        {"8s", "8s", "8s"},
        {"9s", "9s", "9s"},

        {"dong", "dong", "dong"},
        {"nan", "nan", "nan"},
        {"xi", "xi", "xi"},
        {"bei", "bei", "bei"},
        {"zhong", "zhong", "zhong"},
        {"fa", "fa", "fa"},
        {"bai", "bai", "bai"},

        {"1w", "2w", "3w"},
        {"2w", "3w", "4w"},
        {"3w", "4w", "5w"},
        {"4w", "5w", "6w"},
        {"5w", "6w", "7w"},
        {"6w", "7w", "8w"},
        {"7w", "8w", "9w"},

        {"1t", "2t", "3t"},
        {"2t", "3t", "4t"},
        {"3t", "4t", "5t"},
        {"4t", "5t", "6t"},
        {"5t", "6t", "7t"},
        {"6t", "7t", "8t"},
        {"7t", "8t", "9t"},

        {"1s", "2s", "3s"},
        {"2s", "3s", "4s"},
        {"3s", "4s", "5s"},
        {"4s", "5s", "6s"},
        {"5s", "6s", "7s"},
        {"6s", "7s", "8s"},
        {"7s", "8s", "9s"},
};

map<string, int> mp;
bool dfs(int p, int m) {
    if (m == 4) {
        for (const auto &it : mp) if (it.second) return it.second == 2;
        return false;
    }

    rep(i, p, (int)l.size()) {
        bool fail = false;
        for (const auto &s : l[i]) if (--mp[s] < 0) fail = true;
        if (!fail) if (dfs(i, m + 1)) return true;
        for (const auto &s : l[i]) ++mp[s];
    }
    return false;
}

//@ Main Function
int Main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        mp.clear();
        rep(i, 0, N) {
            string s;
            cin >> s;
            ++mp[s];
        }

        bool fail = false;
        for (const auto &it : mp) if (it.second > 4) fail = true;
        if (fail) {
            cout << "Seriously?" << endl;
            continue;
        }

        bool ans = dfs(0, 0);
        cout << (ans ? "HuLe!" : "Sorry.") << endl;
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

//@ Including Header
// Name : ChouUn's Standard Library 纸农の标准库
// Copyright : fateud.com
#ifndef CSL_STD_H_
#define CSL_STD_H_ 20151122L
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair< int, int > pii;
typedef std::vector< int > vi;
typedef std::vector< vi > vvi;
typedef std::vector< pii > vpii;

#define rep(i,a,b) for(auto i=a,i##_n=b;i<i##_n;++i)
#define per(i,a,b) for(auto i=b,i##_n=a;i-->i##_n;)
#define endl '\n'

#endif /* CSL_STD_H_ */


/**
 *  Name : gcj2019qra.cpp
 *  Date : 2019/4/06 13:41
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */
s
//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for(std::cin >> _; _; --_, ++__) {
        std::cout << "Case #" << __ << ": ";
        string s;
        cin >> s;

        string ans1, ans2;
        for (auto ch : s) {
            int m = ch - '0';
            switch (m) {
                case 4:
                case 5:
                    ans1.push_back('0' + m / 2);
                    ans2.push_back('0' + m - m / 2);
                    break;
                case 0:
                case 1:
                    ans1.push_back('0' + m);
                    if (!ans2.empty()) ans2.push_back('0');
                    break;
                default:
                    ans1.push_back('1');
                    ans2.push_back('0' + m - 1);
                    break;
            }
        }
        cout << ans1 << " " << ans2 << endl;
    }
    return 0;
}


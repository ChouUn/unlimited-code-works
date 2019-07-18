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
 *  Name : gcj2019qrb.cpp
 *  Date : 2019/4/06 14:04
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for(std::cin >> _; _; --_, ++__) {
        std::cout << "Case #" << __ << ": ";
        int n;
        string s;
        cin >> n >> s;
        for (auto ch : s) cout << (ch == 'E' ? 'S' : 'E');
        cout << endl;
    }
    return 0;
}


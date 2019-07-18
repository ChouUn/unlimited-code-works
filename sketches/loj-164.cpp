//@ Including Header
#include <cul/std>
#include <numerics/BigInt>

/**
 *  Name : loj-164.cpp
 *  Date : 2019/7/10 19:51
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

using cul::BigInt;

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BigInt a, b; cin >> a >>b;
    cout << a / b << endl;

    return 0;
}

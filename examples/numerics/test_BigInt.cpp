//@ Including Header
#include <cul/std>
#include <numerics/BigInt>

/**
 *  Name : test.cpp
 *  Date : 2019/6/8 17:17
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    stringstream ss;
    string s;

    cul::BigInt a(12345678987654321);
    cul::BigInt b(98765432123456789);
    cul::BigInt c("-98765432123456789");

    assert(c.to_string() == "-98765432123456789");

    assert(a / b == 0);
    assert(a % b == a);
    assert(b / a == 8);
    assert(b % a == 222222221);

    assert(b / c == -1);
    assert(b % c == 0);
    assert(c / b == -1);
    assert(c % b == 0);

    auto x = a + b;
    cout << x << endl;
    assert(x.to_string() == "111111111111111110");

    auto y = a * b;
    cout << y << endl;
    assert(y.to_string() == "1219326320073159566072245112635269");
    assert(y / a == b);
    assert(y / b == a);

    auto z = b + c;
    cout << z << endl;
    assert(z.to_string() == "0");

    return 0;
}

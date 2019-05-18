//@ Including Header
#include <cul/std>

/**
 *  Name : cf1137d.cpp
 *  Date : 2019/5/18 3:30
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

i32 get_next() {
    int n;
    cin >> n;
    rep(i, 0, n) {
        string s;
        cin >> s;
    }
    return n;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    do {
        cout << "next 0 1" << endl;
        get_next();
        cout << "next 0" << endl;
    } while (get_next() == 3);
    do {
        cout << "next 0 1 2 3 4 5 6 7 8 9" << endl;
    } while (get_next() != 1);
    cout << "done" << endl;

    return 0;
}

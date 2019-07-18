//@ Including Header
#include <cul/std>
#include <tree/splay_tree>

/**
 *  Name : loj-104.cpp
 *  Date : 2019-07-06 02:29
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

typedef cul::splay_tree<int> splay;

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    splay sp;

    int n;
    cin >> n;

    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            sp.insert(x);
        } else if (op == 2) {
            sp.erase(x);
        } else if (op == 3) {
            cout << sp.rank(x) << endl;
        } else if (op == 4) {
            cout << sp.kth(x)->key() << endl;
        } else if (op == 5) {
            cout << sp.lower_bound(x)->pred()->key() << endl;
        } else if (op == 6) {
            cout << sp.upper_bound(x)->key() << endl;
        }
    }

    return 0;
}

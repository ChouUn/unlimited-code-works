//@ Including Header
#include <cul/std>
#include <tree/splay_tree>

/**
 *  Name : loj-105.cpp
 *  Date : 2019/7/19 5:52
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

struct aux {
    int val;
    bool rev;
};

typedef cul::splay_tree<int, aux> splay;
using cul::NodeRelation::L;
using cul::NodeRelation::R;
using cul::splay_tree_node;

namespace cul {
    template <>
    void splay_tree_node_push(splay_tree_node<int, aux> *__node) {
        if (__node->value().rev) {
            std::swap(__node->_children[L], __node->_children[R]);

            if (__node->_child(L)) { __node->_child(L)->value().rev ^= __node->value().rev; }
            if (__node->_child(R)) { __node->_child(R)->value().rev ^= __node->value().rev; }

            __node->value().rev = 0;
        }
    }
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i32 n, m;
    cin >> n >> m;

    splay sp;
    rep(i, 1, n + 1) { sp.insert(i, aux { i, false }); }

    while (m--) {
        i32 l, r;
        cin >> l >> r;
        sp.select(l, r + 1)->value().rev ^= 1;
    }

    bool fst = true;
    for (auto it = sp.begin(); it != sp.end(); it = it->succ()) {
        if (fst) { fst = false; } else { cout << ' '; }
        cout << it->value().val;
    }
    cout << endl;

    return 0;
}

//@ Including Header
#include <cul/std>
#include <cul/algorithm>
#include <tree/link_cut_tree>

/**
 *  Name : loj-10138.cpp
 *  Date : 2019/7/27 17:23
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

struct node {
    int val;
    int sum;
    int max;
};

namespace cul {
    template <>
    void link_cut_tree_node_pull(link_cut_tree_node<node> *__node) {
        __node->_value.sum = __node->_value.val;
        if (__node->_children[L]) { __node->_value.sum += __node->_children[L]->_value.sum; }
        if (__node->_children[R]) { __node->_value.sum += __node->_children[R]->_value.sum; }

        __node->_value.max = __node->_value.val;
        if (__node->_children[L]) { update_max(__node->_value.max, __node->_children[L]->_value.max); }
        if (__node->_children[R]) { update_max(__node->_value.max, __node->_children[R]->_value.max); }
    }
}

typedef cul::link_cut_tree<node> lct;
typedef typename cul::link_cut_tree<node>::node_type lct_node;

const int N = 3e4;
lct_node *nodes[N];
int u[N], v[N];

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;
    rep(i, 0, n - 1) { cin >> u[i] >> v[i]; --u[i], --v[i]; }

    lct tree;
    rep(i, 0, n) {
        int w;
        cin >> w;
        nodes[i] = tree.insert(node { w, w, w });
    }
    rep(i, 0, n - 1) { tree.link(nodes[u[i]], nodes[v[i]]); }

    int m;
    cin >> m;
    while (m--) {
        string op;
        cin >> op;
        int a, b;
        cin >> a >> b;
        if (op == "QMAX") {
            --a, --b;
            nodes[a]->evert();
            nodes[b]->access();
            nodes[b]->splay();
            cout << nodes[b]->value().max << endl;
        } else if (op == "QSUM") {
            --a, --b;
            nodes[a]->evert();
            nodes[b]->access();
            nodes[b]->splay();
            cout << nodes[b]->value().sum << endl;
        } else {
            --a;
            nodes[a]->splay();
            nodes[a]->value().val = b;
            cul::link_cut_tree_node_pull(nodes[a]);
        }
    }

    return 0;
}

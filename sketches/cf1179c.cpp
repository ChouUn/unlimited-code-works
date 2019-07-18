//@ Including Header
#include <cul/std>

/**
 *  Name : cf1179c.cpp
 *  Date : 2019/6/22 1:45
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

const i32 N = 3e5;
const i32 M = 3e5;

i32 a[N], b[M];

set<pii> a_rest;
set<pii> b_rest;
map<i32, i32> a_to_b;
map<i32, i32> b_to_a;

void connect(i32 ai, i32 bi) {
    cout << "connect: " << ai << " " << bi << endl;
    a_rest.erase(pii(a[ai], ai));
    b_rest.erase(pii(b[bi], bi));
    a_to_b[ai] = bi;
    b_to_a[bi] = ai;
}

void deconnect(i32 ai, i32 bi) {
    cout << "deconnect: " << ai << " " << bi << endl;
    a_to_b.erase(ai);
    b_to_a.erase(bi);
    a_rest.insert(pii(a[ai], ai));
    b_rest.insert(pii(b[bi], bi));
}

void try_a_to_b(i32 ai) {
    auto it = b_rest.lower_bound(pii(a[ai], 0));
    if (it != b_rest.end()) {
        i32 bi = it->second;
        connect(ai, bi);
    } else {

    }
}

void try_b_to_a(i32 bi) {
    auto it = a_rest.upper_bound(pii(b[bi], 0));
    if (it == a_rest.begin()) return;

    i32 ai = (--it)->second;
    connect(ai, bi);
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, m) cin >> b[i];

    rep(i, 0, n) a_rest.insert(pii(a[i], i));
    rep(i, 0, m) b_rest.insert(pii(b[i], i));
    rep(i, 0, n) try_a_to_b(i);

    i32 q;
    cin >> q;
    while (q--) {
        i32 op, i, x;
        cin >> op >> i >> x;
        --i;

        if (op == 1) {
            i32 ai = i;
            auto it = a_to_b.find(ai);
            if (it == a_to_b.end()) {
                a_rest.erase(pii(a[ai], ai));
                a[ai] = x;
                a_rest.insert(pii(a[ai], ai));
            } else {
                i32 bi = it->second;
                a[ai] = x;
                deconnect(ai, bi);
                try_a_to_b(ai);
                try_b_to_a(bi);
            }
        } else {
            i32 bi = i;
            auto it = b_to_a.find(bi);
            if (it == b_to_a.end()) {
                b_rest.erase(pii(b[bi], bi));
                b[bi] = x;
                b_rest.insert(pii(b[bi], bi));
            } else {
                i32 ai = it->second;
                b[bi] = x;
                deconnect(ai, bi);
                try_a_to_b(ai);
                try_b_to_a(bi);
            }
        }

        if (a_rest.empty()) {
            cout << -1 << endl;
        } else {
            cout << a_rest.rbegin()->first << endl;
        }
    }

    return 0;
}

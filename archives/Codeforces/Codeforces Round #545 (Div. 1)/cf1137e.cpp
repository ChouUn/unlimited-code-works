//@ Including Header
#include <cul/std>

/**
 *  Name : cf1137e.cpp
 *  Date : 2019/5/19 13:37
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

namespace hull {
    struct node {
        i64 x, y;

        node operator-(const node &other) const {
            return {x - other.x, y - other.y};
        }

        bool operator<(const node &other) const {
            return (ld)other.x * y < (ld)x * other.y;
        }
    };

    std::ostream &operator<<(std::ostream &os, const node &p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

    std::vector<node> sta;

    void insert(const node &p) {
        while (sta.size() > 1) {
            auto it = sta.end();
            node &q = *--it;
            node &r = *--it;
            node pp = p - r, qp = q - r;
            if (!(qp < pp))
                sta.pop_back();
            else
                break;
        }

        sta.push_back(p);
    }
};

using hull::node;
using hull::sta;

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 n;
    int m;
    cin >> n >> m;

    i64 b = 0, s = 0;
    sta = {{1, 0},};
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            i64 k;
            cin >> k;
            n += k;
            sta = {{1, 0},};
            b = 0, s = 0;
        } else if (op == 2) {
            i64 k;
            cin >> k;
            node p = {n + 1, -(b + n * s)};
            hull::insert(p);
            n += k;
        } else {
            i64 db, ds;
            cin >> db >> ds;
            b += db, s += ds;
        }

        while (hull::sta.size() > 1) {
            auto it = sta.end();
            node &q = *--it;
            node &r = *--it;
            node pp = {1, -s};
            node qp = q - r;
            if (!(qp < pp))
                sta.pop_back();
            else
                break;
        }
        node &p = sta.back();
        cout << p.x << " " << p.y + b + (p.x - 1) * s << "\n";
    }

    return 0;
}

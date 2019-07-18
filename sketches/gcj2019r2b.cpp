//@ Including Header
#include <cul/std>

/**
 *  Name : gcj2019r2b.cpp
 *  Date : 2019/5/18 23:33
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

typedef pair<double, int> pdi;

set<int> read_set() {
    int m;
    cin >> m;
    assert(m >= 0);

    set<int> s;
    rep(j, 0, m) {
        int x;
        cin >> x;
        s.insert(x);
    }
    return s;
}

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        //std::cout << "Case #" << __ << ": ";
        rep(i, 1, 21) {
            int n;
            cin >> n;
            assert(n == i);

            cout << i << " " << 100 << endl;
            cout.flush();
            clog << i << " " << 100 << endl;
            clog.flush();
        }

        vector<set<int>> vs;
        priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
        rep(i, 21, 41) {
            int n;
            cin >> n;
            assert(n == i);

            cout << i - 20 << " " << 0 << endl;
            cout.flush();
            clog << i - 20 << " " << 0 << endl;
            clog.flush();

            set<int> s = read_set();
            pq.emplace(s.size() - i / 20., vs.size());
            vs.push_back(s);
        }

        for (int i = 41; i < 101; i += 3) {
            int n;
            cin >> n;
            assert(n == i);

            auto p = pq.top();
            pq.pop();

            auto q = pq.top();
            pq.pop();

            int j = q.second;
            auto &s = vs[j];
            int x = 1;
            while (s.find(x) != s.end()) ++x;
            cout << q.second + 1 << " " << x << endl;
            cout.flush();
            clog << q.second + 1 << " " << x << endl;
            clog.flush();

            cin >> n;
            assert(n == i + 1);

            cout << p.second + 1 << " " << 0 << endl;
            cout.flush();
            clog << p.second + 1 << " " << 0 << endl;
            clog.flush();
            auto ps = read_set();
            pq.emplace(ps.size() - (i + 1) / 20., p.second);
            vs[p.second] = ps;

            cin >> n;
            assert(n == i + 2);

            if (i + 2 != 100) {
                cout << q.second + 1 << " " << 0 << endl;
                cout.flush();
                clog << q.second + 1 << " " << 0 << endl;
                clog.flush();
                auto qs = read_set();
                pq.emplace(qs.size() - (i + 2) / 20., q.second);
                vs[q.second] = qs;
            } else {
                cout << q.second + 1 << " " << 100 << endl;
                cout.flush();
                clog << q.second + 1 << " " << 100 << endl;
                clog.flush();
            }
        }

//        pq.pop();
//        rep(i, 41, 61) {
//            int n;
//            cin >> n;
//            assert(n == i);
//
//            pii p = pq.top();
//            pq.pop();
//
//            int j = p.second;
//            auto &s = vs[j];
//
//            int q = 1;
//            while (s.find(q) != s.end()) ++q;
//            s.insert(q);
//            pq.emplace(p.first + 1, j);
//
//            cout << j + 1 << " " << q << endl;
//            cout.flush();
////            clog << j + 1 << " " << q << endl;
////            clog.flush();
//        }
//
//        vs.clear();
//        while (!pq.empty()) pq.pop();
//        rep(i, 61, 81) {
//            int n;
//            cin >> n;
//            assert(n == i);
//
//            cout << i - 60 << " " << 0 << endl;
//            cout.flush();
////            clog << i - 60 << " " << 0 << endl;
////            clog.flush();
//
//            int m;
//            cin >> m;
//            assert(m >= 0);
//
//            set<int> s;
//            rep(j, 0, m) {
//                int x;
//                cin >> x;
//                s.insert(x);
//            }
//            pq.emplace(s.size() + (i - 60) / 20., vs.size());
//            vs.push_back(s);
//        }
//
//        pq.pop();
//        rep(i, 81, 101) {
//            int n;
//            cin >> n;
//            assert(n == i);
//
//            pii p = pq.top();
//            pq.pop();
//
//            int j = p.second;
//            auto &s = vs[j];
//
//            int q = 1;
//            while (s.find(q) != s.end()) ++q;
//            if (i == 100) q = 100;
//            s.insert(q);
//            pq.emplace(p.first + 1, j);
//
//            cout << j + 1 << " " << q << endl;
//            cout.flush();
////            clog << j + 1 << " " << q << endl;
////            clog.flush();
//        }
    }
    return 0;
}

//@ Including Header
#include <cul/std>

// Name : Fenwick Tree 树状数组
// AKA : Binary Indexed Tree 二分索引树
// Copyright : fateud.com

#ifndef FENWICK_H_
#define FENWICK_H_ 20150928L

#include <vector>
#include <functional>

#ifndef lowbit
#define lowbit(x) ((x)&-(x))
#endif

namespace csl {
    template <typename _Tp, typename _Op = std::plus< _Tp >>
    struct fenwick_tree {
        typedef _Tp value_type;
        typedef std::size_t size_type;
        std::vector< value_type > data;
        fenwick_tree() : func() {
        }
        inline void build(size_type p_size) {
            data.assign(p_size + 1, 0);
        }
        void build(const value_type* p_data, size_type p_size) {
            data.resize(p_size + 1);
            for (int i = 1; i <= p_size; ++i)
                data[i] = p_data[i - 1];
            for (int i = 1, j; i <= p_size; ++i)
                if ((j = i + lowbit(i)) <= p_size) data[j] = func(data[j], data[i]);
        }
        inline size_type size() const {
            return data.size();
        }
        value_type query(size_type __x, value_type __res = value_type()) const {
            for (; __x > 0; __x -= lowbit(__x))
                __res = func(__res, data[__x]);
            return __res;
        }
        void update(size_type __x, const value_type& __v) {
            for (; __x < data.size(); __x += lowbit(__x))
                data[__x] = func(data[__x], __v);
        }
    private:
        const _Op func;
    };

    std::size_t search(fenwick_tree< int >& f, int x) {
        if (f.query(f.size() - 1) < x) return -1;
        std::size_t res = 0;
        for (int i = 1 << 20; i > 0 && x > 0; i >>= 1) {
            if (res + i >= f.size()) continue;
            if (x <= f.data[res + i]) continue;
            x -= f.data[res += i];
        }
        return res + 1;
    }

} // namespace csl

#endif /* FENWICK_H_ */

// Name : Discretization 离散化
// Copyright : fateud.com
#ifndef DISCRETE_H_
#define DISCRETE_H_ 20150926L
#include <vector>
#include <algorithm>
namespace csl {
    template <typename _Tp>
    struct discrete {
        typedef std::size_t size_type;

        void build() {
            std::sort(data.begin(), data.end());
            data.resize(std::unique(data.begin(), data.end()) - data.begin());
        }
        inline void clear() {
            data.clear();
        }
        inline size_type size() const {
            return data.size();
        }
        inline void reserve(size_type __n) {
            data.reserve(__n);
        }

        inline size_type query(const _Tp& __x) const {
            return std::lower_bound(data.begin(), data.end(), __x) - data.begin();
        }
        _Tp operator [](size_type __x) const {
            return data[__x];
        }
        inline void insert(_Tp __x) {
            data.push_back(__x);
        }
        template <typename _InputIterator>
        inline void insert(_InputIterator first, _InputIterator last) {
            data.insert(data.end(), first, last);
        }

        std::vector< _Tp > data;
    };
} // namespace csl

#endif /* DISCRETE_H_ */


/**
 *  Name : cf1190d.cpp
 *  Date : 2019/7/12 22:57
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; cin >> n;
    vpii ps;
    rep(i, 0, n) {
        int x, y;
        cin >> x >> y;
        ps.emplace_back(x, y);
    }

    csl::discrete<int> xs, ys;
    rep(i, 0, n) {
        xs.insert(ps[i].first);
        ys.insert(ps[i].second);
    }
    xs.build();
    ys.build();
    rep(i, 0, n) {
        ps[i].first = xs.query(ps[i].first) + 1;
        ps[i].second = ys.query(ps[i].second) + 1;
    }
    sort(ps.begin(), ps.end(), [](const pii& a, const pii& b) {
        return a.second > b.second;
    });

    i64 ans = 0;
    csl::fenwick_tree<int> ft;
    ft.build(n + 1);

    ps.push_back(pii(0, 0));
    vpii qs;
    rep(i, 0, n + 1) {
        if (i == 0 || ps[i].second == ps[i - 1].second) {
            qs.push_back(ps[i]);
        } else {
            i32 nq = qs.size();

            vi v;
            i64 sold = 0, snew = 0;
            for (auto &p : qs) {
                i32 x = p.first;
                i32 sx = ft.query(x) - ft.query(x - 1);
                v.push_back(sx);
                if (sx) sold += 1;
                else snew += 1;
            }
            rep(j, 0, nq) {
                auto p = qs[j];
                i32 x = p.first;
                i32 sx = v[j];
                if (!sx) ft.update(x, 1);
            }
            i32 sn = ft.query(n);
            rep(j, 0, nq) {
                auto p = qs[j];
                i32 x = p.first;
                i32 sx = v[j];
                if (!sx) {
                    ans += sn;
                } else {
                    ans += 1;
                }
                i64 l = ft.query(x - 1) - j;
                i64 r = ft.query(n) - ft.query(x) - (nq - j - 1);
                ans += l * r;
            }
            ans -= (snew - 1) * snew / 2;
            ans += (sold - 1) * sold / 2;

//            for (auto &p : qs) {
//                i32 x = p.first;
//                i32 sx = ft.query(x) - ft.query(x - 1);
//                if (!sx) {
//                    ft.update(x, 1);
//                    ans += ft.query(n);
//                } else {
//                    cout << ft.query(n) << " " << cnt << endl;
//                    ans += ft.query(n) - cnt;
//                }
//                {
//                    i64 l = ft.query(x - 1) - cnt;
//                    i64 r = ft.query(n) - ft.query(x) - (old - cnt - sx);
//
//                    ans += l * r;
//                }
//                cnt += sx;
//            }

            qs.clear();
            qs.push_back(ps[i]);
//            cout << ans << endl;
        }
    }

//    i32 last_y = n + 1, cnt1 = 0, cnt2 = 0;
//    rep(i, 0, n) {
//        i32 x = ps[i].first;
//        i32 y = ps[i].second;
//
//        i32 sx = ft.query(x) - ft.query(x - 1);
//        if (!sx) {
//            ft.update(x, 1);
//            ans += ft.query(n);
//        } else {
//            if (y != last_y) {
//                ans += ft.query(n);
//            } else {
//                ans += ft.query(n) - cnt1;
//            }
//        }
//        {
//            i64 l = ft.query(x - 1);
//            i64 r = ft.query(n) - ft.query(x);
//            if (y == last_y) l -= cnt2;
//            ans += l * r;
//        }
//
//        if (y != last_y) last_y = y, cnt1 = 0;
//        if (sx) cnt1 += 1;
//        cnt2 += 1;
//    }
    cout << ans << endl;

    return 0;
}

//@ Including Header
// Name : ChouUn's Standard Library 纸农の标准库
// Copyright : fateud.com
#ifndef CSL_STD_H_
#define CSL_STD_H_ 20151122L

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<pii> vpii;

#define rep(i, a, b) for(auto i=a,i##_n=b;i<i##_n;++i)
#define per(i, a, b) for(auto i=b,i##_n=a;i-->i##_n;)
#define endl '\n'

#endif /* CSL_STD_H_ */

// Name : BigDec 高精度自然数
// Copyright : fateud.com
#ifndef BIGDEC_H_
#define BIGDEC_H_ 20160318L
#include <cstdint>
#include <cstring>
#include <iomanip>
namespace csl {
    template <typename _Tp, int _Sz>
    class array {
    private:
        _Tp _data[_Sz];
        int _size;
    public:
        array() :
                _size() {
        }
        array(int n, _Tp x = _Tp()) :
                _size(n) {
            while (n > 0)
                _data[--n] = x;
        }
    public:
        inline _Tp* data() {
            return _data;
        }
        inline const _Tp* data() const {
            return _data;
        }
        inline int size() const {
            return _size;
        }
        inline void clear() {
            _size = 0;
        }
        inline _Tp& operator [](int x) {
            return _data[x];
        }
        inline const _Tp& operator [](int x) const {
            return _data[x];
        }
        inline _Tp& at(int x) {
            return _data[x];
        }
        inline void resize(int x) {
            if (x <= _size)
                _size = x;
            else
                while (_size < x)
                    _data[_size++] = _Tp();
        }
        inline void push_back(_Tp x) {
            _data[_size++] = x;
        }
        inline void pop_back() {
            --_size;
        }
    };
    // class array

    template <typename _Sequence = csl::array< std::uint32_t, 50 > >
    class BigDec {
    public:
        typedef std::int32_t int32;
        typedef std::uint32_t uint32;
        typedef std::int64_t int64;
        typedef std::uint64_t uint64;
        typedef _Sequence container;
        typedef BigDec< _Sequence > _Self;
        static int32 Bit, Base;
        BigDec() :
                _bits(1, 0) {
        }
        BigDec(int32 value) {
            split(_bits, value);
        }
        BigDec(uint32 value) {
            split(_bits, value);
        }
        BigDec(int64 value) {
            split(_bits, value);
        }
        BigDec(uint64 value) {
            split(_bits, value);
        }
        BigDec(const container& value) :
                _bits(value) {
        }
        BigDec(container&& value) :
                _bits(std::move(value)) {
        }
        explicit BigDec(const char *p) {
            int n = strlen(p);
            _bits.resize((n - 1) / Bit + 1);
            for (int i = n, j = 0, k = 1; i > 0; --i) {
                _bits[j] += (p[i - 1] - '0') * k;
                if ((k *= 10) == Base) k = 1, ++j;
            }
        }
        inline uint32* data() {
            return _bits.data();
        }
        inline const uint32* data() const {
            return _bits.data();
        }
        inline int32 size() const {
            return _bits.size();
        }
        inline _Self& operator +=(const _Self& value) {
            AddSelf(_bits, value._bits);
            return *this;
        }
        inline _Self& operator -=(const _Self& value) {
            SubSelf(_bits, value._bits);
            return *this;
        }
        inline _Self& operator *=(const _Self& value) {
            _bits = Multi(_bits, value._bits);
            return *this;
        }
        inline _Self& operator /=(const _Self& value) {
            container r;
            Divide(_bits, value._bits, r);
            return _bits = std::move(r), *this;
        }
        inline _Self& operator %=(const _Self& value) {
            container r;
            Divide(_bits, value._bits, r);
            return *this;
        }
        inline _Self operator +(const _Self& b) const {
            return _Self(*this) += b;
        }
        inline _Self operator -(const _Self& b) const {
            return _Self(*this) -= b;
        }
        inline _Self operator *(const _Self& b) const {
            return _Self(*this) *= b;
        }
        inline _Self operator /(const _Self& b) const {
            return _Self(*this) /= b;
        }
        inline _Self operator %(const _Self& b) const {
            return _Self(*this) %= b;
        }
        inline bool operator ==(const _Self& b) const {
            return Compare(_bits, b._bits) == 0;
        }
        inline bool operator !=(const _Self& b) const {
            return Compare(_bits, b._bits) != 0;
        }
        inline bool operator <=(const _Self& b) const {
            return Compare(_bits, b._bits) <= 0;
        }
        inline bool operator >=(const _Self& b) const {
            return Compare(_bits, b._bits) >= 0;
        }
        inline bool operator <(const _Self& b) const {
            return Compare(_bits, b._bits) < 0;
        }
        inline bool operator >(const _Self& b) const {
            return Compare(_bits, b._bits) > 0;
        }
        inline bool operator !() const {
            return _bits.size() == 1 && _bits[0] == 0;
        }
        friend std::istream& operator >>(std::istream &i, _Self& n) {
            std::string s;
            return i >> s, n = _Self(s.data()), i;
        }
        friend std::ostream& operator <<(std::ostream &o, const _Self& n) {
            const container& b = n._bits;
            for (int i = b.size() - 1; i >= 0; i--)
                o << b[i] << std::setfill('0') << std::setw(Bit);
            return o << std::setfill(' ') << std::setw(0);
        }
    private:
        static void split(container& bits, uint64 value) {
            bits.clear();
            do {
                bits.push_back(value % Base), value /= Base;
            } while (value);
        }
        static void StripLeadingZero(container& bits) {
            int32 l = bits.size();
            while (l > 1 && bits[l - 1] == 0)
                --l;
            bits.resize(l);
        }

        static int Compare(const container& l, const container& r) {
            int32 ll = l.size(), rl = r.size();
            if (ll ^ rl) return (ll < rl) ? -1 : 1;
            for (int i = ll - 1; i >= 0; i--)
                if (l[i] ^ r[i]) return (l[i] < r[i]) ? -1 : 1;
            return 0;
        }

        static void AddSelf(container& l, const container& r) {
            int32 ll = l.size(), rl = r.size(), c = 0;
            if (ll < rl) l.resize(ll = rl);
            for (int32 i = 0; i < ll; ++i) {
                c = c + l[i];
                if (i < rl) c = c + r[i];
                if (c < Base)
                    l[i] = c, c = 0;
                else
                    l[i] = c - Base, c = 1;
            }
            if (c) l.push_back(c);
        }

        static void SubSelf(container& l, const container& r) {
            int32 ll = l.size(), rl = r.size(), c = 0;
            for (int32 i = 0; i < ll; ++i) {
                c = c + l[i];
                if (i < rl) c = c - r[i];
                if (c < 0)
                    l[i] = c + Base, c = -1;
                else
                    l[i] = c, c = 0;
            }
            StripLeadingZero(l);
        }

        static container Multi(const container& l, const container& r) {
            int32 ll = l.size(), rl = r.size(), bl = ll + rl;
            container b(bl);
            for (int32 i = 0; i < ll; i++) {
                int64 c = 0;
                for (int32 j = 0; j < rl || c > 0; j++) {
                    if (j < rl) c += (int64)l[i] * r[j];
                    int32 k = i + j;
                    if (k < bl)
                        c += b[k];
                    else
                        b.resize(bl = k + 1);
                    b[k] = c % Base, c /= Base;
                }
            }
            return StripLeadingZero(b), std::move(b);
        }

        static void Divide(container& l, const container& r, container& q) {
            if (Compare(l, r) == -1 && (q = container(1, 0), true)) return;
            int32 ll = l.size();
            q.resize(ll);
            container c(1, 0);
            for (int32 i = ll - 1; i >= 0; --i) {
                if (c.size() != 1 || c[0] != 0) {
                    c.resize(c.size() + 1);
                    for (int32 j = c.size() - 1; j > 0; --j)
                        c[j] = c[j - 1];
                }
                c[0] = l[i];
                int32 left = 0, right = Base - 1;
                while (left < right) {
                    int32 mid = (left + right + 1) / 2;
                    if (Compare(Multi(r, container(1, mid)), c) <= 0)
                        left = mid;
                    else
                        right = mid - 1;
                }
                q[i] = left, SubSelf(c, Multi(r, container(1, left)));
            }
            l = std::move(c), StripLeadingZero(q);
        }
    private:
        container _bits;
    };
    // class BigDec

    template <typename _Sequence> int BigDec< _Sequence >::Bit = 9;
    template <typename _Sequence> int BigDec< _Sequence >::Base = 1000000000;

} // namespace csl

#endif /* BIGDEC_H_ */


// Name : Mathematical Computation 数学计算
// Copyright : fateud.com

#ifndef CSL_MATH_H_
#define CSL_MATH_H_ 20160313L

#include <cmath>
#include <functional>
#include <vector>

#ifndef M_PI
#define M_E        2.71828182845904523536     // - e
#define M_LOG2E    1.44269504088896340736     // - log2(e)
#define M_LOG10E   0.434294481903251827651    // - log10(e)
#define M_LN2      0.693147180559945309417    // - ln(2)
#define M_LN10     2.30258509299404568402     // - ln(10)
#define M_PI       3.14159265358979323846     // - pi
#define M_1_PI     0.318309886183790671538    // - 1/pi
#define M_SQRT2    1.41421356237309504880     // - sqrt(2)
#define M_SQRT1_2  0.707106781186547524401    // - 1/sqrt(2)
#endif /* M_PI */

namespace csl {
    /*
     * greatest common divisor
     */
    template<typename T>
    inline T gcd(T a, T b) {
        for (T c = T(); !!b;)
            c = a % b, a = std::move(b), b = std::move(c);
        return a;
    }

    /*
     * extended Euclidean algorithm
     * solve ax + by = gcd(a,b)
     */
    template<typename T>
    T gcd(const T &a, const T &b, T &x, T &y) {
        if (!b) return x = 1, y = 0, a;
        T r = gcd(b, a % b, y, x);
        return y = y - a / b * x, r;
    }

    /**
     * least common multiple
     */
    template<typename T>
    inline T lcm(const T &a, const T &b) {
        return a / gcd(a, b) * b;
    }

    /**
     * divide and conquer algorithms (with modulo operation)
     */
    template<typename V, typename K, typename M, typename F1, typename F2>
    inline V dnc(V c, V n, K k, M m, const F1 &op1, const F2 &op2) {
        for (n = op2(n, m); !!k; n = op2(op1(n, n), m), k >>= 1)
            if (k & 1) c = op2(op1(c, n), m);
        return c;
    }

    /**
     * divide and conquer algorithms
     */
    template<typename V, typename K, typename F>
    inline V dnc(V c, V n, K k, const F &op) {
        for (; k; n = op(n, n), k >>= 1)
            if (k & 1) c = op(c, n);
        return c;
    }

    /**
     * return a * b (mod m)
     */
    template<typename V>
    inline V mul(V a, V b, const V m) {
        return dnc(V(), a, b, m, std::plus<V>(), std::modulus<V>());
    }

    /**
     * return c * n ^ k
     */
    template<typename V, typename K>
    inline V pow(V c, V n, const K k) {
        return dnc(c, n, k, std::multiplies<V>());
    }

    /**
     * return c * n ^ k (mod m)
     */
    template<typename V, typename K>
    inline V pow(V c, V n, const K k, V m) {
        return dnc(c, n, k, m, std::multiplies<V>(), std::modulus<V>());
    }

    /**
     * return 1 / x (mod m)
     */
    template<typename V>
    inline V inv(const V &x, const V &m) {
        V p, q;
        return gcd(x, m, p, q), (p % m + m) % m;
    }

    template<typename V>
    inline std::vector<V> divide(V x) {
        std::vector<V> res;
        if (x % 2 == 0) {
            res.push_back(2);
            while (x % 2 == 0)
                x >>= 1;
        }
        for (V i(3); i * i <= x; i += 2) {
            if (x % i) continue;
            res.push_back(i);
            while (x % i == 0)
                x /= i;
        }
        if (x != V(1)) res.push_back(x);
        return res;
    }

    /**
     * return Primitive Root of x about m
     */
    template<typename V>
    inline V root(const V &P) {
        std::vector<V> p = csl::divide(P - 1);
        for (V g = 2; g < P; ++g) {
            bool flag = true;
            for (auto i = p.begin(); i != p.end(); ++i)
                if (csl::pow(V(1), g, (P - 1) / *i, P) == 1) {
                    flag = false;
                    break;
                }
            if (flag) return g;
        }
        return -1;
    }

} // namespace csl

#endif /* CSL_MATH_H_ */


/**
 *  Name : gcj2019qrc.cpp
 *  Date : 2019/4/06 14:14
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */

typedef csl::BigDec<> BigInt;

#include <set>
#include <algorithm>

//@ Main Function
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int _, __ = 1;
    for (std::cin >> _; _; --_, ++__) {
        std::cout << "Case #" << __ << ": ";

        string s;
        int n;
        cin >> s >> n;

        vector<BigInt> vb;
        rep(i, 0, n) {
            BigInt b;
            cin >> b;
            vb.push_back(b);
        }

        vector<BigInt> vd;
        vd.push_back(vb[0] / csl::gcd(vb[0], vb[1]));
        rep(i, 0, n) vd.push_back(vb[i] / *vd.rbegin());

        vector<BigInt> vs = vd;
        sort(vs.begin(), vs.end());
        vs.resize(unique(vs.begin(), vs.end()) - vs.begin());

        for (const auto& d : vd) {
            auto idx = lower_bound(vs.begin(), vs.end(), d) - vs.begin();
            cout << (char)('A' + idx);
        }
        cout << endl;
    }
    return 0;
}

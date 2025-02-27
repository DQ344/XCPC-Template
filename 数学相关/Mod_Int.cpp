#include <bits/stdc++.h>

#define int  int32_t
#define Int  int64_t
#define uint uint32_t
#define uInt uint64_t

struct Barrett {
    uInt mod, inv_mod;
    
    constexpr Barrett(uInt _mod = 1)
    : mod(_mod), inv_mod((~0ULL) / _mod + 1) {}

    constexpr uInt opt(uInt a) const {
        const uInt b = (__uint128_t(a) * inv_mod) >> 64;
        if (a < b * mod)
            return a - b * mod + mod;
        else
            return a - b * mod;
    }
};

struct Mod_Int {
    static Barrett B;
    uInt val;

    constexpr Mod_Int()
    : val(0) {}
    
    template <std::unsigned_integral T>
    constexpr Mod_Int(T _val)
    : val(maintain(_val)) {}
    
    template <std::signed_integral T>
    constexpr Mod_Int(T _val)
    : val(maintain(_val)) {}

    template <std::unsigned_integral T>
    constexpr T maintain(T x) const {
        return B.opt(x);
    }

    template <std::signed_integral T>
    constexpr T maintain(T x) const {
        return x < 0 ? B.mod - (Int)B.opt(-x) : maintain<uInt>(x);
    }

    constexpr Mod_Int pow(uInt b) const {
        Mod_Int a = *this, res = 1;
        for (; b; a *= a, b >>= 1)
            if (b & 1) res *= a;
        return res;
    }

    Mod_Int operator - () const {
        return Mod_Int(B.mod - val);
    }

    Mod_Int operator ~ () const {
        assert(val != 0);

        Int a = B.mod, b = val;
        Int x = 0, y = 1;

        while (b) {
            const Int tmp = a / b;
            a -= tmp * b;
            x -= tmp * y;
            std::swap(a, b);
            std::swap(x, y);
        }
        if (x < 0) x += B.mod / a;

        assert(a == 1);
        return Mod_Int(x);
    }

    Mod_Int &operator += (Mod_Int other) & {
        (val += other.val) >= B.mod && (val -= B.mod);
        return *this;
    }

    Mod_Int &operator -= (Mod_Int other) & {
        (val -= other.val) >= B.mod && (val += B.mod);
        return *this;
    }

    Mod_Int &operator *= (Mod_Int other) & {
        val = B.opt(val * other.val);
        return *this;
    }

    Mod_Int &operator /= (Mod_Int other) & {
        val = B.opt(val * (~other).val);
        return *this;
    }

    friend Mod_Int operator + (Mod_Int l, Mod_Int r) {
        return l += r;
    }

    friend Mod_Int operator - (Mod_Int l, Mod_Int r) {
        return l -= r;
    }

    friend Mod_Int operator * (Mod_Int l, Mod_Int r) {
        return l *= r;
    }

    friend Mod_Int operator / (Mod_Int l, Mod_Int r) {
        return l /= r;
    }

    friend constexpr bool operator == (Mod_Int l, Mod_Int r) {
        return l.val == r.val;
    }

    friend constexpr std::strong_ordering operator <=> (Mod_Int l, Mod_Int r) {
        return l.val <=> r.val;
    }

    friend std::istream &operator >> (std::istream &is, Mod_Int &x) {
        return is >> x.val;
    }

    friend std::ostream &operator << (std::ostream &os, const Mod_Int &x) {
        return os << x.val;
    }
};
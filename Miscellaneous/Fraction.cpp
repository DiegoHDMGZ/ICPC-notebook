#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const Long INF = 1e18;

struct Fraction {
    Long num, den;
    Fraction() {}
    Fraction(Long n, Long d) {
        if (d == 0) {
            if (n > 0) num = INF;
            else num = -INF;
            den = 1;
        } else {
            if (d < 0) {
                n *= -1;
                d *= -1;
            }
            num = n;
            den = d;
        }
    }

    void normalize() {
        if (num == 0 && den == 0) return;
        Long g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;
    }

    Fraction operator+(const Fraction &F) const {
        Long g = gcd(den, F.den);
        return Fraction(num * (F.den / g) + F.num * (den / g), den * (F.den / g));
    }

    Fraction operator-(const Fraction &F) const {
        Long g = gcd(den, F.den);
        return Fraction(num * (F.den / g) - F.num * (den / g), den * (F.den / g));
    }

    Fraction operator*(const Fraction &F) const {
        return Fraction(num * F.num, den * F.den);
    }

    Fraction operator/(const Fraction &F) const {
        return Fraction(num * F.den, den * F.num);
    }

    bool operator==(const Fraction &F) const {
        return num * F.den == F.num * den;
    }

    bool operator!=(const Fraction &F) const {
        return !(*this == F);
    }

    bool operator<(const Fraction &F) const {
        return num * F.den < den * F.num;
    }

    bool operator<=(const Fraction &F) const {
        return *this < F || *this == F;
    }

    bool operator>=(const Fraction &F) const {
        return *this > F || *this == F;
    }

    bool operator>(const Fraction &F) const {
        return num * F.den > den * F.num;
    }

    long double getVal() {
        return 1.0 * num / den;
    }

    void debugFraction(string name) {
        cout << name << " = " << num << " / " << den << endl;
    }
};
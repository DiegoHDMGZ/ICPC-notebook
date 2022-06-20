#include <bits/stdc++.h>
using namespace std;

using Long = long long;

void eraseTrailing(deque<Long> &v) {
    while (v.size() > 1 && v[0] == 0) {
        v.pop_front();
    }
}

struct Big {
    deque<Long> digits;
    Long sgn;

    Big() {
        digits.push_back(0);
        sgn = 1;
    }

    Big(Long x) {
        if (x >= 0) {
            sgn = 1;
        } else {
            sgn = -1;
        }
        x = abs(x);
        if (x == 0) {
            digits = {0};
        } else {
            while (x > 0) {
                digits.push_front(x % 10);
                x /= 10;
            }
        }
    }

    Big(deque<Long> v, Long s = 1) {
        deque<Long> transf;
        Long i = 0;
        while (i < v.size() && v[i] == 0) {
            i++;
        }
        while (i < v.size()) {
            transf.push_back(v[i]);
            i++;
        }
        if (transf.size() == 0) {
            transf.push_back(0);
        }

        if (transf.size() == 1 && transf[0] == 0) {
            s = 1;
        }
        digits = transf;
        sgn = s;
    }

    bool operator==(const Big &P) const {
        return P.digits == digits && sgn == P.sgn;
    }

    bool operator<(const Big &P) const {
        if (P.sgn != sgn) {
            return P.sgn == 1;
        }
        if (P.digits.size() != digits.size()) {
            return digits.size() < P.digits.size();
        }
        for (Long i = 0; i < digits.size(); i++) {
            if (digits[i] != P.digits[i]) {
                return digits[i] < P.digits[i];
            }
        }
        return false;
    }

    bool operator>(const Big &P) const {
        if (P.sgn != sgn) {
            return sgn == 1;
        }
        if (P.digits.size() != digits.size()) {
            return digits.size() > P.digits.size();
        }
        for (Long i = 0; i < digits.size(); i++) {
            if (digits[i] != P.digits[i]) {
                return digits[i] > P.digits[i];
            }
        }
        return false;
    }

    Big operator+(const Big &other) const {
        deque<Long> ans;
        deque<Long> a = digits;
        deque<Long> b = other.digits;
        if (sgn * other.sgn == -1) {
            if (sgn == -1) {
                return other - Big(digits, 1);
            } else {
                return (*this) - Big(other.digits, 1);
            }
        }
        Long carry = 0;
        Long i = (Long)a.size() - 1, j = (Long)b.size() - 1;
        while (i >= 0 || j >= 0 || carry > 0) {
            Long x, y;
            if (i >= 0) x = a[i];
            else x = 0;

            if (j >= 0) y = b[j];
            else y = 0;

            Long sum = x + y + carry;
            carry = sum >= 10;
            if (carry) sum -= 10;
            ans.push_front(sum);
            i--;
            j--;
        }
        return Big(ans, sgn);
    }

    Big operator-(const Big &other) const {
        if (sgn * other.sgn == -1) {
            if (sgn == 1) {
                return (*this) + Big(other.digits, 1);
            } else {
                Big ans = Big(digits, 1) + Big(other.digits, 1);
                ans.sgn = -1;
                return ans;
            }
        }
        deque<Long> ans;
        deque<Long> a = digits;
        deque<Long> b = other.digits;
        Long newSgn = sgn;
        if (Big(a) < Big(b)) {
            newSgn = -other.sgn;
            swap(a, b);
        }

        Long i = (Long)a.size() - 1, j = (Long)b.size() - 1;
        while (i >= 0 && j >= 0) {
            Long subs = a[i] - b[j];
            if (subs < 0) {
                subs += 10;
                Long k = i - 1;
                while (a[k] == 0) {
                    a[k] = 9;
                    k--;
                }
                a[k]--;
            }
            ans.push_front(subs);
            i--;
            j--;
        }
        Long k = 0;
        while (k <= i && a[k] == 0) {
            k++;
        }
        for (Long j = i; j >= k; j--) {
            ans.push_front(a[j]);
        }
        return Big(ans, newSgn);
    }

    Big operator*(const Big &b) const {
        Big a = *this;
        Big ans;
        Long n = a.digits.size();
        Long m = b.digits.size();
        ans.digits.resize(n + m - 1, 0);

        for (Long i = n - 1; i >= 0; i--) {
            Long carry = 0;
            for (Long j = m - 1; j >= 0; j--) {
                ans.digits[i + j] += a.digits[i] * b.digits[j];
            }
        }
        for (Long i = (Long)ans.digits.size() - 1; i >= 1; i--) {
            Long carry = ans.digits[i] / 10;
            if (carry > 0) {
                ans.digits[i - 1] += carry;
                ans.digits[i] %= 10;
            }
        }
        while (ans.digits[0] >= 10) {
            Long carry = ans.digits[0] / 10;
            ans.digits[0] %= 10;
            ans.digits.push_front(carry);
        }
        eraseTrailing(ans.digits);
        ans.sgn = sgn * b.sgn;
        if (ans.digits.size() == 1 && ans.digits[0] == 0) {
            ans.sgn = 1;
        }
        return ans;
    }
};

ostream &operator<<(ostream &out, const Big &number) {
    if (number.sgn == -1) {
        out << "-";
    }
    for (Long i = 0; i < number.digits.size(); i++) {
        out << number.digits[i];
    }
    return out;
}

istream &operator>>(istream &in, Big &number) {
    string s;
    in >> s;

    if (s[0] == '-') {
        number.sgn = -1;
    } else {
        number.sgn = 1;
    }
    if (s[0] == '0') {
        number.digits = {0};
    } else {
        for (Long i = 0; i < s.size(); i++) {
            if (s[i] == '-') continue;
            number.digits.push_back(s[i] - '0');
        }
    }
    return in;
}

int main() {
    Big a, b;
    cin >> a >> b;

    cout << a + b << endl;
    cout << a * b << endl;
    return 0;
}

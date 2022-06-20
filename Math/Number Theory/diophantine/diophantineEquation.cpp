#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// Property: the solutions given holds the following:
// |x| <= |b / gcd(a, b)| , |y| <= |a / gcd(a, b)|
Long gcd(Long a, Long b, Long &x, Long &y) { // O(min(log a,log b))
    if (b == 0) {
        if (a >= 0) x = 1;
        else x = -1;
        y = 0;
        return abs(a);
    }
    Long x2, y2;
    Long g = gcd(b, a % b, x2, y2);
    x = y2;
    y = x2 - (a / b) * y2;
    return g;
}

// ax + by = c
bool diophantine(Long a, Long b, Long c, Long &x, Long &y, Long &g) { // O(min(log a,log b))
    if (a == 0 && b == 0) {
        if (c != 0) return false;
        else {
            x = y = g = 0;
            return true;
        }
    }
    g = gcd(a, b, x, y);
    if (c % g != 0) {
        return false;
    }

    x *= c / g;
    y *= c / g;
    return true;
}

Long divDown(Long a, Long b) {
    Long d = abs(a) / abs(b);
    if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
        return d;
    } else {
        if (a % b == 0) return -d;
        else return -d - 1;
    }
}

Long divUp(Long a, Long b) {
    Long d = abs(a) / abs(b);
    if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
        if (a % b == 0) return d;
        else return d + 1;
    } else return -d;
}

vector<pair<Long, Long>> getAllSolutions(Long a, Long b, Long c, Long lx, Long rx, Long ly,
                                         Long ry) { // O(min(log a, log b) + #solutions)
    Long x0, y0, g;
    if (!diophantine(a, b, c, x0, y0, g)) return {};

    vector<pair<Long, Long>> ans;
    if (a == 0) {
        if (b == 0) {
            for (Long i = lx; i <= rx; i++) {
                for (Long j = ly; j <= ry; j++) {
                    ans.push_back({i, j});
                }
            }
        } else {
            if ((ly <= c / b) && (c / b <= ry)) {
                for (Long i = lx; i <= rx; i++) {
                    ans.push_back({i, c / b});
                }
            } else {
                return {};
            }
        }
        return ans;
    } else if (b == 0) {
        if ((lx <= c / a) && (c / a <= rx)) {
            for (Long i = ly; i <= ry; i++) {
                ans.push_back({c / a, i});
            }
        } else {
            return {};
        }
        return ans;
    }

    Long kMin, kMax;
    if (b > 0) {
        kMin = divUp((lx - x0) * g, b);
        kMax = divDown((rx - x0) * g, b);
    } else {
        kMin = divUp((rx - x0) * g, b);
        kMax = divDown((lx - x0) * g, b);
    }
    if (a > 0) {
        kMin = max(kMin, divUp((y0 - ry) * g, a));
        kMax = min(kMax, divDown((y0 - ly) * g, a));
    } else {
        kMin = max(kMin, divUp((y0 - ly) * g, a));
        kMax = min(kMax, divDown((y0 - ry) * g, a));
    }

    if (kMin > kMax) return {};

    for (Long k = kMin; k <= kMax; k++) {
        ans.push_back({x0 + k * (b / g), y0 - k * (a / g)});
    }
    return ans;
}

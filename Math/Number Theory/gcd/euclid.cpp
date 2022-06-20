#include <bits/stdc++.h>
using namespace std;
using Long = long long;

// ax + by = gcd(a , b)
// Property: the solutions given holds the following:
// |x| <= |b / gcd(a, b)| , |y| <= |a / gcd(a, b)|
Long gcd(Long a, Long b, Long &x, Long &y) { // O(min(loga,logb))
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

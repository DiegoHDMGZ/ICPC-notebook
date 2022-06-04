#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

// Pick's Theorem : A = I + B / 2 - 1
//  I = (2A - B + 2) / 2

struct Point {
    Long x, y;
    Point(Long x = 0, Long y = 0) : x(x), y(y) {}
};

Long area2(vector<Point> &v) { // O(n)
    // double of the area
    Long ans = 0;
    Long sz = v.size();
    for (Long i = 0; i < sz; i++) {
        int prevPos = i - 1;
        if (i == 0) prevPos = sz - 1;
        Point P = v[prevPos];
        Point Q = v[i];
        ans += (P.x - Q.x) * (P.y + Q.y);
    }
    return abs(ans);
}

Long boundaryPoints(Point A, Point B) { // O(log MX)
    return __gcd(abs(A.x - B.x), abs(A.y - B.y)) + 1;
}

Long boundaryPoints(vector<Point> &v) { // O(n log MX)
    Long n = v.size();
    Long ans = 0;
    for (Long i = 0; i < n; i++) {
        int prevPos = i - 1;
        if (i == 0) prevPos = n - 1;
        ans += boundaryPoints(v[i], v[prevPos]);
    }
    return ans - n;
}

Long interiorPoints(vector<Point> &v) { // O(n log MX)
    return (area2(v) - boundaryPoints(v) + 2) / 2;
}

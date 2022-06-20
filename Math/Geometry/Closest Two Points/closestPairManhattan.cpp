#include <bits/stdc++.h>
using namespace std;

using Long = long long;

struct Point {
    Long x, y;

    Point() : x(0), y(0) {}
    Point(Long x, Long y) : x(x), y(y) {}

    Point operator+=(const Point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }

    Point operator-=(const Point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }

    Point operator*=(Long t) {
        x *= t;
        y *= t;
        return *this;
    }

    Point operator+(const Point &t) const {
        return Point(*this) += t;
    }

    Point operator-(const Point &t) const {
        return Point(*this) -= t;
    }

    bool operator==(const Point &P) const {
        return P.x == x && P.y == y;
    }

    bool operator!=(const Point &P) const {
        return !(P == Point(*this));
    }
};

bool cmpX(const Point &P1, const Point &P2) {
    return (P1.x != P2.x ? P1.x < P2.x : P1.y < P2.y);
}

bool cmpY(const Point &P1, const Point &P2) {
    return (P1.y != P2.y ? P1.y < P2.y : P1.x < P2.x);
}

Long dist(Point P1, Point P2) {
    return abs(P1.x - P2.x) + abs(P1.y - P2.y);
}

pair<Point, Point> combine(pair<Point, Point> D1, pair<Point, Point> D2) { // O(1)
    if (dist(D1.first, D1.second) > dist(D2.first, D2.second)) {
        swap(D1, D2);
    }
    return D1;
}

pair<Point, Point> closestPair(vector<Point> &X, vector<Point> &Y) { // O(n log n)
    Long n = X.size();
    assert((Long)(X.size()) == (Long)(Y.size()));
    if (n <= 3) {
        pair<Point, Point> minPair = {X[0], X[1]};
        for (Long i = 0; i < n; i++) {
            for (Long j = i + 1; j < n; j++) {
                minPair = combine(minPair, {X[i], X[j]});
            }
        }
        return minPair;
    }
    vector<Point> XL;
    vector<Point> XR;
    vector<Point> YL;
    vector<Point> YR;
    Long mid = n / 2;
    for (Long i = 0; i < mid; i++) {
        XL.push_back(X[i]);
        if (cmpX(Y[i], X[mid])) {
            YL.push_back(Y[i]);
        } else {
            YR.push_back(Y[i]);
        }
    }
    for (Long i = mid; i < n; i++) {
        XR.push_back(X[i]);
        if (cmpX(Y[i], X[mid])) {
            YL.push_back(Y[i]);
        } else {
            YR.push_back(Y[i]);
        }
    }
    pair<Point, Point> ans = combine(closestPair(XL, YL), closestPair(XR, YR));
    Long d = dist(ans.first, ans.second);
    vector<Point> YP;
    for (Long i = 0; i < n; i++) {
        if (abs(X[mid].x - Y[i].x) <= d) {
            YP.push_back(Y[i]);
        }
    }
    Long sz = YP.size();
    for (int i = 0; i < sz; i++) { // one pair from L and one from R
        Long j = i + 1;
        while (j < sz && abs(YP[j].y - YP[i].y) <= d) { // 12 points upper bound
            ans = combine(ans, {YP[i], YP[j]});
            j++;
        }
    }
    return ans;
}

pair<Point, Point> closestPair(vector<Point> &v) { // O( n log n)
    Long n = v.size();
    vector<Point> X = v;
    vector<Point> Y = v;
    sort(X.begin(), X.end(), cmpX);
    sort(Y.begin(), Y.end(), cmpY);
    for (int i = 0; i < n - 1; i++) {
        if (X[i] == X[i + 1]) {
            return {X[i], X[i + 1]};
        }
    }
    return closestPair(X, Y);
}

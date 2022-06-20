#include <bits/stdc++.h>
using namespace std;

using Long = long long;

struct Point {
    Long x, y;
    Point(Long x = 0, Long y = 0) : x(x), y(y) {}
    Point operator-(const Point &other) const {
        return Point(x - other.x, y - other.y);
    }
    Long cross(const Point &other) const {
        return x * other.y - y * other.x;
    }
    Long cross(const Point &A, const Point &B) const {
        return (A - *this).cross(B - *this);
    }
    bool operator==(const Point &P) const {
        return x == P.x && y == P.y;
    }
};

struct Line {
    Long A, B, C; // Ax + By + C = 0
    Line() {}
    Line(Long A, Long B, Long C) : A(A), B(B), C(C) {}
    Line(Point P1, Point P2) {
        A = P1.y - P2.y;
        B = P2.x - P1.x;
        C = -A * P1.x - B * P1.y;
    }
    Long evaluate(Point P) {
        return A * P.x + B * P.y + C;
    }
};

Long square(Long x) {
    return x * x;
}

Long squareDist(Point P1, Point P2) {
    return square(P1.x - P2.x) + square(P1.y - P2.y);
}

vector<Point> convexHull(vector<Point> &v); // O(n log n)

pair<Point, Point> farthestPair(vector<Point> &v) { // O(n log n)
    vector<Point> P = convexHull(v);
    int n = P.size();
    if (n <= 1) return make_pair(P[0], P[0]);
    if (n == 2) return make_pair(P[0], P[1]);
    vector<pair<Point, Point>> antipodals;
    auto nextPos = [&](int pos) {
        if (pos + 1 < n) return pos + 1;
        return 0;
    };
    auto prevPos = [&](int pos) {
        if (pos - 1 >= 0) return pos - 1;
        return n - 1;
    };
    int i = 0;
    int j = i + 2;
    while (i < n) { // O(n)
        // Find the maximum distance from edge hull[i - j]
        Line L(P[i], P[nextPos(i)]);
        Long d = L.evaluate(P[j]);
        j = nextPos(j);
        while (d < L.evaluate(P[j])) {
            d = L.evaluate(P[j]);
            j = nextPos(j);
        }
        antipodals.push_back({P[i], P[prevPos(j)]});
        antipodals.push_back({P[nextPos(i)], P[prevPos(j)]});
        if (L.evaluate(P[j]) == d) {
            antipodals.push_back({P[i], P[j]});
            antipodals.push_back({P[nextPos(i)], P[j]});
        }
        j = prevPos(j);
        i++;
    }
    Long maxDist = -1;
    pair<Point, Point> choice;
    for (auto antipodal : antipodals) {
        auto [P, Q] = antipodal;
        if (squareDist(P, Q) > maxDist) {
            maxDist = squareDist(P, Q);
            choice = antipodal;
        }
    }
    return choice;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

typedef long double Double;

const Double PI = acos(-1);
const Double EPS = 1e-8;
const Double INF = 1e9;
struct Point {
    Double x, y;
    Point() {}
    Point(Double x, Double y) : x(x), y(y) {}

    Point rotate(Double angle) {
        Double rotatedX = x * cos(angle) + y * sin(angle);
        Double rotatedY = -x * sin(angle) + y * cos(angle);
        return Point(rotatedX, rotatedY);
    }
};

Double chordAngle(Double R, Double len) { return 2 * asin(len / (2 * R)); }

bool checkRadius(Double R, vector<Double> &sides, bool aroundCenter) {
    Double sum = 0;
    Double maxAngle = 0;
    for (Double L : sides) {
        Double angle = chordAngle(R, L);
        sum += angle;
        maxAngle = max(maxAngle, angle);
    }
    if (aroundCenter) {
        return sum <= 2 * PI;
    } else {
        return sum - 2 * maxAngle > 0;
    }
}

Double findRadius(Double low, Double high, vector<Double> &sides, bool aroundCenter) {
    // O(logn)
    for (int i = 0; i < 100; i++) {
        Double mid = (low + high) / 2.0;
        if (checkRadius(mid, sides, aroundCenter)) high = mid;
        else low = mid;
    }
    return high;
}

vector<Point> getMaximumAreaPolygon(vector<Double> &sides) {
    Double maxSide = 0;
    int maxIndex = 0;
    for (int i = 0; i < sides.size(); i++) {
        if (sides[i] > maxSide) {
            maxSide = sides[i];
            maxIndex = i;
        }
    }
    if (maxIndex + 1 != sides.size()) {
        rotate(sides.begin(), sides.begin() + maxIndex + 1, sides.end());
    }

    Double minR = maxSide / 2.0;
    Double R;
    if (checkRadius(minR + EPS, sides, true)) {
        R = findRadius(minR + EPS, INF, sides, false);
    } else {
        R = findRadius(minR + EPS, INF, sides, true);
    }
    vector<Point> polygon = {Point(R, 0)};
    for (int i = 0; i + 1 < sides.size(); i++) {
        polygon.push_back(polygon.back().rotate(chordAngle(R, sides[i])));
    }
    if (maxIndex + 1 != sides.size()) {
        rotate(polygon.begin(), polygon.end() - maxIndex - 1, polygon.end());
    }
    return polygon;
}
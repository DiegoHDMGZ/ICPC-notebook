#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct Point {
	Long x, y;
	Point(Long x = 0, Long y = 0): x(x) , y(y){}
	Point operator -(const Point &other) const {
		return Point(x - other.x, y - other.y);
	}
	Point operator -=(const Point &other) {
		*this = *this - other;
		return *this;
	}
	Long cross(const Point &other) const {
		return x * other.y - y * other.x;
	}
	Long cross(const Point &A, const Point &B) const {
		return (A - *this).cross(B - *this);
	}
	bool operator == (const Point &P) const {
		return x == P.x && y == P.y;
	}
};

Long square(Long x) {return x * x;}

Long squareDist(Point P1, Point P2) {
	return square(P1.x - P2.x) + square(P1.y - P2.y);
}

vector<Point> convexHull(vector<Point> &v) { //O(n log n)
	//gives the convex hull in counter clockwise order
	Point center = v[0];
	int n = v.size();
	for (int i = 0; i < n; i++) {
		if (make_pair(v[i].y, v[i].x) < make_pair(center.y, center.x)) {
			center = v[i];
		}
	}
	auto cmp = [&](const Point &P1, const Point &P2) {
		if (center.cross(P1, P2) == 0) {
			return squareDist(center, P1) < squareDist(center, P2);
		}
		return center.cross(P1, P2) > 0;
	};
	sort(v.begin(), v.end(), cmp);
	auto it = unique(v.begin(), v.end());
	v.resize(distance(v.begin(), it));
	n = v.size();

	if (n < 3) return v;
	vector<Point> hull;
	hull.push_back(v[0]);
	hull.push_back(v[1]);
	for (int i = 2 ; i < n; i++) {
		int sz = hull.size();
		Point prev1 = hull[sz - 1];
		Point prev2 = hull[sz - 2];
		while(hull.size() >= 2 && 
		hull.back().cross(v[i], hull.end()[-2]) <= 0) {
			hull.pop_back();
		}
		hull.push_back(v[i]);
	}
	return hull;
}

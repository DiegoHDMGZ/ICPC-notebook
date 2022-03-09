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
	int n = v.size();
	Point center = *min_element(v.begin(), v.end(), 
	[](const Point &A, const Point &B) {
		if (A.y == B.y) return A.x < B.x;
		return A.y < B.y;
	});
	auto cmp = [&](const Point &A, const Point &B) {
		if (center.cross(A, B) == 0) {
			return squareDist(center, A) < squareDist(center, B);
		}
		return center.cross(A, B) > 0;
	};
	sort(v.begin(), v.end(), cmp);
	auto it = unique(v.begin(), v.end());
	v.resize(distance(v.begin(), it));
	n = v.size();
	if (n < 3) return v;
	/*
	//To include collinear points use the following lines
	int i = n - 1;
	while (i > 0 && v[i].cross(v[i - 1], v[0]) == 0) i--;
	if (i > 0) reverse(v.begin() + i, v.end());
	*/
	vector<Point> hull = {v[0], v[1]};
	auto canDelete = [&](const Point &P) {
		return hull.back().cross(hull.end()[-2], P) >= 0;
		//> 0 to include collinear points
	};
	for (int i = 2; i < n; i++) {
		while (hull.size() >= 2 && canDelete(v[i])) hull.pop_back();
		hull.push_back(v[i]);
	}
	return hull;
}

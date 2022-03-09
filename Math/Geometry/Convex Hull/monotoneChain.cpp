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

vector<Point> convexHull(vector<Point> &v) { //O(n log n)
	//gives the convex hull in counter clockwise order
	int n = v.size();
	auto cmp = [&](const Point &P1, const Point &P2) {
		//compare by x and then by y also works
		if (P1.y == P2.y) return P1.x < P2.x;
		return P1.y < P2.y;
	};
	sort(v.begin(), v.end(), cmp);
	auto it = unique(v.begin(), v.end());
	v.resize(distance(v.begin(), it));
	n = v.size();
	if (n < 3) return v;
	Point A = v[0];
	Point B = v.back();
	vector<Point> hull = {A}; //lower hull at the beginning
	auto canDelete = [&](const Point &P) {
		return hull.back().cross(hull.end()[-2], P) >= 0;
		//> 0 to include collinear points
	};
	for (int i = 1; i < n; i++) {
		if (i == n - 1 || v[i].cross(A, B) < 0) { 
			//v[i].cross(A, B) <= 0 to include collinear points
			while (hull.size() >= 2 && canDelete(v[i])) hull.pop_back();
			hull.push_back(v[i]);
		}
	}
	//`hull` is now the lower hull
	//in the second loop we're going to add the upper hull
	
	//To include collinear points use the following line to avoid
	//having repeated points in the degenerate case of a line
	//if (hull.size() == v.size()) return hull;
	
	int szLow = hull.size();
	for (int i = n - 2; i >= 0; i--) {
		if (i == 0 || v[i].cross(A, B) > 0) {
			//v[i].cross(A, B) >= 0 to include collinear points
			while (hull.size() > szLow && canDelete(v[i])) hull.pop_back();
			if (i > 0) hull.push_back(v[i]);
		}
	}
	return hull;
}

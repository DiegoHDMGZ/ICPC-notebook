#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

enum Location{OUTSIDE, BOUNDARY, INSIDE};

const Long INF = 2e9;

Long sgn(Long val) {
	if(val > 0) {
		return 1;
	}
	if(val < 0) {
		return -1;
	}
	return 0;
}

struct Point{
	Long x, y;
	
	Point() : x(0), y(0) {}
	Point(Long x, Long y) : x(x), y(y) {}

	Point operator -= (const Point &t) {
		x -= t.x;
		y -= t.y;
		return *this;
	}

	Point operator - (const Point &t) const {
		return Point(*this) -= t;
	}
	
	bool operator == (const Point &P) const {
		return P.x == x && P.y == y;
	}

	Long cross(const Point &P) const {
		return x * P.y - y * P.x;
	}
	
	Long cross(const Point &a, const Point &b) const {
		return (a - *this).cross(b - *this);
	}
	
	bool inSegment(Point A, Point B) {
		Point target = Point(*this);
		if(A.cross(B , target) == 0) {
			if(target.x >= min(A.x , B.x) && target.x <= max(A.x , B.x) && target.y >= min(A.y , B.y) && target.y <= max(A.y , B.y )) {
				return true;
			} 
		}
		return false;
	}
	
	Location inPolygon(vector<Point> &poly);
};

bool intersectAxis(Long a, Long b , Long c, Long d) {
	if(a > b) {
		swap(a , b);
	}
	if(c > d) {
		swap(c , d);
	}
	return max(a , c) <= min(b , d);
}

bool intersectSegment(Point A, Point B, Point C, Point D) {
	if(C.cross(A, D) == 0 && C.cross(B, D) == 0) {
		//same line
		return intersectAxis(A.x, B.x, C.x, D.x ) && intersectAxis(A.y ,B.y , C.y , D.y);
	}
	return sgn(A.cross(B, C)) != sgn(A.cross(B , D)) && sgn(C.cross(D, A)) != sgn(C.cross(D, B));
}

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

Location Point::inPolygon(vector<Point> &poly) { //O(n)
	//works with any simple polygon 
	int n = poly.size();
	Point P = Point(*this);
	if(n == 1) {
		if (P == poly[0]) return Location::BOUNDARY;
		else return Location::OUTSIDE;
	}
	if(n == 2) {
		if(P.inSegment(poly[0] , poly[1])) return Location::BOUNDARY;
		else return Location::OUTSIDE;
	}
	Point Q = Point(INF, random(0, INF));
	int cnt = 0;
	for (int i = 0; i < poly.size(); i++) {
		Point nextPoint;
		if (i + 1 < poly.size()) nextPoint = poly[i + 1];
		else nextPoint = poly[0];
		if (P.inSegment(poly[i], nextPoint)) return Location::BOUNDARY;
		if (intersectSegment(poly[i], nextPoint, P, Q)) cnt++;
	}
	if (cnt % 2 == 0) {
		return Location::OUTSIDE;
	} else {
		return Location::INSIDE;
	}
}

int main() {
	return 0;
}

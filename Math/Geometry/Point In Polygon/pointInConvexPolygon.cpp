#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

enum Location{OUTSIDE, BOUNDARY, INSIDE};

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
	
	bool inTriangle(Point A, Point B, Point C) {
		//compare areas
		Point P = Point(*this);
		Long a1 = abs(A.cross(B , C));
		Long a2 = abs(P.cross(A , B)) + abs(P.cross(A , C)) + abs(P.cross(B , C));
		return a1 == a2;
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
	
	Location inPolygon(vector<Point> &poly) { //O(log n)
		//works with convex polygons in counter-clockwise order
		//use prepare (poly) before using it
		Long n = poly.size();
		Point P = Point(*this);
		if(n == 1) {
			if (P == poly[0]) return Location::BOUNDARY;
			else return Location::OUTSIDE;
		}
		if(n == 2) {
			if(P.inSegment(poly[0] , poly[1])) return Location::BOUNDARY;
			else return Location::OUTSIDE;
		}
		//verify if the angle of the point lies between the angle of p0p1 and p0pn-1
		if(poly[0].cross(poly[1] , P) != 0 
			&& sgn(poly[0].cross(poly[1] , P)) != sgn(poly[0].cross(poly[1] , poly[n - 1]))) {
			return Location::OUTSIDE;
		}
		if(poly[0].cross(P , poly[n - 1]) != 0 
			&& sgn(poly[0].cross(P , poly[n - 1])) != sgn(poly[0].cross(poly[1] , poly[n - 1]))) {
			return Location::OUTSIDE;
		}
	
		Long low = 2;
		Long high = n - 1;
		if (poly[0].cross(poly[low], P) <= 0) {
			high = low;
		} else {
			while (high - low > 1) { 
				Long mid = (low + high) / 2;
				if (poly[0].cross(poly[mid] , P) <= 0) high = mid;
				else low = mid;
			}
		}
		if (!P.inTriangle(poly[0] , poly[high - 1] , poly[high])) {
			return Location::OUTSIDE;
		}
		if (P.inSegment(poly[high - 1] , poly[high])) {
			return Location::BOUNDARY;
		}
		if (P.inSegment(poly[0] , poly[1])) {
			return Location::BOUNDARY;
		}
		if (P.inSegment(poly[0], poly[n - 1])) {
			return Location::BOUNDARY;
		}
		return Location::INSIDE;
	}
};

void prepare(vector<Point> &poly) {
	//make sure the polygon is in counter-clockwise order 
	if (poly.size() >= 3 && poly[1].cross(poly[2], poly[0]) < 0) {
		reverse(poly.begin(), poly.end());
	}
	//make sure the first point have minimum x (minimum y in case of ties)
	Long sz = poly.size();
	Long pos = 0;
	for(Long i = 1; i < sz; i++) {
		if(make_pair(poly[i].x , poly[i].y) < make_pair(poly[pos].x , poly[pos].y)) {
			pos = i;
		}
	}
	rotate(poly.begin() , poly.begin() + pos , poly.end());
}

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)

using namespace std;

typedef long long Long;
typedef long double Double;
const Double EPS = 1e-10;
const Double PI = acos(-1);

Double square(Double x) {
	return x * x;
}

int getSgn(Double x) {
	if (fabs(x) < EPS) return 0;
	if (x > 0) return 1;
	return -1;
}

struct Point{
	Double x, y;
	Point(Double x = 0, Double y = 0): x(x), y(y) {}
	Point operator +(const Point &other) const {
		return Point(x + other.x, y + other.y);
	}
	Point operator -(const Point &other) const {
		return Point(x - other.x, y - other.y);
	}
	Point operator *(Double t) const {
		return Point(x * t, y * t);
	}
	Point operator /(Double t) const {
		assert(fabs(t) > EPS);
		return Point(x / t, y / t);
	}
	Point operator +=(const Point &other) {
		*this = *this + other;
		return *this;
	}
	Point operator -=(const Point &other) {
		*this = *this - other;
		return *this;
	}
	Point operator *=(Double t) {
		*this = *this * t;
		return *this;
	}
	Point operator /=(Double t) {
		*this = *this / t;
		return *this;
	}
	bool operator ==(const Point &P) const {
		return fabs(x - P.x) < EPS && fabs(y - P.y) < EPS;
	}
	Double abs2() {
		return x * x + y * y;
	}
	Double abs() {
		return sqrt(abs2());
	}
	Point ort() {
		return Point(-y, x);
	}
	Double dot(const Point &other) {
		return x * other.x + y * other.y;
	}
	Double cross(const Point &P) const {
		return x * P.y - y * P.x;
	}
	Double cross(const Point &A, const Point &B) const {
		//Given the current point P, this calculate PA x PB
		return (A - *this).cross(B - *this);
	}
};

typedef Point Vector;

//additional point operators with double
Point operator *(Double a, Point b) {
	return b * a;
}

Point operator /(Double a , Point b) {
	return b / a;
}

//Auxiliary functions
Double dist(Point A, Point B) {
	return sqrt(square(B.x - A.x) + square(B.y - A.y));
}

Point midPoint(Point A, Point B) {
	return Point((A + B) / 2.0);
}

int quad(const Point &P) {
	//quadrant of a point
	if(P.x >= 0 && P.y > 0) return 1;
	if(P.x < 0 && P.y >= 0) return 2;
	if(P.x <= 0 && P.y < 0) return 3;
	return 4;
} 

bool counterClockwise(const Point &A, const Point &B, Point &center) {
	if (quad(A - center) != quad(B - center)) {
		return quad(A - center) < quad(B - center);
	}
	return center.cross(A, B) > 0;
}

//Vector Functions
Vector getProj(Vector A, Vector B) {
	//projection of A on to B
	assert(B.abs() > EPS);
	Vector unitB = B / B.abs();
	return unitB * (A.dot(B)) / B.abs();
}

Vector bisect(Vector A, Vector B) {
	return A * B.abs() + B * A.abs();
}

Double getSimpleAngle(Vector A, Vector B) {
	//return angle in [0 , PI] and does not have orientation
	Double num = A.dot(B);
	Double den = A.abs() * B.abs();
	assert(fabs(den) >= EPS);
	Double cosine = num / den;
	if (cosine > 1 - EPS) return 0;
	if (cosine < -1 + EPS) return PI;
	return acos(num / den);
}

Double getAngle(Vector A, Vector B) {
	//return angle from A to B (order matters) in [0 , 2 * PI]
	Double ang = getSimpleAngle(A, B);
	int sineSgn = getSgn(A.cross(B));
	if (sineSgn < 0) ang = 2 * PI - ang;
	return ang;
}

Vector rotate(Vector v, Double sine) {
	Double cosine = sqrt(1 - sine * sine);
	return Vector(v.x * cosine + v.y * sine, -v.x * sine + v.y * cosine);
}

//Segment functions
bool between(Double x, Double l, Double r) {
	//is x in [l , r] or [r, l] ?
	return x >= min(l, r) - EPS && x <= max(l, r) + EPS;
}

bool axisHasIntersection(Double l1, Double r1, Double l2, Double r2) {
	//return if it exists intersection in 
	//[min(l1, r1), max(l1, r1)], [min(l2, r2), max(l2, r2)]
	if (l1 > r1) swap(l1 , r1);
	if (l2 > r2) swap(l2 , r2);
	return max(l1, l2) <= min(r1, r2) + EPS;
}

struct Segment {
	Point A, B;
	Segment(){}
	Segment(Point A, Point B): A(A), B(B){}
	bool contains(const Point &P) const {
		if (fabs(A.cross(B, P)) < EPS) {
			return between(P.x, A.x, B.x) && between(P.y, A.y, B.y);
		}
		return false;
	} 	
	bool hasIntersection(const Segment &other) const {
		Point C = other.A;
		Point D = other.B;
		if (C.cross(A, D) == 0 && C.cross(B, D) == 0) {
			//same line
			return axisHasIntersection(A.x, B.x, C.x, D.x) 
			&& axisHasIntersection(A.y, B.y, C.y, D.y);
		}
		bool ok1 = getSgn(A.cross(B, C)) != getSgn(A.cross(B, D));
		bool ok2 = getSgn(C.cross(D, A)) != getSgn(C.cross(D, B));
		return ok1 && ok2;
	}
};

//Line functions
struct Line{
	Double A, B, C; //Ax + By + C = 0
	Line(){}
	Line(Double A, Double B, Double C): A(A), B(B), C(C){}
	Line(Point P1, Point P2){
		A = P1.y - P2.y;
		B = P2.x - P1.x;
		C = -A * P1.x  - B * P1.y;	
	}
	Double evaluate(Point P) {
		return A * P.x + B * P.y + C;
	}
	Double dist(const Point &P) {
		//minimum distance from point to line
		return fabs(evaluate(P)) / sqrt(square(A) + square(B));
	}
};

Double det(Double a, Double b, Double c, Double d) {
	return a * d - b * c;
}

vector<Point> intersect(Line &L1, Line &L2) {
	//empty vector -> Parallel lines
	//size 1 -> One point of intersection
	//size 2 -> Equivalent Lines
	Double den = det(L1.A, L1.B, L2.A, L2.B);
	Double x = -det(L1.C, L1.B, L2.C, L2.B);
	Double y = -det(L1.A, L1.C, L2.A, L2.C);
	if (fabs(den) < EPS) {
		if (fabs(x) < EPS && fabs(y) < EPS) return vector<Point>(2);
		else return {};
	}
	Point ans(x, y);
	ans /= den;
	return {ans};
}

//Circle functions
struct Circle{
	Point center;
	Double r;
	Circle(){}
	Circle(Point center, Double r): center(center), r(r){}
};

vector<Point> intersect(Line L, Circle C) {
	//coordinate translation to center of circle
	Double delta = C.center.x * L.A + C.center.y * L.B;
	L.C += delta;
	Double den = square(L.A) + square(L.B);
	Double x0 = -L.A * L.C / den;
	Double y0 = -L.B * L.C / den;
	Double diff = square(C.r) - square(L.C) / den;
	vector<Point> ans;
	if(fabs(diff) < EPS){
		//distance between line and center is equal to r
		ans = {Point(x0, y0)};
	} else if (diff < EPS){
		//if the distance between the line and center 
		//is greater than r, then there is no intersection
		return {};
	} else {
		Double d = sqrt(diff / den);
		ans.push_back(Point(x0 + L.B * d, y0 - L.A * d));
		ans.push_back(Point(x0 - L.B * d, y0 + L.A * d));
	}
	//undo translation
	for (Point &P : ans) P += C.center;
	return ans;
}

vector<Point> intersect(Circle C, Line L) {
	return intersect(L, C);
}

vector<Point> intersect(Circle C1, Circle C2) {
	//empty vector: no intersection
	//size 3: infinite points
	if (C1.center == C2.center) {
		if (C1.r == C2.r) return vector<Point>(3);
		else return {};
	}
	Double d = dist(C1.center, C2.center);
	if(d > C1.r + C2.r + EPS) return {}; //too far away
	if(d < fabs(C1.r - C2.r) - EPS) return {}; //circle inside the other
	Point O(0 , 0);
	C2.center -= C1.center; //translation
	//Let (x', y') be the other center
	//x^2 + y^2 = (r1)^2
	//(x - x')^2 + (y - y')^2 = (r2)^2
	//=> x (-2x') + y (-2y') + ((x')^2 + (y')^2 + (r1)^2 - (r2)^2) = 0
	Double x2 = C2.center.x;
	Double y2 = C2.center.y;
	Double A = -2 * x2;
	Double B = -2 * y2;
	Double C = square(x2) + square(y2) + square(C1.r) - square(C2.r);
	Line L(A, B, C);
	vector<Point> ans = intersect(Circle(O, C1.r), L);
	for (Point &P : ans) P += C1.center;
	return ans;
}

vector<Line> getTangents(Circle C, Point P) {
	if (dist(P, C.center) < C.r - EPS) return {};
	if (dist(P, C.center) < C.r + EPS) {
		Point Q = P + (C.center - P).ort();
		return {Line(P, Q)};
	}
	Double D = dist(C.center, P);
	Double R = C.r;
	Vector PC = C.center - P;
	Point A = rotate(PC, R / D) + P;
	Point B = rotate(PC, -R / D) + P;
	Line L1(P, B);
	Line L2(P, A);
	return {L1, L2};
}

vector<Line> getTangents(Point P, Circle C) {
	return getTangents(C, P);
}
//Triangle functions
struct Triangle {
	Point A, B, C;
	Triangle(){}
	Triangle(Point A, Point B, Point C): A(A), B(B), C(C){}
	Double area() {
		return fabs(A.cross(B, C)) / 2.0;
	}
	bool contains(Point &P) {
		//compare areas
		Double a1 = fabs(A.cross(B, C));
		Double a2 = fabs(P.cross(A, B)) + fabs(P.cross(A, C)) + fabs(P.cross(B, C));
		return fabs(a1 - a2) < EPS;
	} 
	
	Circle circumcircle() {
		//assuming non-degenerated triangle
		Point M = midPoint(A, B);
		Point N = midPoint(A, C);
		Point Mx = M + (B - A).ort();
		Point Nx = N + (C - A).ort();
		Line L1(M, Mx);
		Line L2(N, Nx);
		Circle ans;
		ans.center = intersect(L1 , L2)[0];
		ans.r = dist(ans.center , A);
		return ans;
	}

	Circle incircle() {
		//assuming non-degenerated triangle
		Double a = dist(B, C);
		Double b = dist(A, C);
		Double c = dist(A, B);
		Circle ans;
		ans.center.x = (a * A.x + b * B.x + c * C.x);
		ans.center.y = (a * A.y + b * B.y + c * C.y);
		ans.center /= a + b + c;
		Double p = (a + b + c) / 2.0;
		ans.r = area() / p;
		return ans;
	}
};


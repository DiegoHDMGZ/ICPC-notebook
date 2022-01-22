#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)

using namespace std;

typedef long double Double;
typedef long long Long;
const Double EPS = 1e-10;
const Double PI = acos(-1);

bool near(Double a, Double b) {
	return fabs(a - b) < EPS;
}

struct Point{
	Double x, y, z;
	Point(Double x = 0, Double y = 0, Double z = 0): x(x), y(y), z(z){}
	Point operator +(const Point &other) const {
		return Point(x + other.x, y + other.y, z + other.z);
	}
	Point operator -(const Point &other) const {
		return Point(x - other.x, y - other.y, z - other.z);
	}
	Double operator /(const Point &other) const {
		//A = t B 
		Double t;
		assert(other != Point());
		if (!near(other.x, 0)) t = x / other.x;
		else if (!near(other.y, 0)) t = y / other.y;
		else t = z / other.z;
		return t;
	}
	Point operator *(Double t) const {
		return Point(x * t, y * t, z * t);
	}
	Point operator /(Double t) const {
		assert(fabs(t) > EPS);
		return Point(x / t, y / t, z / t);
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
		return near(x, P.x) && near(y, P.y) && near(z, P.z);
	}
	bool operator !=(const Point &P) const {
		return !(P == *this);
	}
	Double abs2() {
		return x * x + y * y + z * z;
	}
	Double abs() {
		return sqrt(abs2());
	}
};

typedef Point Vector;

//dot and cross products
Double dot(Point A, Point B) {
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

Point cross(Point A, Point B) {
	return Point(
		A.y * B.z - A.z * B.y, 
		A.z * B.x - A.x * B.z, 
		A.x * B.y - A.y * B.x
	);
}

//additional point operators with double
Double square(Double x) {
	return x * x;
}

Point operator *(Double a, Point b) {
	return b * a;
}

Point operator /(Double a , Point b){
	return b / a;
}

Vector getProj(Vector A, Vector B) {
	//projection of A on to B
	assert(B.abs() > EPS);
	Vector unitB = B / B.abs();
	return unitB * (dot(A, B)) / B.abs();
}

Point midPoint(Point A, Point B) {
	return Point((A + B) / 2.0);
}

Double angle(Point A, Point B) {
	//return angle in [0 , PI]
	Double num = dot(A, B);
	Double den = A.abs() * B.abs();
	assert(fabs(den) >= EPS);
	Double cosine = num / den;
	if (near(cosine, 1)) return 0;
	if (near(cosine, -1)) return PI;
	return acos(num / den);
}

Double dist(Point A, Point B) {
	return sqrt(square(B.x - A.x) + square(B.y - A.y) + square(B.z - A.z));
}

Double triple(Point A, Point B, Point C) {
	return dot(A, cross(B, C));
}

//Line functions
struct Line{
	//L: P = O + t d, t is a real number
	Point O; //A point from the line
	Vector d; //directional vector of line
	Line(){}
	Line(Point A, Point B) {
		O = A;
		d = B - A;
	}
	bool operator ==(const Line L) const {
		Point zero(0, 0, 0);
		return cross(L.O - O, d) == zero && cross(d, L.d) == zero;
	}
	Point getPoint(Double t) {
		return O + t * d;
	}
};

Double dist(Line L, Point P) {
	return fabs(cross(L.d, P - L.O).abs() / L.d.abs());
}

Double dist(Line L1, Line L2) {
	Vector n = cross(L1.d, L2.d);
	if (n.abs() < EPS) return dist(L1, L2.O); //parallel
	//skew lines have distance > 0
	//intersecting lines hace distance = 0
	return fabs(dot(n, L1.O - L2.O) / n.abs());
}

vector<Point> intersect(Line L1, Line L2) {
	Vector d1 = L1.d;
	Vector d2 = L2.d;
	Vector n = cross(d1, d2);
	if (L1 == L2) return vector<Point>(2); //coincide
	if (n == Point(0, 0, 0)) return {}; //parallel
	Point P1 = L1.O;
	Point P2 = L2.O;
	Double t1 = cross(P2 - P1, d2) / n;
	Double t2 = cross(P1 - P2, d1) / (-1 * n);
	if (L1.getPoint(t1) == L2.getPoint(t2)) return {L1.getPoint(t1)};
	return {}; //skew
}
//Plane functions

struct Plane {
	//Point P belongs to the plane if: n.P = d
	//This is equivalent to equation ax + by + cz = d
	Vector n; //orthongal vector to the plane
	Double d; 
	Plane(){}
	Plane(Vector n, Double d): n(n), d(d){}
	Plane(Vector n, Point P) {
		this->n = n;
		d = dot(n, P);
	}
	Plane(Point A, Point B, Point C) {
		n = cross(B - A, C - A);
		d = dot(n, A);
	}
	Double evaluate(Point P) {
		return dot(n, P) - d;
	}
	bool contains(Point P) {
		return near(evaluate(P), 0);
	}
};

vector<Point> intersect(Plane P, Line L) {
	//empty vector -> Parallel lines
	//size 1 -> One point of intersection
	//size 2 -> Line inside plane
	if (near(dot(P.n, L.d), 0)) {
		if (near(P.evaluate(L.O), 0)) return vector<Point>(2);
		return {};
	}
	Double t = -P.evaluate(L.O) / dot(P.n, L.d);
	return {L.getPoint(t)};
}

vector<Line> intersect(Plane P1, Plane P2) {
	Vector d = cross(P1.n, P2.n);
	if (d == Point(0, 0, 0)) {
		if (P1.n * P2.d == P2.n * P1.d) return vector<Line>(2);
		return {};
	}
	Line ans;
	ans.d = d;
	ans.O = cross(P1.d * P2.n - P2.d * P1.n, d) / d.abs2();
	return {ans};
}

istream & operator >> (istream &in, Point &A){
	in >> A.x >> A.y >> A.z;
	return in;
}

ostream & operator << (ostream &out, const Point &A){
	out << A.x << " " << A.y << " " << A.z;
	return out;
}

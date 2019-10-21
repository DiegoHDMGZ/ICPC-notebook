#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long double Double;
typedef long long Long;
const Double EPS = 1e-10;
const Double INF = 1e17;

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
	Long x,y;
	
	Point(){
		x = 0;
		y = 0;
	}
	Point(Long _x, Long _y){
		x = _x, y = _y;
	}

	Point operator += (const Point &t){
		x += t.x;
		y += t.y;
		return *this;
	}
	Point operator -= (const Point &t){
		x -= t.x;
		y -= t.y;
		return *this;
	}
	Point operator *= (Long t){
		x *= t;
		y *= t;
		return *this;
	}
	Point operator +(const Point &t) const {
		return Point(*this) += t;
	}
	Point operator - (const Point &t) const{
		return Point(*this) -= t;
	}
	
	bool operator == (const Point &P) const {
		return P.x == x && P.y == y;
	}
	
	bool operator != (const Point &P) const {
		return !(P == Point(*this));
	}

	Long cross(const Point &P) const {
		return x * P.y - y * P.x;
	}
	
	Long cross(const Point &a , const Point &b) const {
		return (a - *this).cross(b - *this);
	}
	
	bool inTriangle(Point A, Point B , Point C) {
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
	
	Long inPolygon( vector<Point> &poly ) { //O(log n)
		//works with convex polygons in counter-clockwise order
		//use prepare (poly) before using it
		
		//-1 : not inside
		//0 : boundary
		//1 : inside
		Long n = poly.size();
		Point P = Point(*this);
		if(n == 1) {
			if(P == poly[0]) {
				return 0;
			} else{
				return -1;
			}
		}
		
		if(n == 2) {
			if(P.inSegment(poly[0] , poly[1])) {
				return 0;
			} else{
				return -1;
			}
		}
		
		//verify if the angle of the point lies between the angle of p0p1 and p0pn-1
		if(poly[0].cross(poly[1] , P)  != 0 
		    && sgn(poly[0].cross(poly[1] , P)  ) != sgn(poly[0].cross(poly[1] , poly[n - 1]) )) {
			return -1;
		}
		if(poly[0].cross(P , poly[n - 1]) != 0 
		    && sgn(poly[0].cross(P , poly[n - 1]) ) != sgn(poly[0].cross(poly[1] , poly[n - 1]) )) {
			return -1;
		}
	
		Long ini = 2;
		Long fin = n - 1;
		
		if(poly[0].cross(poly[ini], P) <= 0){
			fin = ini;
		} else {
			while(fin - ini > 1){ // hay mas de 2 valores
				Long med= (ini + fin) / 2;
				
				if(poly[0].cross(poly[med] , P) <= 0){
					fin=med;
				} 
				else {
					ini = med;
				}
			}
		}
		
		if(!P.inTriangle(poly[0] , poly[fin - 1] , poly[fin])) {
			return -1;
		}
		
		if(P.inSegment(poly[fin - 1] , poly[fin] )) {
			return 0;
		}
		if(P.inSegment(poly[0] , poly[1] )) {
			return 0;
		}
		if(P.inSegment(poly[0], poly[n - 1] )) {
			return 0;
		}
		return 1;
	}
	
	void debugPoint(string nombre){
		cout << nombre << " = ( " << fixed << setprecision(2) <<  x << " , " << y  << " ) " << endl; 
	}
	
};


void prepare(vector<Point> &poly) {
	Long sz = poly.size();
	Long pos = 0;
	
	for(Long i = 1; i < sz; i++) {
		if(poly[i].y < poly[pos].y || (poly[i].y == poly[pos].y && poly[i].x < poly[pos].x) ) {
			pos = i;
		}
	}
	rotate(poly.begin() , poly.begin() + pos , poly.end());
}


int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	*/
/*
6
1 2
-3 -2
2 -8
8 -8
14 0
8 4

8 4

*/
	vector<Point> v;
	cout << "N = ";
	Long N;
	cin >> N;
	
	cout << "Puntos (antihorario):" << endl;
	REP(i , N) {
		Point P;
		cin >> P.x >> P.y;
		v.pb(P);
	}
	prepare(v);
	cout << "queries : " << endl;
	while(true) {
		Point target;
		cin >> target.x >> target.y;
		Long x = target.inPolygon(v);
		if(x >= 0) {
			if(x == 0) {
				cout << "Borde" << endl;
			} else{
				cout << "Dentro" << endl;
			}
		} else {
			cout << "Fuera" << endl;
		}
	}
	return 0;
}

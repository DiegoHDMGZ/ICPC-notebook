#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

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

	
	Long cross(const Point &P) const {
		return x * P.y - y * P.x;
	}
	
	Long cross(const Point &a , const Point &b) const {
		return (a - *this).cross(b - *this);
	}
	
	void debugPoint(string nombre){
		cout << nombre << " = ( " << fixed << setprecision(2) <<  x << " , " << y  << " ) " << endl; 
	}
};

bool pointInTriangle(Point A, Point B , Point C , Point P) {
	//compare areas
	Long a1 = abs(A.cross(B , C));
	Long a2 = abs(P.cross(A , B)) + abs(P.cross(A , C)) + abs(P.cross(B , C));
	return a1 == a2;
}

void prepare(deque<Point> &poly) {
	Long sz = poly.size();
	Long pos = 0;
	
	for(Long i = 1; i < sz; i++) {
		if(poly[i].y < poly[pos].y || (poly[i].y == poly[pos].y && poly[i].x < poly[pos].x) ) {
			pos = i;
		}
	}
	rotate(poly.begin() , poly.begin() + pos , poly.end());
}

Long sgn(Long val) {
	if(val > 0) {
		return 1;
	}
	if(val < 0) {
		return -1;
	}
	return 0;
}

bool inSegment(Point A, Point B, Point target) {
	if(A.cross(B , target) == 0) {
		if(target.x >= min(A.x , B.x) && target.x <= max(A.x , B.x) && target.y >= min(A.y , B.y) && target.y <= max(A.y , B.y )) {
			return true;
		} 
	}
	return false;
}

Long pointInPolygon(Point P , deque<Point> &poly) {
	//works with convex polygons in counter-clockwise order
	
	//-1 : not inside
	//0 : boundary
	//1 : inside
	Long n = poly.size();
	
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
	
	if(!pointInTriangle(poly[0] , poly[fin - 1] , poly[fin] , P)) {
		return -1;
	}
	
	if(inSegment(poly[fin - 1] , poly[fin] , P)) {
		return 0;
	}
	if(inSegment(poly[0] , poly[1] , P)) {
		return 0;
	}
	if(inSegment(poly[0], poly[n - 1] , P)) {
		return 0;
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long N , M ,K;
	deque<Point> v;
	cin >> N >> M >> K;
	REP(i , N) {
		Point P;
		cin >> P.x >> P.y;
		v.pb(P);
	}
	prepare(v);
	
	Long cnt = 0;
	REP(i , M) {
		Point explo;
		cin >> explo.x >> explo.y;
		if(pointInPolygon(explo , v) != -1) {
			cnt++;
		}
	}
	if(cnt >= K) {
		cout << "YES" << endl;
	} else{
		cout << "NO" << endl;
	}
	return 0;
}


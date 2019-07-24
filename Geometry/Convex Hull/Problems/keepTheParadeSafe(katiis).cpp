#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long INF = 1e18;

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
	
	Long cross(const Point &P) const {
		return x * P.y - y * P.x;
	}
	
	Long cross(const Point &a , const Point &b) const {
		return (a - *this).cross(b - *this);
	}
	
	bool operator == (const Point &P) const {
		return x == P.x && y == P.y;
	}
	
	bool operator != (const Point &P) const {
		return !(Point(*this) == P);
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
	
	Long inPolygon( vector<Point> &poly ) {
		//works with convex polygons in counter-clockwise order
		//use prepare (poly) before use it
		
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

Point center;

Long squareDist(Point P1 , Point P2) {
	return (P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y);
}

bool cmp(const Point &P1 , const Point &P2) {
	if(center.cross(P1 , P2) == 0) {
		return squareDist(center, P1) < squareDist(center, P2);
	}
	return center.cross(P1 , P2) > 0;
}

void prepare(vector<Point> &v) { //O(n)
	Long n = v.size();
	vector<Point> transf;
	Long i = 1;
	transf.pb(v[0]);
	while(i < n) {
		if(v[i] == v[0]) {
			i++;
			continue;
		}
		if(i + 1< n ) {
			if(v[0].cross(v[i] , v[i + 1]) == 0) {
				while(i + 1 < n && v[0].cross(v[i] , v[i + 1]) == 0) {
					i++;
				}
				transf.pb(v[i]);
				i++;
				continue;
			}
		} 
		transf.pb(v[i]);
		i++;
	}
	v = transf;
}

vector<Point> convexHull(vector<Point> v) { //O( n log n)
//gives the convex hull in counter clockwise order
	center = Point(INF , INF);
	Long n = v.size();
	REP(i , n) {
		if( make_pair(v[i].y , v[i].x) < make_pair(center.y , center.x) ) {
			center = v[i];
		}
	}
	sort(v.begin(),v.end(), cmp);
	
	prepare(v);
	n = v.size();
	vector<Point> hull;
	if(n < 3) {
		return v;
	}
	hull.pb(v[0]);
	hull.pb(v[1]);
	hull.pb(v[2]);
	for(Long i = 3 ; i < n; i++) {
		Long sz = hull.size();
		Point ant1 = hull[sz - 1];
		Point ant2 = hull[sz - 2];
		while(ant1.cross(v[i] , ant2) <= 0) {
			hull.pop_back();
			sz--;
			ant1 = hull[sz - 1];
			ant2 = hull[sz - 2];
		}
		hull.pb(v[i]);
	}
	return hull;
}

void prepare2(vector<Point> &poly) {
	Long sz = poly.size();
	Long pos = 0;
	
	for(Long i = 1; i < sz; i++) {
		if(poly[i].y < poly[pos].y || (poly[i].y == poly[pos].y && poly[i].x < poly[pos].x) ) {
			pos = i;
		}
	}
	rotate(poly.begin() , poly.begin() + pos , poly.end());
}

Long inside(vector<Point> & castle, vector<Point> &hull) {
	prepare2(hull);
	Long sz = castle.size();
	Long ans = 0;
	REP(i , sz) {
		if(castle[i].inPolygon(hull) >= 0) {
			ans++;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<Point> v;
	Long n;
	cin >> n;
	REP(i , n) {
		Point P;
		cin >> P.x >> P.y;
		v.pb(P); 
	}
	vector<Point> hull = convexHull(v);
	
	Long S;
	cin >> S;
	vector<Point> castle;
	REP(i, S) {
		Point P;
		cin >> P.x >> P.y;
		castle.pb(P);
	}
	
	if(hull.size() <= 2) {
		cout << 0 << endl;
		return 0;
	}
	if(hull.size() >= 4) {
		cout << inside(castle , hull) << endl;
		return 0;
	}
	
	prepare2(hull);
	Long a = 0, b = 0 , c = 0;
	REP(i , n) {
		if(v[i].inPolygon(hull) == 1)	{
			cout << inside(castle , hull) << endl;
			return 0;
		} else {
			if(v[i] != hull[0] && v[i] != hull[1] && v[i] != hull[2]) {
				if(v[i].inSegment(hull[0], hull[1])) {
					a++;
				} else if(v[i].inSegment(hull[1] , hull[2])) {
					b++;
				} else if(v[i].inSegment(hull[0] , hull[2])){
					c++;
				}
			}
		}
	}

	Long cnt = 0;
	if(a > 0) {
		cnt++;
	}
	if(b > 0) {
		cnt++;
	}
	if(c > 0) {
		cnt++;
	}
	if(cnt == 3) {
		cout << inside(castle , hull) << endl;
		return 0;
	}
	if(cnt <= 1) {
		cout << 0 << endl;
		return 0;
	}
	//cnt = 2
	Point ign;
	if(a == 0) {
		ign = hull[2];
	} else if(b == 0) {
		ign = hull[0];
	} else {
		ign = hull[1];
	}
	vector<Point> newV;
	REP(i , n) {
		if(v[i] != ign) {
			newV.pb(v[i]);
		}
	}
	hull = convexHull(newV);
	assert((Long)(hull.size()) == 4);
	
	cout << inside(castle , hull) << endl;
	return 0;
}


#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long INF = 1e18;
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
	
	void debugPoint(string nombre){
		cout << nombre << " = ( " << fixed << setprecision(2) <<  x << " , " << y  << " ) " << endl; 
	}
};

Point center;

Long squareDist(Point P1 , Point P2) {
	return (P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y);
}

long double dist(Point P1 , Point P2) {
	return sqrt(squareDist( P1 ,  P2));
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

vector<Point> convexHull(vector<Point> &v) { //O( n log n)
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



void test() {
	map<pair<Long,Long> , Long> key;
	vector<Point> v;
	Long n;
	cin >> n;
	REP(i , n) {
		Point P;
		cin >> P.x >> P.y;
		v.pb(P);
		if(key[{P.x , P.y}] == 0) {
			key[{P.x , P.y}] = i + 1;
		}
	}
	vector<Point> hull = convexHull(v);
	
	long double ans = 0.0;
	Long sz = hull.size();
	REP(i , sz) {
		ans += dist(hull[i] , hull[(i + 1) % sz]);
	}
	cout << fixed << setprecision(2) << ans << endl;
	REP(i , sz) {
		cout << key[{hull[i].x, hull[i].y}] << " ";
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	while(T--) {
		test();
	}
	
	return 0;
}


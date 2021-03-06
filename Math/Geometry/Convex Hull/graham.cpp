#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

struct Point{
	Long x,y;
	
	Point() : x(0), y(0) {}
	Point(Long x, Long y) : x(x) , y(y){}

	Point operator -= (const Point &t){
		x -= t.x;
		y -= t.y;
		return *this;
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

bool cmp(const Point &P1 , const Point &P2) {
	if(center.cross(P1 , P2) == 0) {
		return squareDist(center, P1) < squareDist(center, P2);
	}
	return center.cross(P1 , P2) > 0;
}

vector<Point> convexHull(vector<Point> &v) { //O( n log n)
//gives the convex hull in counter clockwise order
	center = v[0];
	Long n = v.size();
	REP(i , n) {
		if( make_pair(v[i].y , v[i].x) < make_pair(center.y , center.x) ) {
			center = v[i];
		}
	}
	sort(v.begin(),v.end(), cmp);
	auto it = unique(v.begin(), v.end());
	v.resize(distance(v.begin(),it));
	n = v.size();
	vector<Point> hull;
	
	if(n < 3) {
		return v;
	}
	hull.pb(v[0]);
	hull.pb(v[1]);
	for(Long i = 2 ; i < n; i++) {
		Long sz = hull.size();
		Point prev1 = hull[sz - 1];
		Point prev2 = hull[sz - 2];
		while(prev1.cross(v[i] , prev2) <= 0) {
			hull.pop_back();
			sz--;
			if(sz < 2) break;
			prev1 = hull[sz - 1];
			prev2 = hull[sz - 2];
		}
		hull.pb(v[i]);
	}
	return hull;
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
	REP(i , hull.size()) {
		hull[i].debugPoint("hull[" + to_string(i) + "]");
	}
	return 0;
}


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

struct Line{
	Long A , B ,C;
	//AX + BY + C = 0
	
	Line(){	}
	
	Line(Point P1, Point P2){
		A = P1.y - P2.y;
		B = P2.x - P1.x;
		C = -A*P1.x  - B*P1.y;	
	}
	
	Long calc(Point P) {
		return P.x * A + P.y * B + C;
	}
	
	void debugLine(string nombre){
		cout << nombre << " : " << A << "x + " << B << "y + " << C << " = 0" << endl;
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


pair<Point,Point> farthestPair(vector<Point> &v) { //O( n log n)
	vector<Point> P = convexHull(v);
	Long n = P.size();
	
	if(n <= 1) {
		return make_pair(Point(-INF, - INF)  , Point(-INF , -INF));
	}
	if(n == 2) {
		return make_pair(P[0] , P[1]);
	}
	vector<pair<Point,Point> > antipodal;
	
	Long i = 0;
	Long j = (i + 2) % n;
	while( i < n) { //O(n)
		//Find the maximum distance from edge hull[i - j]
		Line L(P[i] , P[(i + 1) % n]);
		Long d = L.calc(P[j]);
		j = (j + 1) % n;	
		while(d < L.calc(P[j])) {
			d = L.calc(P[j]);
			j = (j + 1) % n;
		}
		Long ant = (j - 1 + n) % n;
		antipodal.pb({P[i] , P[ant]});
		antipodal.pb({P[(i + 1) % n] , P[ant]});
		if(L.calc(P[j]) == d) {
			antipodal.pb({P[i] , P[j]});
			antipodal.pb({P[(i + 1) % n] , P[j]});
		}
		j = (j - 1 + n) % n;
		i++;
	}
	Long maxDist = -1;
	pair<Point, Point> choice;
	REP(i , antipodal.size() ) {
		if(squareDist(antipodal[i].first , antipodal[i].second) > maxDist) {
			maxDist = squareDist(antipodal[i].first , antipodal[i].second);
			choice = antipodal[i];
		} 
	}
	return choice;
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
	
	Long Q;
	cin >> Q;
	REP(q , Q) {
		Long l,r;
		cin >> l >> r;
		l--;
		r--;
		vector<Point> query;
		for(Long i = l; i <= r; i++) {
			query.pb(v[i]);
		}
		pair<Point,Point> p = farthestPair(query);
		cout << squareDist(p.first, p.second) << endl;
	}
	
	return 0;
}


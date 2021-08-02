#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

struct Point{
	Long x, y;
	
	Point(Long x = 0, Long y = 0) : x(x) , y(y){}

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
	hull.push_back(v[0]);
	hull.push_back(v[1]);
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
		hull.push_back(v[i]);
	}
	return hull;
}

pair<Point,Point> farthestPair(vector<Point> &v) { //O(n log n)
	vector<Point> P = convexHull(v);
	Long n = P.size();
	
	if(n <= 1) {
		return make_pair(P[0], P[0]);
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
		antipodal.push_back({P[i] , P[ant]});
		antipodal.push_back({P[(i + 1) % n] , P[ant]});
		if(L.calc(P[j]) == d) {
			antipodal.push_back({P[i] , P[j]});
			antipodal.push_back({P[(i + 1) % n] , P[j]});
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
	return 0;
}


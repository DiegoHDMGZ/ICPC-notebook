#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
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

bool cmp(const Point &P1 , const Point &P2) {
	if(P1.x == P2.x){
		return P1.y < P2.y;
	}
	return P1.x < P2.x;
}

vector<Point> convexHull(vector<Point> &v) { //O( n log n)
	//gives the convex hull in counter clockwise order
	Long n = v.size();
	sort(v.begin(),v.end(), cmp);
	
	auto it = unique(v.begin(), v.end());
	v.resize(distance(v.begin(),it));
	n = v.size();
	
	if(n < 3) {
		return v;
	}
	
	vector<Point> hull; //lower hull at the beginning
	vector<Point> upperHull;
	
	Point A = v[0];
	Point B = v.back();
	
	hull.push_back(A);
	upperHull.push_back(A);
	for(Long i = 1 ; i < n; i++) {
		if(i == n - 1 || v[i].cross(A , B) > 0){
			//upper
			Long sz = upperHull.size();
			while(sz >= 2 && upperHull[sz - 1].cross(upperHull[sz - 2] , v[i]) <= 0){
				upperHull.pop_back();
				sz--;
			}
			upperHull.push_back(v[i]);
		} 
		if(i == n - 1 || v[i].cross(A , B) < 0){
			//lower
			Long sz = hull.size();
			while(sz >= 2 && hull[sz - 1].cross(hull[sz - 2] , v[i]) >= 0){
				hull.pop_back();
				sz--;
			}
			hull.push_back(v[i]);
		}
	}

	for(Long i = (Long)upperHull.size() - 2; i >= 1; i--) hull.push_back(upperHull[i]);
	return hull;
}

int main() {
	return 0;
}


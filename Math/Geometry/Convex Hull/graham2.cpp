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
	
	vector<Point> hull; //lower envelope at the beginning
	vector<Point> upperEnv;
	
	Point A = v[0];
	Point B = v.back();
	
	hull.push_back(A);
	upperEnv.push_back(A);
	for(Long i = 1 ; i < n; i++) {
		if(i == n - 1 || v[i].cross(A , B) > 0){
			//upper
			Long sz = upperEnv.size();
			while(sz >= 2 && upperEnv[sz - 1].cross(upperEnv[sz - 2] , v[i]) <= 0){
				upperEnv.pop_back();
				sz--;
			}
			upperEnv.push_back(v[i]);
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

	for(Long i = (Long)upperEnv.size() - 2; i >= 1; i--) hull.push_back(upperEnv[i]);
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


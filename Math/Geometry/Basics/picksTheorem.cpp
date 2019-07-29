#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//Pick's Theorem : A = I + B / 2 - 1
// I = (2A - B + 2) / 2

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

Long area2(vector<Point> &v) { //O(n)
	//el doble del area
	Long ans = 0;
	Long sz = v.size();
	for(Long i = 0; i < sz; i++) {
		Point P = v[(i - 1 + sz) % sz ];
		Point Q = v[i];
		ans += (P.x - Q.x) * (P.y + Q.y);
	}
	return abs(ans);
}

Long boundaryPoints(Point A, Point B) { //O(1)
	return __gcd(abs(A.x - B.x) , abs(A.y - B.y)) + 1;
}

Long boundaryPoints(vector<Point> &v) { //O(n)
	Long n = v.size();
	Long ans = 0;
	for(Long i = 0; i < n; i++) {
		ans += boundaryPoints(v[i] , v[(i - 1 + n) % n]);
	}
	return ans - n;
}

Long interiorPoints(vector<Point> &v) { //O(n)
	return (area2(v) - boundaryPoints(v) + 2) / 2;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	cin >> n;
	vector<Point> v;
	REP(i , n) {
		Point P;
		cin >> P.x >> P.y;
		v.pb(P);
	}
	double A = area2(v) / 2.0;
	debug(A);
	Long B = boundaryPoints(v);
	debug(B);
	Long I = interiorPoints(v);
	debug(I);
	
	return 0;
}


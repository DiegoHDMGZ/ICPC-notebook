#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef long double Double;

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
	
	bool operator == (const Point &P) const {
		return P.x == x && P.y == y;
	}
	
	bool operator != (const Point &P) const {
		return !(P == Point(*this));
	}

	void debugPoint(string nombre){
		cout << nombre << " = ( " << fixed << setprecision(2) <<  x << " , " << y  << " ) " << endl; 
	}
	
};

bool cmpX(const Point &P1 , const Point &P2) {
	return (P1.x != P2.x ? P1.x < P2.x : P1.y < P2.y);
}

bool cmpY(const Point &P1 , const Point &P2) {
	return (P1.y != P2.y ? P1.y < P2.y : P1.x < P2.x);
}

Long squareDist(Point P1 , Point P2) {
	return (P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y);
}

Double dist(Point P1, Point P2) {
	return sqrt(squareDist(P1 , P2));
}

Double perimeter(Point P1, Point P2, Point P3) {
	return dist(P1 ,P2) + dist(P2 , P3) + dist(P3 , P1);
}

Double minPerimeter(vector<Point> &X , vector<Point> &Y) { //O(n log n)
	Long n = X.size();
	assert((Long)(X.size()) == (Long)(Y.size()));
	if(n <= 5) {
		Double minPer = INF;
		for(Long i = 0; i < n; i++) {
			for(Long j = i + 1; j < n ; j++) {
				for(Long k = j + 1; k < n; k++) {
					minPer = min(minPer, perimeter(X[i] , X[j], X[k]));
				}
			}
		}
		return minPer;
	}
	vector<Point> XL;
	vector<Point> XR;
	vector<Point> YL;
	vector<Point> YR;
	Long mid = n / 2;
	for(Long i = 0; i < mid; i++) {
		XL.pb(X[i]);
		if(cmpX(Y[i] , X[mid])) {
			YL.pb(Y[i]);
		} else {
			YR.pb(Y[i]);
		}
	}
	for(Long i = mid; i < n; i++) {
		XR.pb(X[i]);
		if(cmpX(Y[i] , X[mid])) {
			YL.pb(Y[i]);
		} else {
			YR.pb(Y[i]);
		}
	}
	
	Double ans = min(minPerimeter(XL, YL ) , minPerimeter(XR, YR));
	
	vector<Point> YP;
	for(Long i = 0; i < n; i++) { 
		if(abs(X[mid].x - Y[i].x)  <= 2 * ans) {
			YP.pb(Y[i]);
		}
	}
	Long sz = YP.size();
	REP(i , sz) { 
		Long j = i + 1;
		while(j < sz && (YP[j].y - YP[i].y) <= ans) { // 16 points maximum
			Long k = j + 1;
			while(k < sz && (YP[k].y - YP[i].y) <= ans) {
				ans = min(ans , perimeter(YP[i] , YP[j] , YP[k]));
				k++;
			}
			j++;
		}
	}

	return ans;
}

Double minPerimeter(vector<Point> &v) { //O( n log n)
	Long n = v.size();
	vector<Point> X = v;
	vector<Point> Y = v;
	sort(X.begin() , X.end() , cmpX);
	sort(Y.begin() , Y.end() , cmpY);
	REP(i , n - 1) {
		if(X[i] == X[i + 1]) {
			return 0.0;
		}
	}
	return minPerimeter(X , Y);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	while(cin >> n) {
		if(n == -1) {
			break;
		}
		vector<Point> v;
		REP(i , n) {
			Point P;
			cin >> P.x >> P.y;
			v.pb(P);
		}
		Double ans = minPerimeter(v);
		cout << fixed << setprecision(3) << ans << endl;
	}

	
	return 0;
}


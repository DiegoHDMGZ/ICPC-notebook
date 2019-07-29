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

Long dist(Point P1 , Point P2) {
	return abs(P1.x - P2.x) + abs(P1.y - P2.y);
}


pair<Point, Point> combine(pair<Point, Point> D1, pair<Point, Point> D2) { //O(1)
	if(dist(D1.first , D1.second) > dist(D2.first, D2.second)) {
		swap(D1 , D2);
	}
	return D1;
}

pair<Point,Point> closestPair(vector<Point> &X , vector<Point> &Y) { //O(n log n)
	Long n = X.size();
	assert((Long)(X.size()) == (Long)(Y.size()));
	if(n <= 3) {
		pair<Point,Point> minPair = {X[0] , X[1]};
		for(Long i = 0; i < n; i++) {
			for(Long j = i + 1; j < n ; j++) {
				minPair = combine(minPair , {X[i] , X[j]});
			}
		}
		return minPair;
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
	
	pair<Point,Point> ans = combine(closestPair(XL, YL ) , closestPair(XR, YR));
	Long d = dist(ans.first, ans.second);
	
	vector<Point> YP;
	for(Long i = 0; i < n; i++) { 
		if(abs(X[mid].x - Y[i].x)  <= d) {
			YP.pb(Y[i]);
		}
	}
	Long sz = YP.size();
	REP(i , sz) { //one pair from L and one from R
		Long j = i + 1;
		while(j < sz && abs(YP[j].y - YP[i].y)  <= d) { // 12 points upper bound
			ans = combine(ans , {YP[i] , YP[j]});
			j++;
		}
	}

	return ans;
}

pair<Point, Point> closestPair(vector<Point> &v) { //O( n log n)
	Long n = v.size();
	vector<Point> X = v;
	vector<Point> Y = v;
	sort(X.begin() , X.end() , cmpX);
	sort(Y.begin() , Y.end() , cmpY);
	REP(i , n - 1) {
		if(X[i] == X[i + 1]) {
			return {X[i] , X[i + 1]};
		}
	}
	return closestPair(X , Y);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
/*
9
18 -2
10 3
-47 4
33 3
-25 0
-13 4
-13 -2
-35 0
24 2
Rpta: manhattan distance = 6 con (-13 , 4) y (-13, -2)

*/
	vector<Point> v;
	Long n;
	cin >> n;
	REP(i , n) {
		Point P;
		cin >> P.x >> P.y;
		v.pb(P); 
	}
	pair<Point,Point> f = closestPair(v);
	
	f.first.debugPoint("P1");
	f.second.debugPoint("P2");
	
	return 0;
}


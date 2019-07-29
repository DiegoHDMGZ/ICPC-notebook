#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

struct Point{
	Long x,y;
	Long index;
	Long tipo;
	Point(){
		x = 0;
		y = 0;
	}
	Point(Long _x, Long _y, Long ind , Long t){
		x = _x, y = _y , index = ind , tipo = t;
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
		cout << nombre << " = ( "  <<  x << " , " << y  << " , " << index << " ) " << endl; 
	}
	
};

bool cmpX(const Point &P1 , const Point &P2) {
	return (P1.x != P2.x ? P1.x < P2.x : P1.y < P2.y);
}

bool cmpY(const Point &P1 , const Point &P2) {
	return (P1.y != P2.y ? P1.y < P2.y : P1.x < P2.x);
}

const Long INF = 1e18;
Long squareDist(Point P1 , Point P2) {
	if(P1.index == P2.index) {
		return INF;
	}
	return (P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y);
}


pair<Point, Point> combine(pair<Point, Point> D1, pair<Point, Point> D2) { //O(1)
	if(squareDist(D1.first , D1.second) > squareDist(D2.first, D2.second)) {
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
	Long d = squareDist(ans.first, ans.second);
	
	vector<Point> YP;
	for(Long i = 0; i < n; i++) { 
		if((X[mid].x - Y[i].x) * (X[mid].x - Y[i].x) <= d) {
			YP.pb(Y[i]);
		}
	}
	Long sz = YP.size();
	REP(i , sz) { //one pair from L and one from R
		Long j = i + 1;
		while(j < sz && (YP[j].y - YP[i].y) * (YP[j].y - YP[i].y) <= d) { // 7 points maximum
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
		if(X[i] == X[i + 1] && X[i].index != X[i + 1].index) {
			return {X[i] , X[i + 1]};
		}
	}
	return closestPair(X , Y);
}


Long opo(Long s) {
	return 5 - s;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	vector<Point> v;
	Long n;
	cin >> n;
	REP(i , n) {
		Point P;
		cin >> P.x >> P.y;
		P.index = i + 1;
		P.tipo = 1;
		v.pb(P);
		if(P.x != 0) {
			v.pb(Point(-P.x , P.y , i + 1, 2));
		}
		if(P.y != 0) {
			v.pb(Point(P.x , -P.y, i + 1, 3));
		}
		if(P.x != 0 && P.y != 0) {
			v.pb(Point(-P.x , -P.y, i + 1, 4));
		}
		
	}
	pair<Point,Point> f = closestPair(v);

	cout << f.first.index << " " << f.first.tipo << " " << f.second.index << " " << opo(f.second.tipo) << endl;
	return 0;
}


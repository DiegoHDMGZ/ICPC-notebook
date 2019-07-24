#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define RANDOM mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define unif(a,b) uniform_int_distribution<int>(a,b)(rng)

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

Long minManhattan(vector<Point> &v) { //O( n log n)
	Long n = v.size();
	vector<Point> X = v;
	vector<Point> Y = v;
	sort(X.begin() , X.end() , cmpX);
	sort(Y.begin() , Y.end() , cmpY);
	REP(i , n - 1) {
		if(X[i] == X[i + 1]) {
			return 0;
		}
	}
	pair<Point,Point> p = closestPair(X,Y);
	return dist(p.first, p.second);
}

Long bruteforce(vector<Point> &v) {
	Long sz = v.size();
	Long minDist = 1e18;
	REP(i , sz ) {
		for(Long j = i + 1; j < sz; j++) {
			minDist = min(minDist , dist(v[i], v[j]));
		}
	}
	return minDist;
}

RANDOM;
void test() {
	Long N = unif(100 , 1000);
	vector<Point> v;
	REP(i , N) {
		Long x = unif(-1e9 , 1e9);
		Long y = unif(-1e9 , 1e9);
		v.pb(Point(x , y));
	}
	if(bruteforce(v) != minManhattan(v)) {
		debug(N);
		REP(i , N) {
			cout << v[i].x << " " << v[i].y << endl;
		}
		cout << "***************" << endl << endl;
		system("pause");
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long T = 100;
	while(T--) {
		test();
	}
	
	return 0;
}


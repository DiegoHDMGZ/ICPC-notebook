#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef long double Double;

struct Point{
	Double x,y;
	
	Point(){
		x = 0;
		y = 0;
	}
	Point(Double _x, Double _y){
		x = _x, y = _y;
	}

	
	bool operator == (const Point &P) const {
		return P.x == x && P.y == y;
	}
	
	bool operator != (const Point &P) const {
		return !(P == Point(*this));
	}
	
};

bool cmpX(const Point &P1 , const Point &P2) {
	return (P1.x != P2.x ? P1.x < P2.x : P1.y < P2.y);
}

bool cmpY(const Point &P1 , const Point &P2) {
	return (P1.y != P2.y ? P1.y < P2.y : P1.x < P2.x);
}

Double dist(Point P1 , Point P2) {
	return sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y) );
}


pair<Point, Point> combine(pair<Point, Point> D1, pair<Point, Point> D2) { //O(1)
	if(dist(D1.first , D1.second) > dist(D2.first, D2.second)) {
		swap(D1 , D2);
	}
	return D1;
}

void debugVector(vector<Point> &v, string s) {
	cout << s << " = { ";
	REP(i , v.size()) {
		cout << "( " << v[i].x << "," << v[i].y << " ) ";
	}
	cout << endl;
}

const Long INF = 1e18;
pair<Point,Point> closestPair(vector<Point> &X , vector<Point> &Y) { //O(n log n)
	Long n = X.size();
	assert((Long)(X.size()) == (Long)(Y.size()));
	if(n <= 3) {
		Double minD = 1e18;
		pair<Point,Point> minPair;
		for(Long i = 0; i < n; i++) {
			for(Long j = i + 1; j < n ; j++) {
				if(dist(X[i] , X[j]) < minD) {
					minD = dist(X[i] , X[j]);
					minPair = {X[i] , X[j]};
				}
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
		if(fabs(X[mid].x - Y[i].x)  <= d) {
			YP.pb(Y[i]);
		}
	}
	Long sz = YP.size();
	REP(i , sz) { //one pair from L and one from R
		Long j = i + 1;
		while(j < sz && fabs(YP[j].y - YP[i].y) <= d) { // 7 points maximum
			ans = combine(ans , {YP[i] , YP[j]});
			j++;
		}
	}
	return ans;
}

Double closestPair(vector<Point> &v) { //O( n log n)
	Long n = v.size();
	if(n <= 1) {
		return INF;
	}
	vector<Point> X = v;
	vector<Point> Y = v;
	sort(X.begin() , X.end() , cmpX);
	sort(Y.begin() , Y.end() , cmpY);
	REP(i , n - 1) {
		if(X[i] == X[i + 1]) {
			return 0;
		}
	}
	pair<Point, Point> p = closestPair(X , Y);
	return dist(p.first, p.second);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	while(cin >> n) {
		if(n == 0) {
			break;
		}
		vector<Point> v;
		REP(i , n) {
			Point P;
			cin >> P.x >> P.y;
			v.pb(P);
		}
		Double ans = closestPair(v);
		if(ans >= 10000) {
			cout << "INFINITY" << endl;
		} else{
			cout << fixed << setprecision(4) << ans << endl;
		}
	}
	
	return 0;
}


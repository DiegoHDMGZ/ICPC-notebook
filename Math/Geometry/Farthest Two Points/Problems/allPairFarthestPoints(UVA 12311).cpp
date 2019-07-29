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



const Long MAX = 4e4;
Long maxPair[MAX];
Long maxDist[MAX];

void farthestPairs(vector<Point> &P) { //O( n)
	Long n = P.size();
	REP(i , n) {
		maxPair[i] = 1e18;
		maxDist[i] = -1;
	}
	
	vector<pair<Long,Long> > antipodal;
	
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
		antipodal.pb({i ,ant});
		antipodal.pb({(i + 1) % n , ant});
		if(L.calc(P[j]) == d) {
			antipodal.pb({i , j});
			antipodal.pb({(i + 1) % n , j});
		}
		j = (j - 1 + n) % n;
		i++;
	}
	
	REP(i , antipodal.size()) {
		Long a = antipodal[i].first;
		Long b = antipodal[i].second;
		if(squareDist(P[a] , P[b]) > maxDist[a]) {
			maxDist[a] = squareDist(P[a] , P[b]);
			maxPair[a] = b + 1;
		} else if(squareDist(P[a] , P[b]) == maxDist[a]) {
			maxPair[a] = min(maxPair[a] , b + 1);
		}
		
		if(squareDist(P[a] , P[b]) > maxDist[b]) {
			maxDist[b] = squareDist(P[a] , P[b]);
			maxPair[b] = a + 1;
		} else if(squareDist(P[a] , P[b]) == maxDist[b]) {
			maxPair[b] = min(maxPair[b] , a + 1);
		}
	}
	
	REP(i , n) {
		cout << maxPair[i] << endl;
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
/*
14
17 833
30 296
67 15
877 2
912 12
946 40
969 96
998 172
999 932
985 962
943 983
776 987
366 994
17 993
0
*/
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
		farthestPairs(v);
	}

	
	return 0;
}


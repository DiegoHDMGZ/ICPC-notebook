#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
Long n, k;

const Long MX = 2000;
Long X[MX];
Long w[MX];

const Long INF = 1e18;
struct Line{
	Long m , b;
	Line(){}
	Line(Long m , Long b) : m(m), b(b){}
	
	bool operator < (const Line &L1) const {
		return m < L1.m;
	}
	
	Long val(Long x){
		return m * x + b;
	}
};

struct CHT{
	deque<Line> envelope;
	
	void clear(){
		envelope.clear();
	}
	
	Long div(Long a, Long b){ //floored division
		assert(b != 0);
		return a / b - ((a ^ b) < 0 && a % b); 
	}
	
	Long intersect(Line l1, Line l2){
		return div(l1.b - l2.b , l2.m - l1.m );
	}
	
	bool bad(Line l1, Line l2, Line l3){
		//tells if l2 is bad an can be eliminated by l3
		return intersect(l2 , l3) <= intersect(l1, l2);
	}

	void addLine(Line l3){
		l3.m *= -1;
		l3.b *= -1;
		if(envelope.size() == 0) {
			envelope.push_back(l3);
			return;
		}
		if(l3.m == envelope.back().m){
			if(l3.b > envelope.back().b){
				envelope.pop_back();
			} else {
				return;
			}
		}
		if(envelope.size() <= 1) {
			envelope.push_back(l3);
			return;
		}
		Long sz = envelope.size();
		Line l1 = envelope[sz - 2];
		Line l2 = envelope[sz - 1];
		while(bad(l1 , l2 , l3) ) {
			envelope.pop_back();
			if(envelope.size() == 1) {
				break;
			}
			sz = envelope.size();
			l1 = envelope[sz - 2];
			l2 = envelope[sz - 1];
		}
		envelope.push_back(l3);
	}
	
	Long maxY(Long x){ //O(log n)
		assert(!envelope.empty());
		while(envelope.size() >= 2 && intersect(envelope[0], envelope[1]) < x){
			envelope.pop_front();
		}
		return -envelope.front().val(x);
	}
	
}cht[MX];

Long dp[MX][MX];
Long P[MX];
Long Q[MX];

void solve(){
	REP(i , n){
		cin >> X[i] >> w[i];
	}
	P[0] = Q[0] = 0;
	REP(i , n){
		P[i + 1] = P[i] + w[i];
		Q[i + 1] = Q[i] + X[i] * w[i];
	}
	
	cht[0].clear();
	cht[0].addLine(Line(X[n - 1] , X[n - 1] * P[n] - Q[n] ));
	for(Long j = 1; j <= k; j++){
		cht[j].clear();
		for(Long i = n - 1; i >= 0; i--){
			dp[i][j] = cht[j - 1].maxY(-P[i]) + Q[i];
			if(i < n - 1){
				cht[j].addLine(Line(X[i] , X[i] * P[i + 1] - Q[i + 1] + dp[i + 1][j]));
			}
			
		}
	}
	cout << dp[0][k] << endl;
	
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	/*freopen("input.txt", "r" , stdin);
	freopen("output.txt" , "w" , stdout);*/
	while(cin >> n >> k){
		solve();
	}

	return 0;
}

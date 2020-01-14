#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 2e6;
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
	vector<Line> envelope;

	bool check( Long med, Long x ){
		return envelope[med + 1].val(x) - envelope[med].val(x) <= 0;
	}

	Long search(  Long ini , Long fin, Long x ){ //O(logn)
		// F F F... V V V
		if(!check(fin - 1, x)) return envelope[fin].val(x); //todos F
		if(check(ini, x)) return envelope[ini].val(x); //todos V
		while(fin - ini > 1){ // hay mas de 2 valores
			Long med= ini + (fin - ini) / 2;
			
			if(check( med , x )){
				fin = med;
			} 
			else {
				ini = med;
			}
		}
		//hay 2 valores ini es F y fin es V
		return envelope[fin].val(x);
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

	void build(vector<Line> &lines){ //O(n log n)
		sort(lines.begin(), lines.end() );
		for(Line l : lines){
			addLine(l);
		}
	}
	
	Long maxY(Long x){ //O(log n)
		assert(!envelope.empty());
		return search(0, (Long)envelope.size() - 1, x);
	}
	
}cht;
struct Point{
	Long x, y , a;
}P[MX];

Long dp[MX];

bool cmp(const Point &P1, const Point &P2){
	return P1.x < P2.x;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	cin >> n;
	REP(i , n){
		cin >> P[i].x >> P[i].y >> P[i].a;
	}
	sort(P, P + n, cmp);
	
	cht.addLine(Line(0, 0));
	for(Long i = 0; i < n; i++){
		dp[i] = P[i].x * P[i].y - P[i].a;
		Long best = cht.maxY(-P[i].y);
		dp[i] += best;
		cht.addLine(Line(P[i].x , dp[i]));
	}
	Long ans = 0;
	for(Long i = 0; i < n; i++){
		ans = max(ans , dp[i]);
	}
	cout << ans << endl;
	return 0;
}

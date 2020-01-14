#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/contest/1083/problem/E

const Long MX = 2e6;
struct Point{
	Long x, y , a;
}P[MX];

bool cmp(const Point &P1, const Point &P2){
	return P1.x < P2.x;
}

struct Line{
	mutable Long m , b , rInter;
	Line(){}
	Line(Long m , Long b, Long rInter) : m(m), b(b) , rInter(rInter){}
	Line(Long m , Long b) : m(m), b(b) , rInter(0){}
	
	bool operator < (const Line &L1) const {
		return m < L1.m;
	}
	
	bool operator < (const Long &x) const {
		return rInter < x;
	}
	
	Long val(Long x){
		return m * x + b;
	}
};

const Long INF = 1e18;

struct CHT{
	set<Line , less<>> envelope;
	
	Long div(Long a, Long b){ //floored division
		return a / b - ((a ^ b) < 0 && a % b); 
	}
	
	Long intersect(Line l1, Line l2){
		return div(l1.b - l2.b , l2.m - l1.m );
	}
	
	bool bad(Line l1, Line l2, Line l3){
		//tells if l2 is bad an can be eliminated by l3
		//intersection of l2 , l3 left of intersection of l1, l2
		return intersect(l2 , l3) <= intersect(l1, l2);
	}
	
	void addLine(Line L){ //O(log n)
		L.rInter = INF;
		auto it = envelope.lower_bound(L);
		if(it != envelope.end()){ //same slope
			if(it->m == L.m){
				if(it->b >= L.b){
					return;
				} else {
					it = envelope.erase(it);
				}
			}
		}
		if(it != envelope.begin()){
			if(it != envelope.end()){
				if(bad(*prev(it), L , *it)){ //L is not necessary
					return;
				} 
			}
			it--;
			while(it != envelope.begin()){ //left elimination
				if(bad(*prev(it), *it, L)){
					it = envelope.erase(it);
					it--;
				} else {
					break;
				}
			}
			it->rInter = intersect(*it, L);
		} 
		
		it = envelope.upper_bound(L);
		
		if(it != envelope.end()){
			while(next(it) != envelope.end()){ //right elimination
				if(bad(L , *it, *next(it))){
					it = envelope.erase(it);
				} else {
					break;
				}
			}
			L.rInter = intersect(L , *it);
		}
		envelope.insert(L);
	}
	
	Long maxY(Long x){ //O(log n)
		assert(!envelope.empty());
		Line L = *envelope.lower_bound(x);
		return L.val(x);
	}
	
}cht;

Long dp[MX];

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
		Long best = cht.maxY(P[i].y);
		dp[i] += best;
		cht.addLine(Line(-P[i].x , dp[i]));
	}
	Long ans = 0;
	for(Long i = 0; i < n; i++){
		ans = max(ans , dp[i]);
	}
	cout << ans << endl;
	return 0;
}

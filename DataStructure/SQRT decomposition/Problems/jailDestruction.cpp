#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
 
using namespace std;
 
typedef long long Long;

//https://codeforces.com/gym/102307/problem/J
 
const Long MX = 1e5 + 8;
const Long SQ = sqrt(MX) + 8;
vector<pair<Long,Long>> v[SQ];
Long acum[SQ][SQ];

struct SQRT{

	Long lazy[SQ];
	 
	Long n, sq;
	
	void setN(Long x){
		n = x;
		sq = sqrt(n) + 1;
	}
	 
	Long block(Long i){
		return i / sq;
	}
	 
	Long lowerLim(Long i){
		return (i / sq)* sq;
	}
	 
	Long upperLim(Long i ){
		return min(lowerLim(i) + sq - 1 , n - 1);
	}
	 
	void update(Long l , Long r , Long x){
		if(l > r) return;
		if(block(l) == block(r)){
			Long b = block(l);
			Long sz = v[b].size();
			for(Long i = 0; i < sz; i++){
				v[b][i].first = max(0LL, v[b][i].first - lazy[b]);
				if(v[b][i].second >= l && v[b][i].second <= r){
					v[b][i].first = max(0LL , v[b][i].first - x);
				}
			}
			lazy[b] = 0;
			sort(v[b].begin() , v[b].end());
			for(Long i = 0; i < sz; i++){
				acum[b][i + 1] = acum[b][i] +  v[b][i].first;
			}
			return;
		}
		update(l , upperLim(l) , x);
		update(lowerLim(r) , r , x);
		Long l0 = block(l) + 1;
		Long r0 = block(r) - 1;
		for(Long i = l0; i <= r0; i++){
			lazy[i] += x;
		} 
	}
	 
	Long query(Long l , Long r){
		if(l > r) return 0;
		
		if(block(l) == block(r)){
			Long b = block(l);
			Long ans = 0;
			Long sz = v[b].size();
			for(Long i = 0; i < sz; i++){
				if(v[b][i].second >= l && v[b][i].second <=r ){
					ans += max(v[b][i].first - lazy[b] , 0LL);;
				}
			}
			return ans;
		}
		Long ans = 0;
		ans += query(l , upperLim(l));
		ans += query(lowerLim(r), r);
		Long l0 = block(l) + 1;
		Long r0 = block(r ) - 1;
		for(Long i = l0; i <= r0; i++){
			pair<Long,Long> aux = {lazy[i], -1};
			auto it = lower_bound(v[i].begin(), v[i].end(), aux);
			if(it == v[i].end()) continue;
			Long ind = it - v[i].begin();
			Long sz = v[i].size();
			sz--;
			ans += acum[i][sz + 1] - acum[i][ind] - lazy[i] * (sz - ind + 1);
		}
		return ans;
	}
}sq;

 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n , q;
	cin >> n  >> q;
	sq.setN(n);
	
	REP(i , n){
		Long h;
		cin >> h;
		v[sq.block(i)].pb({h, i}); 
	}
	REP(i , sq.sq){
		sort(v[i].begin(), v[i].end());
		for(Long j = 0; j < v[i].size(); j++){
			acum[i][j + 1] = acum[i][j] + v[i][j].first;
		}
	}
	REP(i , q){
		Long tipo;
		cin >> tipo;
		Long a, b;
		cin >> a >> b;
		a--;
		b--;
		if(tipo == 1){
			Long ans = 0;
			if(a <= b){
				ans = sq.query(a , b);
			} else {
				ans = sq.query(0 , b) + sq.query(a , n - 1);
			}
			cout << ans << endl;
			
		} else {
			Long x;
			cin >> x;
			if(a <= b){
				sq.update(a , b , x);
			} else {
				sq.update(0 , b , x);
				sq.update(a , n - 1, x);
			}
		}
	}

	return 0;
}

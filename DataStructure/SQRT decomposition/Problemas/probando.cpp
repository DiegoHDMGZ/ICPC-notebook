#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
 
using namespace std;
 
typedef long long Long;
 
//https://www.spoj.com/problems/UPDATEIT/
const Long MX = 1e4 + 5;
const Long SQ = sqrt(MX) + 1;

struct SQRT{
	Long A[MX];
	Long ans[SQ];
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
	
	void clear(Long N){
		if(n == 0){
			return;
		}
		for(Long i = 0; i < N; i++){
			A[i] = 0;
			ans[block(i)] = 0;
			lazy[block(i)] = 0;
		}
		n = 0;
		sq = 0;
	}
	
	void build(vector<Long> &v){
		setN(v.size());
		for(Long i = 0; i < n; i++){
			A[i] = v[i];
			ans[block(i)] += v[i];
		}
	}
	 
	void update(Long l , Long r , Long x){
		if(l > r) return;
		if(block(l) == block(r)){
			Long b = block(l);
			for(Long i = lowerLim(l); i <= upperLim(l); i++){
				//update all the block with lazy
				A[i] += lazy[b];
			}
			lazy[b] = 0;
			for(Long i = l; i <= r; i++){
				A[i] += x;
				ans[b] += x;
			}
			return;
		}
		update(l , upperLim(l) , x);
		update(lowerLim(r) , r , x);
		l = upperLim(l) + 1;
		r = lowerLim(r) - 1 ;
		for(Long i = l; i <= r; i+= sq){
			ans[block(i)] += x * (upperLim(i) - lowerLim(i) + 1);
			lazy[block(i)] += x;
		} 
	}
	 
	Long query(Long l , Long r){
		if(l > r) return 0;
		
		if(block(l) == block(r)){
			Long b = block(l);
			Long sum = 0;
			for(Long i = l; i <= r; i++){
				sum += A[i] + lazy[b];
			}
			return sum;
		}
		Long sum = 0;
		sum += query(l , upperLim(l));
		sum += query(lowerLim(r), r);
		l = upperLim(l) + 1;
		r = lowerLim(r) - 1 ;
		for(Long i = l; i <= r; i+= sq){
			sum += ans[block(i)];
		} 
		return sum;
	}
}sq;

 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Long T;
	cin >> T;
	REP(t, T){
		Long n;
		cin >> n;
		sq.clear(n);
		sq.setN(n);
		Long u;
		cin >> u;
		REP(i , u){
			Long l , r , x;
			cin >> l >> r >> x;

			sq.update(l , r , x);
		}
		Long q;
		cin >> q;
		REP( i , q){
			Long pos;
			cin >> pos;
			cout << sq.query(pos , pos) << "\n";
		}
	}
	return 0;
}
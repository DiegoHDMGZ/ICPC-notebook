#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

pair<Long,Long> combine(pair<Long,Long> a, pair<Long,Long> b){
	if(a.second > b.second) return a;
	else return b;
}

struct SegmentTree{
	pair<Long,Long> t[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = {0, -1};
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl, Long tr){ //O(n)
		if(tl == tr){
			t[id] = {a[tl], 0};
		}
		else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = {0, -1};
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	pair<Long,Long> query(Long pos, Long id , Long tl , Long tr ){ //O(logn)
		if(tl == tr) return t[id];	

		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1 ;
		
		if(pos <= tm){
			return combine(t[id] , query(pos, left , tl, tm));
		}
		else{
			return combine(t[id] ,  query(pos, right, tm + 1, tr));
		}
	}
	
	Long query(Long pos) {
		assert(maxN > 0);
		return query(pos , 1 , 0 , maxN - 1).first;
	}
	
	void update(Long l, Long r, Long val, Long prior, Long id, Long tl, Long tr ){ //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			t[id] = {val, prior};
		}else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			update(l, r, val , prior , left, tl, tm);
			update(l, r, val , prior ,right, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Long val, Long prior) {
		assert(maxN > 0);
		update(l , r , val, prior, 1 , 0 , maxN - 1);
	}
} st;

struct Brute{
	vector<Long> a;
	
	void build(vector<Long> a){
		this->a = a;
	}
	
	void update(Long l , Long r, Long val){
		for(Long i = l; i <= r ; i++){
			a[i] = val;
		}
	}
	
	Long query(Long pos){
		return a[pos];
	}
	
}brute;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

void solve(){
	Long n = random(1 , 10);
	vector<Long> v(n);
	for(Long i = 0; i < n; i++){
		v[i] = random(-100, 100);
	}
	
	brute.build(v);
	st.build(v);
	Long q = 1000;
	for(Long i = 0; i < q; i++){
		if(random(0 , 1) == 0){
			Long l = random(0, n - 1);
			Long r = random(l , n - 1);
			Long val = random( 0 , 1);

			st.update(l , r , val, i + 1);
			brute.update(l , r  , val);
		} else{
			Long pos = random(0 , n - 1);
			if(brute.query(pos) != st.query(pos)){
				debug(pos);
				debug(st.query(pos));
				debug(brute.query(pos));
			}
			
			assert(brute.query(pos) == st.query(pos));
		}
		
		
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 100;
	REP(t, T ) solve();
	return 0;
}

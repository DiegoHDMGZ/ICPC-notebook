#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree{
	Long t[4 * MX];
	bool marked[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
			marked[i] = false;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl, Long tr){ //O(n)
		marked[id] = false;
		if(tl == tr){
			t[id] = a[tl];
		}
		else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = 0;
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long id){ //O(1)
		if(marked[id]){
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			t[left] = t[right] = t[id];
			marked[left] = marked[right] = true;
			marked[id] = false;
		}
	}
	
	Long query(Long pos, Long id , Long tl , Long tr ){ //O(logn)
		if(tl == tr) return t[id];	
		if(marked[id]){
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1 ;
		push(id);
		if(pos <= tm){
			return query(pos, left , tl, tm);
		}
		else{
			return query(pos, right, tm + 1, tr);
		}
	}
	
	Long query(Long pos) {
		assert(maxN > 0);
		return query(pos , 1 , 0 , maxN - 1);
	}
	
	void update(Long l, Long r, Long val, Long id, Long tl, Long tr ){ //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			t[id] = val;
			marked[id] = true;
		}else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id);
			update(l, r, val , left, tl, tm);
			update(l, r, val , right, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Long val) {
		assert(maxN > 0);
		update(l , r , val, 1 , 0 , maxN - 1);
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
	Long n = random(1 , 1000);
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
			Long val = random( -1000, 1000);

			st.update(l , r , val);
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

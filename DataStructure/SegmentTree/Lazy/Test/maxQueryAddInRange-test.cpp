#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

Long combine(Long x, Long y){
	return max(x, y);
}

struct SegmentTree {
	Long t[4 * MX];
	Long lazy[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
			lazy[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl , Long tr ) { //O(n)
		lazy[id] = 0;
		if (tl == tr) {
			t[id] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = max(t[left], t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long id) { //O(1)
		Long left = 2 * id;
		Long right = 2 * id + 1;
		t[left] += lazy[id];
		lazy[left] += lazy[id];
		t[right] += lazy[id];
		lazy[right] += lazy[id];
		lazy[id] = 0;
	}

	Long query(Long l, Long r, Long id , Long tl, Long tr ) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		push(id);
		if(r < tm + 1){
			return query(l , r , left , tl , tm);
		}else if(tm < l){
			return query(l , r, right , tm + 1 , tr);  
		} else{
			return combine(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Long add, Long id , Long tl , Long tr) { //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			t[id] += add;
			lazy[id] += add;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id);
			update(l, r, add , left, tl, tm);
			update(l, r, add , right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void update(Long l , Long r, Long add) {
		assert(maxN > 0);
		update(l, r , add , 1 , 0 , maxN - 1);
	}
} st;

struct Brute{
	vector<Long> a;
	
	void build(vector<Long> a){
		this->a = a;
	}
	
	void update(Long l , Long r, Long val){
		for(Long i = l; i <= r ; i++){
			a[i] += val;
		}
	}
	
	Long query(Long l, Long r){
		Long maxi = a[l];
		for(Long i = l; i <= r; i++) maxi = max(maxi , a[i]);
		return maxi;
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
		v[i] = random(-1000, 1000);
	}
	
	brute.build(v);
	st.build(v);
	Long q = 1000;
	for(Long i = 0; i < q; i++){
		if(random(0 , 1) == 0){
			Long l = random(0, n - 1);
			Long r = random(l , n - 1);
			Long val = random(-100 , 100);

			st.update(l , r , val);
			brute.update(l , r  , val);
		} else{
			Long l = random(0 , n - 1);
			Long r = random(l , n - 1);
			/*if(brute.query(l , r) != st.query(l, r)){
				debug(l);
				debug(st.query(pos));
				debug(brute.query(pos));
			}*/
			
			assert(brute.query(l , r) == st.query(l , r));
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

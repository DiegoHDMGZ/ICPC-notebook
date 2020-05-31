#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long INF = 1e18;
const Long MX = 1e5;

Long combine(Long x, Long y){
	return min(x , y);
}

struct SegmentTree {
	multiset<Long> t[2 * MX]; //O(nlogn)
	Long curVal[MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i].clear();
			curVal[i] = INF;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a , Long id , Long tl , Long tr) { //O(nlog²n)
		if (tl == tr){
			t[id] = {a[tl]};
			curVal[tl] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a , left, tl, tm);
			build(a , right, tm + 1, tr);
			t[id] = t[left];
			t[id].insert(t[right].begin(), t[right].end());
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long x , Long id , Long tl , Long tr) { //O(log²n)
		//find the smallest number greater or equal to X
		if(tr < l || tl > r){
			return INF;
		}

		if (l <= tl && tr <= r) {
			auto it = t[id].lower_bound(x);
			if (it != t[id].end()) {
				return *it;
			} else{
				return INF;
			}
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;

		return combine(query(l, r, x , left, tl, tm) , query(l, r, x , right, tm + 1, tr));
	}
	
	Long query(Long l , Long r , Long x) {
		assert(maxN > 0);
		return query(l , r , x , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long val , Long id , Long tl, Long tr ) { //O(log²n)
		t[id].erase(t[id].find(curVal[pos]));
		t[id].insert(val);
		if(tl == tr){
			curVal[pos] = val;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val , right, tm + 1, tr);
			}
		} 
	}
	
	void update(Long pos , Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;


struct Brute{
	vector<Long> a;
	void build(vector<Long> a){
		this->a = a;
	}
	
	void update(Long pos ,Long val){
		a[pos] = val;
	}
	
	Long query(Long l , Long r, Long x){
		Long ans = INF;
		for(Long i = l; i <= r; i++){
			if(a[i] >= x)ans = min(ans , a[i]);
		}
		return ans;
	}
}brute;
mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

void solve(){
	Long n = random(1 , 1000);

	vector<Long> v(n);
	REP(i , n){
		v[i] = random(-2000 , 2000);
	}
	st.build(v);
	brute.build(v);
	Long Q = 10;
	REP(q, Q){
		if(random(0 , 1) == 0){
			Long pos, val;
			pos = random(0, n - 1);
			val = random(-20 , 50);
			st.update(pos, val);
			brute.update(pos , val);
		} else{
			Long l , r , x;
			l = random(0 , n - 1);
			r = random(l , n - 1);
			x = random(-100 , 100);
			assert(st.query(l , r , x) == brute.query(l , r , x));
		}
	}
}

int main() {
	Long T = 100;
	REP(t, T ) solve();
	return 0;
}

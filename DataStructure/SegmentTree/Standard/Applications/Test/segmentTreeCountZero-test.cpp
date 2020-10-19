#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree{
	Long t[2 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a , Long id , Long tl  , Long tr) { //O(n)
		if (tl == tr){
			a[tl] == 0 ? t[id] = 1 : t[id] = 0;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = t[left] + t[right];
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long countZeros(Long l, Long r, Long id  , Long tl , Long tr) { //O(logn)
		//# of zeros in interval
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if(r < tm + 1){
			//only left child
			return countZeros(l , r , left , tl , tm);
		}else if(tm < l){
			//only right child
			return countZeros(l , r, right , tm + 1 , tr); 
		} else{
			//both children
			return countZeros(l, r, left, tl, tm) + countZeros(l, r, right, tm + 1, tr);
		}
	}
	
	Long countZeros(Long l , Long r) {
		assert(maxN > 0);
		return countZeros(l , r , 1 , 0 , maxN - 1);
	}

	Long find_kth(Long k, Long id, Long tl, Long tr) { //(O(logn)
		//k-th zero , 1-indexed
		if (k > t[id]) {
			return -1;
		}
		if (tl == tr) {
			return tl;
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if (t[left] >= k) {
			return find_kth(k, left, tl, tm);
		}else {
			return find_kth(k - t[left], right, tm + 1, tr);
		}
	}
	
	Long find_kth(Long k) {
		assert(k > 0);
		assert(maxN > 0);
		return find_kth(k , 1 , 0 , maxN - 1);
	}


	void update(Long pos, Long val, Long id , Long tl , Long tr ) { //O(logn)
		if (tl == tr) {
			val == 0 ? t[id] = 1 : t[id] = 0;
		}else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val, right, tm + 1, tr);
			}
			t[id] = t[left] + t[right];
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;

struct Brute{
	vector<Long> v;
	void build(vector<Long> v){
		this->v = v;
	}
	
	Long countZeros(Long l , Long r){
		Long ans = 0;
		for(Long i = l ; i <= r; i++){
			if(v[i] == 0) ans++;
		}
		return ans;
	}
	
	Long find_kth(Long k){
		Long cnt = 0;
		for(Long i = 0; i < v.size(); i++){
			if(v[i] == 0) cnt++;
			if(cnt == k) return i;
		}

		return -1;
	}
	
	void update(Long pos, Long val){
		v[pos] = val;
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
		v[i] = 1;
		if(random(0 , 100) <= 70){
			v[i] = 0;
		} 
	}
	/*debug(n);
	for(Long i = 0; i < n; i++){
		cout << v[i] << " ";
	}
	cout << endl;*/
	brute.build(v);
	st.build(v);
	Long q = 1e7 / n;
	for(Long i = 0; i < q; i++){
		Long pos , val;
		pos = random(0 , n - 1);
		val = random( 0 , 1);
		st.update(pos , val);
		brute.update(pos , val);
		Long l = random(0, n - 1);
		Long r = random(l , n - 1);
		assert(brute.countZeros(l , r) == st.countZeros(l , r));
		assert(brute.find_kth(i + 1) == st.find_kth(i + 1));
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 10;
	REP(t , T ) solve();
	
	return 0;
}


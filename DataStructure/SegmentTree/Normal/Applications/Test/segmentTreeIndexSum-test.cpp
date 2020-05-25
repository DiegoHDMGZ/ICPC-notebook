#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
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
	
	void build(vector<Long> &a, Long id , Long tl , Long tr ){ //O(n)
		if(tl == tr){
			t[id] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a , left , tl , tm);
			build(a , right , tm + 1 , tr);
			t[id] = t[left] + t[right];
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long findInd(Long sum, Long id , Long tl , Long tr  ){ //O(logn)
		//min index where the prefix sum is >= target
		//it only works if the array is of non-negative numbers
		if(sum > t[id]){
			return -1;
		}
		if(tl == tr){
			return tl;
		}
		Long tm= (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if(t[left] >= sum){
			return findInd(sum , left , tl , tm);
		}else{
			return findInd(sum - t[left] , right, tm + 1 ,tr);
		}
	}
	
	Long findInd(Long sum) {
		assert(maxN > 0);
		return findInd(sum , 1 , 0 , maxN - 1);
	}
	
	void update(Long pos, Long val, Long id , Long tl , Long tr ){ //O(logn)
		if(tl == tr){
			t[id] = val;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if(pos <= tm){
				update(pos, val , left , tl, tm);
			}else{
				update(pos, val, right , tm + 1, tr);
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
	
	Long findInd(Long sum){
		Long acum = 0;
		for(Long i = 0; i < v.size(); i++){
			acum += v[i];
			if(acum >= sum){
				return i ;
			}
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
		v[i] = random(0, 1000);
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
		val = random( 0 , 1000);
		st.update(pos , val);
		brute.update(pos , val);
		Long sum = random(0 , 1000);
		if(brute.findInd(sum) != st.findInd(sum)){
			debug(sum);
			debug(brute.findInd(sum));
			debug(st.findInd(sum));
		}
		
		assert(brute.findInd(sum) == st.findInd(sum));
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


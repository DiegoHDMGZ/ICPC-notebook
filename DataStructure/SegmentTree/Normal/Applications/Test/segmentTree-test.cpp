#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define getMatrix(n , m) vector<vector<Long>>(n , vector<Long>(m, 0))
using namespace std;

typedef long long Long;

const Long MX = 1e5;

Long combine(Long x , Long y) {
	return x + y;
}

Long cntQuery;
Long cntUpdate;
struct SegmentTree{
	Long t[4 * MX];
	
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl , Long tr) { //O(n)
		if (tl == tr){
			t[id] = a[tl];
		} else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left] , t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long id , Long tl , Long tr ) { //O(logn)
		cntQuery++;
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		if(r < tm + 1){
			//only left child
			return query(l , r , left , tl , tm);
		}else if(tm < l){
			//only right child
			return query(l , r, right , tm + 1 , tr);  
		} else{
			//both children
			return combine(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}
	
	void update(Long pos, Long val, Long id, Long tl , Long tr) { //O(logn)
		cntUpdate++;
		if (tl == tr) {
			t[id] = val;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val, right, tm + 1, tr);
			}
			t[id] = combine(t[left] , t[right] );
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val, 1 , 0 , maxN - 1);
	}
} st;


mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

long double getTime(){
	return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

void solve(){
	Long n = random(1024 ,1024);
	vector<Long> A(n);
	for(Long i = 0; i < n; i++){
		A[i]= random(-10, 10);
	}
	st.build(A);
	
	Long q = 1;

	REP(i , q){
		Long pos , val;
		pos = random(0 , n - 1);
		val = random(-100, 100);
		cntUpdate = 0;

		st.update(pos, val);
		
		debug(cntUpdate);
		
		assert(cntUpdate <= (ceil(log2(n) + 1) ));
		
		Long l = 1, r = n - 2;

		cntQuery = 0;
		Long stQuery = st.query(l , r);

		debug(cntQuery);
		assert(cntQuery <= 4 * (ceil(log2(n))) - 3  );
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 1;
	REP(t , T) solve();

	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.hackerrank.com/contests/stryker-codesprint/challenges/kth-zero/problem

const Long MX = 1e5;

struct SegmentTree{
	Long t[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a , Long id , Long tl  , Long tr) { //O(n)
		if(tl > a.size()){
			return;
		}
		if (tl == tr){
			a[tl] == 0 ? t[id] = 1 : t[id] = 0;
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a, 2 * id, tl, tm);
			build(a, 2 * id + 1, tm + 1, tr);
			t[id] = t[2 * id] + t[2 * id + 1];
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
		if(tm < l){
			//only right child
			return countZeros(l , r, 2 * id + 1 , tm + 1 , tr); 
		} else if(r < tm + 1){
			//only left child
			return countZeros(l , r , 2 * id , tl , tm);
		} else{
			//both children
			return countZeros(l, r, 2 * id, tl, tm) + countZeros(l, r, 2 * id + 1, tm + 1, tr);
		}
	}
	
	
	Long countZeros(Long l , Long r) {
		assert(maxN > 0);
		return countZeros(l , r , 1 , 0 , maxN - 1);
	}

	Long find_kth(Long k, Long id, Long tl, Long tr) { //(O(logn)
		//k-th zero
		if (k > t[id]) {
			return -1;
		}
		if (tl == tr) {
			return tl;
		}
		Long tm = (tl + tr) / 2;
		if (t[2 * id] >= k) {
			return find_kth(k, 2 * id, tl, tm);
		}
		else {
			return find_kth(k - t[2 * id], 2 * id + 1, tm + 1, tr);
		}
	}
	
	Long find_kth(Long k) {
		assert(maxN > 0);
		return find_kth(k , 1 , 0 , maxN - 1);
	}


	void update(Long pos, Long val, Long id , Long tl , Long tr ) { //O(logn)
		if (tl == tr) {
			val == 0 ? t[id] = 1 : t[id] = 0;
		}
		else {
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, val, 2 * id, tl, tm);
			}
			else {
				update(pos, val, 2 * id + 1, tm + 1, tr);
			}
			t[id] = t[2 * id] + t[2 * id + 1];
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n , q;
	cin >> n >> q;
	vector<Long> v(n);
	REP(i , n){
		cin >> v[i];
	}
	st.build(v);
	
	REP(i , q){
		Long type;
		cin >> type;
		if(type == 1){
			Long k;
			cin >> k;
			Long ans = st.find_kth(k);
			if(ans == -1){
				cout << "NO\n";
			} else{
				cout <<  ans << "\n";
			}
			
		} else {
			Long p;
			Long val;
			cin >> p >> val;
			st.update(p, val);
		}
	}

	return 0;
}

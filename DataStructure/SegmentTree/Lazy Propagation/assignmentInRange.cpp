#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree{
	Long lazy[4 * MX];
	bool marked[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			lazy[i] = 0;
			marked[i] = false;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl, Long tr) { //O(n)
		marked[id] = false;
		if (tl == tr) {
			lazy[id] = a[tl];
		} else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			lazy[id] = 0;
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long id) { //O(1)
		if (marked[id]) {
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			
			//aggregate the lazy value to the lazy value of the children
			lazy[left] = lazy[right] = lazy[id];
			marked[left] = marked[right] = true;
			
			//restart the lazy value
			marked[id] = false;
		}
	}
	
	Long query(Long pos, Long id, Long tl, Long tr) { //O(logn)
		if (tl == tr) return lazy[id];	
		if (marked[id]) {
			return lazy[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1 ;
		push(id);
		if (pos <= tm) {
			return query(pos, left , tl, tm);
		} else{
			return query(pos, right, tm + 1, tr);
		}
	}
	
	Long query(Long pos) {
		assert(maxN > 0);
		return query(pos , 1 , 0 , maxN - 1);
	}
	
	void update(Long l, Long r, Long val, Long id, Long tl, Long tr) { //O(logn)
		if (tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			lazy[id] = val;
			marked[id] = true;
		} else {
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

int main() {
	return 0;
}

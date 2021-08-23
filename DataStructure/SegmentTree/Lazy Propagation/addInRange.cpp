#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
const Long MX = 1e5;

struct SegmentTree {
	Long t[2 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i <  2 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id, Long tl, Long tr) { //O(n)
		if (tl == tr) {
			t[id] = a[tl];
		} else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = 0;
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long pos, Long id, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if (pos <= tm) {
			return t[id] + query(pos, left, tl, tm);
		}else {
			return t[id] + query(pos, right, tm + 1, tr);
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
			t[id] += val;
		} else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			update(l, r, val , left, tl, tm);
			update(l, r, val , right, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Long val) {
		assert(maxN > 0);
		update(l , r, val, 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MAX = 1e5;

struct SegmentTree {
	Long t[4 * MAX];

	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear() {
		for(Long i = 0; i < 4 * MAX; i++) {
			t[i] = 0;
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a, Long v, Long tl, Long tr ) { //O(n)
		if (tl == tr) {
			t[v] = a[tl];
		}
		else {
			Long tm = (tl + tr) / 2;
			build(a, 2 * v, tl, tm);
			build(a, 2 * v + 1, tm + 1, tr);
			t[v] = 0;
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long get(Long pos, Long v, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			return t[v];
		}
			
		Long tm = (tl + tr) / 2;
		if (pos <= tm) {
			return t[v] + get(pos, 2 * v, tl, tm);
		}
		else {
			return t[v] + get(pos, 2 * v + 1, tm + 1, tr);
		}
	}
	
	Long get(Long pos ) {
		assert(maxN > 0);
		return get(pos , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Long add, Long v, Long tl , Long tr ) { //O(logn)
		if (l > r) {
			return;
		}
			
		if (l == tl && r == tr) {
			t[v] += add;
		}
		else {
			Long tm = (tl + tr) / 2;
			update(l, min(r, tm), add, 2 * v, tl, tm);
			update(max(l, tm + 1), r, add, 2 * v + 1, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Long add) {
		assert(maxN > 0);
		update(l , r, add, 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;
const Long MAX = 100000;
const Long INF = 1e18;

struct SegmentTree {
	Long t[4 * MAX];
	Long lazy[4 * MAX];
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear() {
		for(Long i = 0; i < 4 * MAX; i++) {
			t[i] = 0;
			lazy[i] = 0;
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a, Long v , Long tl , Long tr ) { //O(n)
		if (tl == tr) {
			t[v] = a[tl];
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a, 2 * v, tl, tm);
			build(a, 2 * v + 1, tm + 1, tr);
			t[v] = max(t[2 * v], t[2 * v + 1]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long v) { //O(1)
		t[2 * v] += lazy[v];
		lazy[2 * v] += lazy[v];
		t[2 * v + 1] += lazy[v];
		lazy[2 * v + 1] += lazy[v];
		lazy[v] = 0;
	}

	Long query(Long l, Long r, Long v , Long tl, Long tr ) { //O(logn)
		if (l > r) {
			return -INF;
		}
		
		if (l == tl && r == tr) {
			return t[v];
		}
		push(v);
		Long tm = (tl + tr) / 2;
		return max(query(l, min(r, tm), 2 * v, tl, tm), query(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr));
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Long addend, Long v , Long tl , Long tr) { //O(logn)
		if (l > r) {
			return;
		}
		if (l == tl && r == tr) {
			t[v] += addend;
			lazy[v] += addend;
		}
		else{
			push(v);
			Long tm = (tl + tr) / 2;
			update(l, min(r, tm), addend, 2 * v, tl, tm);
			update(max(l, tm + 1), r, addend, 2 * v + 1, tm + 1, tr);
			t[v] = max(t[2 * v], t[2 * v + 1]);
		}
	}
	
	void update(Long l , Long r, Long add) {
		assert(maxN > 0);
		update(l, r , add , 1 , 0 , maxN - 1);
	}
} st;

int main(){
	return 0;
}

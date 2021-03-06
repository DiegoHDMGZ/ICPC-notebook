#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

Long combine(Long x, Long y){
	return x + y;
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
	
	void build(vector<Long> &a, Long id, Long tl, Long tr) { //O(n)
		lazy[id] = 0;
		if (tl == tr) {
			t[id] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long id, Long tl, Long tr) { //O(1)
		Long left = 2 * id;
		Long right = 2 * id + 1;
		Long tm = (tl + tr) / 2;
		Long szLeft = tm - tl + 1;
		Long szRight = tr - tm;
		//Apply the lazy value of the node to the children
		t[left] += lazy[id] * szLeft;
		t[right] += lazy[id] * szRight;
		
		//aggregate the lazy value to the lazy value of the children
		lazy[left] += lazy[id];
		lazy[right] += lazy[id];
		
		//restart the lazy value
		lazy[id] = 0;
	}

	Long query(Long l, Long r, Long id, Long tl, Long tr) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		push(id, tl , tr);
		if (r < tm + 1) {
			return query(l , r , left , tl , tm);
		} else if (tm < l) {
			return query(l , r, right , tm + 1 , tr);  
		} else{
			return combine(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Long val, Long id, Long tl, Long tr) { //O(logn)
		if (tr < l || tl > r) {
			return;
		}
		if (l <= tl && tr <= r) {
			Long sz = tr - tl + 1;
			t[id] += val * sz;
			lazy[id] += val;
		} else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id, tl , tr);
			update(l, r, val , left, tl, tm);
			update(l, r, val , right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void update(Long l, Long r, Long val) {
		assert(maxN > 0);
		update(l, r , val , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

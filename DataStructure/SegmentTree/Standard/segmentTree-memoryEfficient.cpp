#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 1e5;

Long combine(Long x , Long y) {
	return x + y;
}

struct SegmentTree{
	Long t[2 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id, Long tl, Long tr) { //O(n)
		if (tl == tr){
			t[id] = a[tl];
		} else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1);
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left] , t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long id, Long tl, Long tr) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1);
		if (r < tm + 1) {
			//only left child
			return query(l , r , left , tl , tm);
		} else if (tm < l) {
			//only right child
			return query(l , r, right , tm + 1 , tr); 
		} else{
			//both children
			return combine(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Long query(Long l, Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}
	
	void update(Long pos, Long val, Long id, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[id] = val;
		} else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1);
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			} else {
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

int main(){
	return 0;
}

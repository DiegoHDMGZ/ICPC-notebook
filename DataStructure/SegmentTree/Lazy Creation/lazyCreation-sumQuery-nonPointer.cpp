#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

Long combine(Long x, Long y){
	return x + y;
}

const int MX = 1e9;
const int MX_U = 1e5;
const int MX2 = 4 * (63 - __builtin_clzll(MX)) * MX_U + 1;
  
struct SegmentTree {
	Long sum[MX2];
	Long lazy[MX2];
	int left[MX2];
	int right[MX2];
	int nodes;
	Long n;
	
	void build(Long n) {
		for (int i = 1; i <= nodes; i++) {
			left[i] = 0;
			right[i] = 0;
			sum[i] = 0;
			lazy[i] = 0;
		}
		nodes = 1;
		this->n = n;
	}
	
	void push(int id, Long tl , Long tr) { //O(1)
		if (left[id] == 0) {
			//Create children if they dont exist
			left[id] = ++nodes;
			right[id] = ++nodes;
		}	
		Long tm = (tl + tr) / 2;
		Long szLeft = tm - tl + 1;
		Long szRight = tr - tm;
		
		//Apply the lazy value of the node to the children
		sum[left[id]] += szLeft * lazy[id];
		sum[right[id]] += szRight * lazy[id];
		
		//aggregate the lazy value of the node to the lazy value of the children
		lazy[left[id]] += lazy[id];
		lazy[right[id]] += lazy[id];
		
		//restart the lazy value
		lazy[id] = 0;
	}
	
	Long query(Long l, Long r, int id , Long tl, Long tr ) { //O(logn)
		if (l <= tl && tr <= r) return sum[id];
		Long tm = (tl + tr) / 2;
		push(id, tl , tr);
		if (r < tm + 1) return query(l , r , left[id] , tl , tm);
		else if (tm < l) return query(l , r, right[id] , tm + 1 , tr);  
		else{
			return combine(query(l, r, left[id], tl, tm) , query(l, r, right[id], tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(n > 0);
		return query(l , r , 1 , 0 , n - 1);
	}

	void update(Long l, Long r, Long val, int id, Long tl , Long tr) { //O(logn)
		if (tr < l || tl > r) return;
		if (l <= tl && tr <= r) {
			sum[id] += (tr - tl + 1) * val;
			lazy[id] += val;
		} else {
			Long tm = (tl + tr) / 2;
			push(id, tl , tr);
			update(l, r, val , left[id], tl, tm);
			update(l, r, val , right[id], tm + 1, tr);
			sum[id] = combine(sum[left[id]] , sum[right[id]]);
		}
	}
	
	void update(Long l , Long r, Long val) {
		assert(n > 0);
		update(l, r , val , 1 , 0 , n - 1);
	}
}st;

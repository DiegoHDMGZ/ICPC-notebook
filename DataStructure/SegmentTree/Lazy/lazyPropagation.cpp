#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MAX = 100000;

struct SegmentTree{
	Long t[4 * MAX];
	bool marked[4 * MAX];
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	} 
	
	void clear() {
		for(Long i = 0; i < 4 * MAX; i++) {
			t[i] = 0;
			marked[i] = false;
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a, Long v , Long tl, Long tr){ //O(n)
		if(tl == tr){
			t[v] = a[tl];
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a, 2 * v , tl , tm);
			build(a, 2 * v + 1, tm + 1 , tr);
			t[v] = 0;
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long v){ //O(1)
		if(marked[v]){
			t[2 * v] = t[2 * v + 1] = t[v];
			marked[2 * v] = marked[2 * v + 1] = true;
			marked[v] = false;
		}
	}
	
	Long get(Long pos, Long v , Long tl , Long tr ){ //O(logn)
		if(tl == tr) return t[v];	
		if(marked[v]){
			return t[v];
		}
		Long tm = (tl + tr) / 2;
		if(pos <= tm){
			return get(pos, 2 * v , tl, tm);
		}
		else{
			return get(pos,2 * v + 1, tm + 1, tr);
		}
	}
	
	Long get(Long pos) {
		assert(maxN > 0);
		return get(pos , 1 , 0 , maxN - 1);
	}
	
	void update(Long l, Long r, Long val, Long v, Long tl, Long tr ){ //O(logn)
		if(l > r) return;
		
		if(l == tl && r == tr){
			t[v] = val;
			marked[v] = true;
		} else{
			push(v);
			Long tm = (tl + tr) / 2;
			update(l, min(r , tm), val , 2 * v , tl, tm);
			update(max(l, tm + 1) , r , val , 2 * v + 1, tm + 1 , tr);
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



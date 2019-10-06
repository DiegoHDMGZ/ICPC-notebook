#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 100000;

Long combine(Long x , Long y) {
	return x + y;
}

struct SegmentTree{
	Long t[4 * MX];
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a, Long v , Long tl , Long tr) { //O(n)
		if (tl == tr){
			t[v] = a[tl];
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a, 2 * v, tl, tm);
			build(a, 2 * v + 1, tm + 1, tr);
			t[v] = combine(t[2 * v] , t[2 * v + 1]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long v , Long tl , Long tr ) { //O(logn)
		if (l > r) {
			return 0;
		}
		if (l == tl && r == tr) {
			return t[v];
		}
		Long tm = (tl + tr) / 2;
		return combine(query(l, min(r, tm), 2 * v, tl, tm) , query(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr));
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long valor, Long v, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[v] = valor;
		}
		else{
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, valor, 2 * v, tl, tm);
			}
			else {
				update(pos, valor, 2 * v + 1, tm + 1, tr);
			}
			t[v] = combine(t[2 * v] , t[2 * v + 1] );
		}
	}
	
	void update(Long pos, Long valor) {
		assert(maxN > 0);
		update(pos , valor, 1 , 0 , maxN - 1);
	}
} st;

int main(){
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

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
	
	void build(vector<Long> &a , Long v , Long tl , Long tr ) { //O(n)
		if (tl == tr){
			a[tl] == 0 ? t[v] = 1 : t[v] = 0;
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a, 2 * v, tl, tm);
			build(a, 2 * v + 1, tm + 1, tr);
			t[v] = t[2 * v] + t[2 * v + 1];
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long countZeros(Long l, Long r, Long v , Long tl, Long tr) { //O(logn)
		//# de ceros entre l y r
		if (l > r) {
			return 0;
		}
		if (l == tl && r == tr) {
			return t[v];
		}
		Long tm = (tl + tr) / 2;
		return countZeros(l, min(r, tm), 2 * v, tl, tm) + countZeros(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr);
	}
	
	Long countZeros(Long l , Long r) {
		assert(maxN > 0);
		return countZeros(l , r , 1 , 0 , maxN - 1);
	}

	Long find_kth(Long k, Long v , Long tl , Long tr ) { //(O(logn)
		//k-esimo cero
		if (k > t[v]) {
			return -1;
		}
		if (tl == tr) {
			return tl;
		}
		Long tm = (tl + tr) / 2;
		if (t[2 * v] >= k) {
			return find_kth(k, 2 * v, tl, tm);
		}
		else {
			return find_kth(k - t[2 * v], 2 * v + 1, tm + 1, tr);
		}
	}
	
	Long find_kth(Long k) {
		assert(maxN > 0);
		return find_kth(k , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long valor, Long v, Long tl, Long tr ) { //O(logn)
		if (tl == tr) {
			valor == 0 ? t[v] = 1 : t[v] = 0;
		}
		else {
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, valor, 2 * v, tl, tm);
			}
			else {
				update(pos, valor, 2 * v + 1, tm + 1, tr);
			}
			t[v] = t[2 * v] + t[2 * v + 1];
		}
	}
	
	void update(Long pos, Long valor) {
		update(pos , valor , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

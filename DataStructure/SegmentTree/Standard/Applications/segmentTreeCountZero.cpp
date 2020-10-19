#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree{
	Long t[2 * MX];
	Long maxN;
	
	void clear(Long n) {
		for (Long i = 0; i < 2 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id, Long tl, Long tr) { //O(n)
		if (tl == tr){
			a[tl] == 0 ? t[id] = 1 : t[id] = 0;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = t[left] + t[right];
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long countZeros(Long l, Long r, Long id, Long tl, Long tr) { //O(logn)
		//# of zeros in interval
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if (r < tm + 1) {
			//only left child
			return countZeros(l , r , left , tl , tm);
		} else if (tm < l) {
			//only right child
			return countZeros(l , r, right , tm + 1 , tr); 
		} else{
			//both children
			return countZeros(l, r, left, tl, tm) + countZeros(l, r, right, tm + 1, tr);
		}
	}
	
	Long countZeros(Long l , Long r) {
		assert(maxN > 0);
		return countZeros(l , r , 1 , 0 , maxN - 1);
	}

	Long find_kth(Long k, Long id, Long tl, Long tr) { //(O(logn)
		//k-th zero , 1-indexed
		if (k > t[id]) {
			return -1;
		}
		if (tl == tr) {
			return tl;
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if (t[left] >= k) {
			return find_kth(k, left, tl, tm);
		} else {
			return find_kth(k - t[left], right, tm + 1, tr);
		}
	}
	
	Long find_kth(Long k) {
		assert(k > 0);
		assert(maxN > 0);
		return find_kth(k , 1 , 0 , maxN - 1);
	}


	void update(Long pos, Long val, Long id, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			val == 0 ? t[id] = 1 : t[id] = 0;
		} else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val, right, tm + 1, tr);
			}
			t[id] = t[left] + t[right];
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

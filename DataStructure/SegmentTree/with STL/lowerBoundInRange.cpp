#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const int MX = 1e5;
const Long INF = 1e18;

Long combine(Long x, Long y){
	return min(x, y);
}

struct SegmentTree {
	vector<Long> t[2 * MX]; //O(nlogn)
	int n;
	
	void clear(int n) { 
		for (int i = 0; i < 2 * n; i++) {
			t[i].clear();
		}
		this->n = n;
	}

	void build(vector<Long> &a, int id, int tl, int tr) { //O(nlogn)
		if (tl == tr) {
			t[id] = {a[tl]};
		} else {
			int tm = (tl + tr) / 2;
			int left = id + 1;
			int right = id + 2 * (tm - tl + 1) ;
			build(a, left , tl, tm);
			build(a, right, tm + 1, tr);
			merge(t[left].begin(), t[left].end(), t[right].begin(), t[right].end(), back_inserter(t[id]));
		}
	}
	
	void build(vector<Long> &a) {
		n = a.size();
		build(a , 1 , 0 , n - 1);
	}

	Long query(int l, int r, Long x, int id, int tl, int tr) { //O(log^2 n)
		//find the smallest number greater or equal to x
		if (tr < l || tl > r) return INF;
		if (l <= tl && tr <= r) {
			auto it = lower_bound(t[id].begin(), t[id].end(), x);
			if (it != t[id].end()) return *it;
			else return INF;
		}
		int tm = (tl + tr) / 2;
		int left = id + 1;
		int right = id + 2 * (tm - tl + 1) ;
		return combine(query(l, r, x , left, tl, tm) , query(l, r, x , right, tm + 1, tr));
	}
	
	Long query(int l, int r, Long x) {
		assert(n > 0);
		return query(l , r , x , 1 , 0 , n - 1);
	}
} st;

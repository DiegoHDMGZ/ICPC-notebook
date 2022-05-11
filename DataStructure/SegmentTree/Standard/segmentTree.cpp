#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 1e5;

Long combine(Long x, Long y) {
	return x + y;
}

struct SegmentTree{
	Long t[2 * MX];
	int n;
	
	void clear(int n) {
		for (int i = 0; i < 2 * n; i++) {
			t[i] = 0;
		}
		this->n = n;
	}
	
	void build(vector<Long> &a, int id, int tl, int tr) { //O(n)
		if (tl == tr) {
			t[id] = a[tl];
		} else {
			int tm = (tl + tr) / 2;
			int left = id + 1;
			int right = id + 2 * (tm - tl + 1);
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void build(vector<Long> &a) {
		n = a.size();
		build(a, 1, 0, n - 1);
	}

	Long query(int l, int r, int id, int tl, int tr) { //O(logn)
		if (l <= tl && tr <= r) return t[id];
		int tm = (tl + tr) / 2;
		int left = id + 1;
		int right = id + 2 * (tm - tl + 1);
		if (r < tm + 1) return query(l, r, left, tl, tm);
		else if (tm < l) return query(l, r, right, tm + 1, tr); 
		else return combine(query(l, r, left, tl, tm), query(l, r, right, tm + 1, tr));
	}
	
	Long query(int l, int r) {
		assert(n > 0);
		return query(l, r, 1, 0, n - 1);
	}
	
	void update(int pos, Long val, int id, int tl , int tr) { //O(logn)
		if (tl == tr) {
			t[id] = val;
		} else {
			int tm = (tl + tr) / 2;
			int left = id + 1;
			int right = id + 2 * (tm - tl + 1);
			if (pos <= tm) update(pos, val, left, tl, tm);
			else update(pos, val, right, tm + 1, tr);
			t[id] = combine(t[left], t[right] );
		}
	}
	
	void update(int pos, Long val) {
		assert(n > 0);
		update(pos, val, 1, 0, n - 1);
	}
} st;

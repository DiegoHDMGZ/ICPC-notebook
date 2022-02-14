#include <bits/stdc++.h>

typedef long long Long;
// Binary Indexed Tree
// tree[i] = f[i - 2^r + 1] + ... + f[i]
//last significant bit = x & -x;

using namespace std;

const int MX = 1e5;
const int EXTRA = 6;
struct BIT{
	Long tree[MX + EXTRA];
	
	void clear(int n) { //O(n)
		for (int i = 0; i < n + EXTRA; i++) {
			tree[i] = 0;
		}
	}
	
	Long query(int x) { //O(log n)
		x += EXTRA;
		Long ans = 0;
		while (x > 0) {
			ans += tree[x];
			x -= (x & -x);
		}
		return ans;
	}
	
	void update(int x, Long val) { //O(log n)
		x += EXTRA;
		while (x < MX + EXTRA) {
			tree[x] += val;
			x += (x & -x);
		}
	}
	
	void update(int l, int r, Long add) {
		update(l, add);
		update(r + 1, -add);
	}		
} ft;

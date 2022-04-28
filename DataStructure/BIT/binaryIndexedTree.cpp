#include <bits/stdc++.h>

typedef long long Long;
// Binary Indexed Tree
// tree[i] = a[i - 2^r + 1] + ... + a[i]
// last significant bit = x & -x;

using namespace std;

struct BIT {
	vector<Long> tree;

	BIT(int n) {
		tree = vector<Long>(n + 1, 0);
	}
	
	Long query(int r) { //O(log n)
		//a[0] + a[1] + ... + a[r]
		r++;
		if (r <= 0) return 0;
		Long ans = 0;
		while (r > 0) {
			ans += tree[r];
			r -= (r & -r);
		}
		return ans;
	}
	
	void update(int l, Long val) { //O(log n)
		//a[i] += val, i >= l
		l++;
		while (l < tree.size()) {
			tree[l] += val;
			l += (l & -l);
		}
	}
	
	//you can only use one of this range implementations
	Long query(int l, int r) { //O(log n)
		return query(r) - query(l - 1);
	}
	
	void update(int l, int r, Long add) { //O(log n)
		update(l, add);
		update(r + 1, -add);
	}		
};

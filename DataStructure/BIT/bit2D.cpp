#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct BIT2D {
	vector<vector<Long>> tree;
	
	BIT2D(int n, int m) {
		tree = vector<vector<Long>>(n + 1, vector<Long>(m + 1));
	}

	Long query(int rx, int ry) { // O(log n log m)
		rx++;
		ry++;
		if (rx <= 0 || ry <= 0) return 0;
		Long ans = 0;
		while (rx > 0) {
			Long r = ry;
			while (r > 0) {
				ans += tree[rx][r];
				r -= (r & -r);
			}
			rx -= (rx & -rx);
		}
		return ans;
	}
	
	void update(Long lx, Long ly, Long val) { // O(log n log m)
		lx++;
		ly++;
		while (lx < tree.size()) {
			Long l = ly;
			while (l < tree[lx].size()) {
				tree[lx][l] += val;
				l += (l & -l);
			}
			lx += (lx & -lx);
		}
	}
	
	//you can only use one of this range implementations
	Long query(int x1, int y1, int x2, int y2) { // O(log n log m)
		return query(x2 , y2) - query(x2 , y1 - 1) - query(x1 - 1 , y2) + query(x1 - 1 , y1 - 1);
	}
	
	void update(int x1, int y1, int x2, int y2, Long add) { // O(log n log m)
		update(x1, y1, add);
		update(x2 + 1, y1, -add);
		update(x1, y2 + 1, -add);
		update(x2 + 1, y2 + 1, add);
	}	
};

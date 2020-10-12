#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long EXTRA = 5;

struct BIT{
	Long tree[MX + EXTRA];
	
	void clear(Long n) { //O(n)
		for (Long i = 0; i < n + EXTRA; i++) {
			tree[i] = 0;
		}
	}
	
	Long query(Long x) { //O(log n)
		x += EXTRA;
		Long sum = 0;
		while (x > 0) {
			sum += tree[x];
			x -= (x & -x);
		}
		return sum;
	}

	void update(Long x, Long add) { //O(log n)
		x += EXTRA;
		while (x < MX + EXTRA) {
			tree[x] += add;
			x += (x & -x);
		}
	}
};

struct RangeBIT{
	BIT ft1, ft2;
	
	void clear(Long n) {
		ft1.clear(n);
		ft2.clear(n);
	}
	
	Long query(Long x) {
		Long m = ft1.query(x);
		Long b = ft2.query(x);
		return m * x + b;
	}
	
	Long query(Long l, Long r) {
		return query(r) - query(l - 1);
	}
	
	void update(Long l, Long r, Long v) {
		ft1.update(l , v);
		ft1.update(r + 1 , -v);
		
		ft2.update(l , -v * (l - 1));
		ft2.update(r + 1 , v * r);
	}
}ft;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	return 0;
}

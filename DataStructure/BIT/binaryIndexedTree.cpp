#include <bits/stdc++.h>

typedef long long Long;
// Binary Indexed Tree
// tree[i] = f[i - 2^r + 1] + ... + f[i]
//last significant bit = x & -x;

using namespace std;

const Long MX = 1e5;
const Long EXTRA = 6;
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
	
	void update(Long l, Long r, Long add) {
		update(l, add);
		update(r + 1, -add);
	}		
} ft;

int main() {
	return 0;
}

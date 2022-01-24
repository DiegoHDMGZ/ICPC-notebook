#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e6;
const Long LG = 32 - __builtin_clz(MX);

struct SparseTable {
	Long st[MX][LG];
	
	Long f(Long a, Long b) {
		return min(a , b);
	}

	void build(vector<Long> &A) { // O(|f| n log n)
		int n = A.size();
		for (int i = 0; i < n; i++) {
			st[i][0] = A[i];
		}
		
		for (int k = 1; k < LG; k++) {
			for (int i = 0; i + (1 << k) <= n; i++) {
				st[i][k] = f(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
			}
		}
	}
	
	/*Long query(int l, int r) { //O(|f| log n)
		Long ans = st[l][0];
		if (l == r) return ans;
		l++;
		int range = r - l + 1;
		
		while ( range > 0) {
			int step = range & -range;
			int j = __builtin_ctz(step);
			ans = f(ans , st[l][j]);
			l += step;
			range -= step;
		}
		
		return ans;
	}*/
	
	Long query(int l, int r) { //O(|f|)
		//special cases : idempotent(min, max, gcd)
		int sz = r - l + 1;
		int lg = 31 - (__builtin_clz(sz));
		return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
	}
}st;

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
		Long n = A.size();
		for (Long i = 0; i < n; i++) {
			st[i][0] = A[i];
		}
		
		for (Long k = 1; k < LG; k++) {
			for (Long i = 0; i + (1 << k) <= n; i++) {
				st[i][k] = f(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
			}
		}
	}
	
	/*Long query(Long l, Long r) { //O(|f| log n)
		Long ans = st[l][0];
		if (l == r) return ans;
		l++;
		Long range = r - l + 1;
		
		while ( range > 0) {
			Long step = range & -range;
			Long j = __builtin_ctz(step);
			ans = f(ans , st[l][j]);
			l += step;
			range -= step;
		}
		
		return ans;
	}*/
	
	Long query(Long l, Long r) { //O(|f|)
		//special cases : idempotent(min, max, gcd)
		Long sz = r - l + 1;
		Long lg = 31 - (__builtin_clz(sz));
		return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
	}
}st;

int main() {
	return 0;
}

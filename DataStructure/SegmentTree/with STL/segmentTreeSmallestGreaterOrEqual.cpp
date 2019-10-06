#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e5;
const Long INF = 1e18;

struct SegmentTree {
	vector<Long> t[4 * MX]; //O(nlogn)
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear(Long n) { 
		for(Long i = 0; i < 4 * n; i++) {
			t[i].clear();
		}
		maxN = 0;
	}

	void build(vector<Long> &a, Long v , Long tl, Long tr ) { //O(nlogn)
		if (tl == tr) {
			t[v] = vector<Long>(1, a[tl]);
		}
		else {
			Long tm = (tl + tr) / 2;
			build(a, 2 * v , tl, tm);
			build(a, 2 * v + 1, tm + 1, tr);
			merge(t[2 * v].begin(), t[2 * v].end(), t[2 * v + 1].begin(), t[2 * v + 1].end(), back_inserter(t[v]));
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l , Long r, Long x, Long v, Long tl , Long tr) { //O(log²n)
		//find the smaLongest number greater or equal to X
		if (l > r) {
			return INF;
		}

		if (l == tl && r == tr) {
			vector<Long>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
			if (pos != t[v].end()) {
				return *pos;
			}
				
			return INF;
		}
		Long tm = (tl + tr) / 2;
		return min(query( l, min(r, tm), x , 2 * v, tl, tm), query( max(l, tm + 1), r, x , 2 * v + 1, tm + 1, tr));
	}
	
	Long query(Long l , Long r, Long x) {
		assert(maxN > 0);
		return query(l , r , x , 1 , 0 , maxN - 1);
	}

} st;

int main() {
	return 0;
}

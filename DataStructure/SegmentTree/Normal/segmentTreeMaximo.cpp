#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

pair<Long, Long> combine(pair<Long, Long> p1, pair<Long, Long> p2) {
	if (p1.first > p2.first) {
		return p1;
	}
	if (p1.first < p2.first) {
		return p2;
	}
	return make_pair(p1.first, p1.second + p2.second);
}

struct SegmentTree {
	pair<Long, Long> t[4 * MX]; // pair<maximo,apariciones>
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = {0 , 0};
		}
		maxN = 0;
	}
	

	void build(vector<Long> &a, Long v , Long tl , Long tr) { //O(n)
		if (tl == tr) {
			t[v] = make_pair(a[tl], 1);
		}
		else {
			Long tm = (tl + tr) / 2;
			build(a, 2 * v, tl, tm);
			build(a, 2 * v + 1, tm + 1, tr);
			t[v] = combine(t[2 * v], t[2 * v + 1]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}


	pair<Long, Long> getMax(Long l, Long r, Long v , Long tl , Long tr) { //O(logn)
		//pair<maximo,apariciones>
		if (l > r) {
			return make_pair(-INF, 0LL);
		}

		if (l == tl && r == tr) {
			return t[v];
		}

		Long tm = (tl + tr) / 2;

		return combine(getMax(l, min(r, tm), 2 * v, tl, tm), getMax(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr));
	}
	
	pair<Long, Long> getMax(Long l , Long r) {
		assert(maxN > 0);
		return getMax(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long valor, Long v, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[v] = make_pair(valor, 1);
		}
		else {
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, valor, 2 * v, tl, tm);
			}
			else {
				update(pos, valor, 2 * v + 1, tm + 1, tr);
			}
			t[v] = combine(t[2 * v], t[2 * v + 1]);
		}
	}
	
	void update(Long pos, Long valor) {
		assert(maxN > 0);
		update(pos , valor , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

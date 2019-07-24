#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long INF = 1e18;
const Long MAX = 1e5;
Long a[MAX];

struct SegmentTree {
	multiset<Long> t[4 * MAX]; //O(nlogn)
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear() {
		for(Long i = 0; i < 4 * MAX; i++) {
			t[i].clear();
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a , Long v , Long tl , Long tr) { //O(nlog²n)
		if (tl == tr){
			t[v].insert(a[tl]);
		}
		else{
			Long tm = (tl + tr) / 2;
			build(a , 2 * v, tl, tm);
			build(a , 2 * v + 1, tm + 1, tr);
			t[v] = t[2 * v];
			t[v].insert(t[2 * v + 1].begin(), t[2 * v + 1].end());
			//merge(t[2*v].begin(),t[2*v].end(),t[2*v+1].begin(),t[2*v+1].end(),back_inserter(t[v]));
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long x , Long v , Long tl , Long tr) { //O(log²n)
		//find the smaLongest number greater or equal to X
		if (l > r) {
			return INF;
		}

		if (l == tl && r == tr) {
			multiset<Long>::iterator pos = t[v].lower_bound(x);
			if (pos != t[v].end()) {
				return *pos;
			}
			return INF;
		}

		Long tm = (tl + tr) / 2;

		return min(query( l, min(r, tm), x , 2 * v , tl, tm), query(max(l, tm + 1), r, x , 2 * v + 1, tm + 1, tr));
	}
	
	Long query(Long l , Long r , Long x) {
		assert(maxN > 0);
		return query(l , r , x , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long valor, Long v , Long tl, Long tr ) { //O(log²n)
		t[v].erase(t[v].find(a[pos]));
		t[v].insert(valor);

		if (tl != tr) {
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, valor, 2 * v, tl, tm);
			}
			else {
				update(pos, valor, 2 * v + 1, tm + 1, tr);
			}
		}
		else {
			a[pos] = valor;
		}
	}
	
	void update(Long pos , Long valor) {
		assert(maxN > 0);
		update(pos , valor , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

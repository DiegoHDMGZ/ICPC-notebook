#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;
struct Data {
	Long sum, pref, suf, ans;
};

Data combine(Data l, Data r) {
	Data d;
	d.sum = l.sum + r.sum;
	d.pref = max(l.pref, l.sum + r.pref);
	d.suf = max(r.suf, r.sum + l.suf);
	d.ans = max(max(l.ans, r.ans), l.suf + r.pref);
	return d;
}

Data make_data(Long val) {
	Data r;
	r.sum = val;
	r.pref = r.suf = r.ans = val; //max(0LL,val); para considerar el arreglo vacio
	return r;
}

struct SegmentTree {
	Data t[4 * MAX];
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}
	
	void clear() {
		for(Long i = 0; i < 4 * MAX; i++) {
			t[i] = make_data(0);
		}
		maxN = 0;
	}
	
	void build(vector<Long> &a, Long v , Long tl , Long tr) { //O(n)
		if (tl == tr) {
			t[v] = make_data(a[tl]);
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

	Data query(Long l, Long r, Long v, Long tl , Long tr ) { //O(logn)
		//maxSubsemengtSum in [l,r]
		//if(l > r)	return make_data(0LL); para considerar arreglo vacio
		if (l == tl && r == tr) {
			return t[v];
		}
			
		Long tm = (tl + tr) / 2;

		if (r <= tm) {
			return query(l, min(r, tm), 2 * v, tl, tm);
		}
		else if (l > tm) {
			return query(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr);
		}
		return combine(query(l, min(r, tm), 2 * v, tl, tm), query(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr));
	}
	
	Data query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r, 0 , 1 , maxN - 1);
	}

	void update(Long pos, Long valor, Long v, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			t[v] = make_data(valor);
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
	
	void update(Long pos ,Long valor) {
		assert(maxN > 0);
		update(pos , valor , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

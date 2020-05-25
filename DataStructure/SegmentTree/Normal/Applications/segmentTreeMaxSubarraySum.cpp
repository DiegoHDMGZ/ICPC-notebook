#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
struct Data {
	Long sum, pref, suf, ans;
	Data(){}
	Data(Long val){
		sum = val;
		pref = suf = ans = val; //max(0LL,val); to consider the empty array
	}
};

Data combine(Data l, Data r) {
	Data d;
	d.sum = l.sum + r.sum;
	d.pref = max(l.pref, l.sum + r.pref);
	d.suf = max(r.suf, r.sum + l.suf);
	d.ans = max(max(l.ans, r.ans), l.suf + r.pref);
	return d;
}

struct SegmentTree {
	Data t[2 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i] = Data(0);
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl , Long tr) { //O(n)
		if (tl == tr) {
			t[id] = Data(a[tl]);
		}else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Data query(Long l, Long r, Long id, Long tl , Long tr ) { //O(logn)
		//maxSubsemengtSum in [l,r]
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if(r < tm + 1){
			//only left child
			return query(l , r , left , tl , tm);
		} else if(tm < l){
			//only right child
			return query(l , r, right , tm + 1 , tr); 
		} else {
			//both children
			return combine(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Data query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r, 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long val, Long id, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			t[id] = Data(val);
		}
		else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val, right, tm + 1, tr);
			}
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void update(Long pos ,Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

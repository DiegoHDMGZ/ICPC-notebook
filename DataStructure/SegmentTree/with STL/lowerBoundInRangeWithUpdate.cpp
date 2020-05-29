#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long INF = 1e18;
const Long MX = 1e5;

Long combine(Long x, Long y){
	return min(x , y);
}

struct SegmentTree {
	multiset<Long> t[2 * MX]; //O(nlogn)
	Long curVal[MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i].clear();
			curVal[i] = INF;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a , Long id , Long tl , Long tr) { //O(nlog²n)
		if (tl == tr){
			t[id] = {a[tl]};
			curVal[tl] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a , left, tl, tm);
			build(a , right, tm + 1, tr);
			t[id] = t[left];
			t[id].insert(t[right].begin(), t[right].end());
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		assert(maxN > 0);
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long x , Long id , Long tl , Long tr) { //O(log²n)
		//find the smallest number greater or equal to X
		if(tr < l || tl > r){
			return INF;
		}

		if (l <= tl && tr <= r) {
			auto it = t[id].lower_bound(x);
			if (it != t[id].end()) {
				return *it;
			} else{
				return INF;
			}
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;

		return combine(query(l, r, x , left, tl, tm) , query(l, r, x , right, tm + 1, tr));
	}
	
	Long query(Long l , Long r , Long x) {
		assert(maxN > 0);
		return query(l , r , x , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long val , Long id , Long tl, Long tr ) { //O(log²n)
		if (tl != tr) {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val , right, tm + 1, tr);
			}
		} 
		t[id].erase(t[id].find(curVal[pos]));
		t[id].insert(val);
	}
	
	void update(Long pos , Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
		curVal[pos] = val;
	}
} st;

int main() {
	return 0;
}

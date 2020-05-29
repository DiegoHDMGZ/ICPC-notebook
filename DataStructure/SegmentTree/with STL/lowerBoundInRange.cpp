#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e5;
const Long INF = 1e18;

Long combine(Long x, Long y){
	return min(x, y);
}

struct SegmentTree {
	vector<Long> t[2 * MX]; //O(nlogn)
	Long maxN;
	
	void clear(Long n) { 
		for(Long i = 0; i < 2 * n; i++) {
			t[i].clear();
		}
		maxN = n;
	}

	void build(vector<Long> &a, Long id , Long tl, Long tr ) { //O(nlogn)
		if (tl == tr) {
			t[id] = {a[tl]};
		}else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left , tl, tm);
			build(a, right, tm + 1, tr);
			merge(t[left].begin(), t[left].end(), t[right].begin(), t[right].end(), back_inserter(t[id]));
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l , Long r, Long x, Long id, Long tl , Long tr) { //O(log²n)
		//find the smallest number greater or equal to x
		if(tr < l || tl > r){
			return INF;
		}

		if (l <= tl && tr <= r) {
			auto it = lower_bound(t[id].begin(), t[id].end(), x);
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
	
	Long query(Long l , Long r, Long x) {
		assert(maxN > 0);
		return query(l , r , x , 1 , 0 , maxN - 1);
	}

} st;

int main() {
	return 0;
}

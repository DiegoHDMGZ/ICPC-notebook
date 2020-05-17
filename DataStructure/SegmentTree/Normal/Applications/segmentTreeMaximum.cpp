#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Data{
	Long maxi, cnt;
	Data(){}
	Data(Long maxi, Long cnt = 1) : maxi(maxi), cnt(cnt){}
};

Data combine(Data p1, Data p2) {
	if (p1.maxi > p2.maxi) {
		return p1;
	}
	if (p1.maxi < p2.maxi) {
		return p2;
	}
	return Data(p1.maxi, p1.cnt + p2.cnt);
}

struct SegmentTree {
	Data t[4 * MX]; 
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = Data(0, 0);
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id, Long tl , Long tr) { //O(n)
		if (tl == tr) {
			t[id] = Data(a[tl]);
		}else {
			Long tm = (tl + tr) / 2;
			build(a, 2 * id, tl, tm);
			build(a, 2 * id + 1, tm + 1, tr);
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}


	Data query(Long l, Long r, Long id , Long tl , Long tr) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		if(tm < l){
			//only right child
			return query(l , r, 2 * id + 1 , tm + 1 , tr); 
		} else if(r < tm + 1){
			//only left child
			return query(l , r , 2 * id , tl , tm);
		} else{
			//both children
			return combine(query(l, r, 2 * id, tl, tm) , query(l, r, 2 * id + 1, tm + 1, tr));
		}
	}
	
	Data query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long val, Long id, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[id] = Data(val);
		}
		else {
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, val, 2 * id, tl, tm);
			}else {
				update(pos, val, 2 * id + 1, tm + 1, tr);
			}
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;

int main() {
	return 0;
}

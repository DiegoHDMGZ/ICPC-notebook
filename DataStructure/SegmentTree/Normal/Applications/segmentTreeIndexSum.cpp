#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree{
	Long t[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl , Long tr ){ //O(n)
		if(tl == tr){
			t[id] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			build(a , 2 * id , tl , tm);
			build(a , 2 * id + 1 , tm + 1 , tr);
			t[id] = t[2 * id] + t[2 * id + 1];
		}
	}
	
	void build(vector<Long> &a) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long findInd(Long sum, Long id , Long tl , Long tr  ){ //O(logn)
		//min index where the prefix sum is >= target
		//it only works if the array is of non-negative numbers
		if(sum > t[id]){
			return -1;
		}
		if(tl == tr){
			return tl;
		}
		Long tm= (tl + tr) / 2;
		if(t[2 * id] >= sum){
			return findInd(sum , 2 * id , tl , tm);
		}else{
			return findInd(sum - t[2 * id] , 2 * id + 1, tm + 1 ,tr);
		}
	}
	
	Long findInd(Long sum) {
		assert(maxN > 0);
		return findInd(sum , 1 , 0 , maxN - 1);
	}
	
	void update(Long pos, Long val, Long id , Long tl , Long tr ){ //O(logn)
		if(tl == tr){
			t[id] = val;
		}else{
			Long tm = (tl + tr) / 2;
			if(pos <= tm){
				update(pos, val ,2 * id, tl, tm);
			}else{
				update(pos, val, 2 * id + 1 , tm + 1, tr);
			}
			t[id] = t[2 * id] + t[2 * id + 1];
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

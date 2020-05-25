#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree{
	Long t[2 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl , Long tr ){ //O(n)
		if(tl == tr){
			t[id] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a , left , tl , tm);
			build(a , right , tm + 1 , tr);
			t[id] = t[left] + t[right];
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
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if(t[left] >= sum){
			return findInd(sum , left , tl , tm);
		}else{
			return findInd(sum - t[left] , right, tm + 1 ,tr);
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
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if(pos <= tm){
				update(pos, val , left , tl, tm);
			}else{
				update(pos, val, right , tm + 1, tr);
			}
			t[id] = t[left] + t[right];
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

#include <bits/stdc++.h>
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Credits : https://www.geeksforgeeks.org/mos-algorithm-query-square-root-decomposition-set-1-introduction/
//For a good explanation check : https://www.hackerearth.com/practice/notes/mos-algorithm/
//And check : https://cp-algorithms.com/data_structures/sqrt_decomposition.html

const Long MX = 1e5;
const Long block = 400;
//Conditions
//1) No update
//2) Offline
//3) Knowing f([l,r]) , we can compute in O(|f|):
//  f([l + 1 , r]) ,f([l - 1 , r]) , f([l, r + 1]) , f([l , r - 1]) 
//=> Overall complexity O((N + Q) sqrt(N) |f|)

struct Query{
    Long id, l, r;
    Query(){}
    Query(Long id, Long l, Long r): id(id), l(l) , r(r){}
};

bool cmp(const Query &x, const Query &y) {
	//queries are sorted in increasing order of the block of l
	Long bx = x.l / block ;
	Long by = y.l / block;
	if (bx != by) return bx < by;
	
	//If queries are in the same blocks
	//if the block is odd, sort in ascending order of r
	//otherwise, in descending order of r
	if (bx & 1 == 1) {
		return x.r < y.r;
	} else{
		return x.r > y.r;
	}
}

struct Mo{
	void add(Long val, Long &ans) { //O(|f|)
		ans += val;
	}
	
	void remove(Long val, Long &ans) { //O(|f|)
		ans -= val;
	}
	
	vector<Long> process(vector<Long> &A, vector<Query> &queries) { //O((N + Q) sqrt(N) |f|)
	    sort(queries.begin() , queries.end(), cmp);
	    Long curL = 0, curR = 0;
	    Long acum = 0;
		vector<Long> answer(queries.size());
	    for (int i = 0; i < queries.size(); i++) {
	        Long l = queries[i].l;
	        Long r = queries[i].r;
			while (curR <= r) {//f(l , r + 1)
				add(A[curR], acum);
				curR++;
			}
			while (curL > l) { //f(l - 1 , r)
				curL--;
				add(A[curL] , acum);
			}
			while (curL < l) { // f(l + 1 , r)
				remove(A[curL] , acum);
				curL++;
			}
			while (curR > r + 1) { //f(l , r - 1)
				curR--;
				remove(A[curR] , acum);
			}
			answer[queries[i].id] = acum;
	    }
	    return answer;
	}
}mo;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long n;
	cin >> n;
	vector<Long> A(n);
	for (int i = 0; i < n; i++){
		cin >> A[i];
	}
	Long Q;
	cin >> Q;
	vector<Query> queries;
	for (int q = 0; q < Q; q++){
		Long l, r;
		cin >> l >> r;
		queries.push_back(Query(q, l , r));
	}
    vector<Long> ans = mo.process(A, queries);
    for (int q = 0; q < Q; q++){
    	cout << ans[q] << endl;
	}
    return 0;
}

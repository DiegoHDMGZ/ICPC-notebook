#include <bits/stdc++.h>
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Hilber Curves: https://codeforces.com/blog/entry/61203

//Conditions
//1) No update
//2) Offline
//3) Knowing f([l,r]) , we can compute in O(|f|):
//  f([l + 1 , r]) ,f([l - 1 , r]) , f([l, r + 1]) , f([l , r - 1]) 
//=> Overall complexity O(N sqrt(Q))

Long hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow - 1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	Long subSquareSize = 1LL << (2 * pow - 2);
	Long ans = seg * subSquareSize;
	Long add = hilbertOrder(nx, ny, pow - 1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct Query{
	Long id, l, r, order;
	Query(){}
	Query(Long id, Long l, Long r){
		this->id = id;
		this->l = l;
		this->r = r;
		int k = 21; //k holds 2^k >= N
		this->order = hilbertOrder(l, r, k, 0);
	}

	bool operator <(const Query &other) const {
		return order < other.order;
	}
};

struct Mo{
	void add(Long val, Long &ans) { //O(|f|)
		ans += val;
	}
	
	void remove(Long val, Long &ans) { //O(|f|)
		ans -= val;
	}
	
	vector<Long> process(vector<Long> &A, vector<Query> &queries) { //O((N + Q) sqrt(N) |f|)
		sort(queries.begin() , queries.end());
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

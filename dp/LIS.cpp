#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://blog.asarkar.org/assets/docs/algorithms-curated/Longest%20Increasing%20Subsequence%20-%20Jan.pdf

const Long INF = 1e18;

deque<Long> LIS(vector<Long> &A) {
	Long n = A.size();
	vector<Long> L(n);
	vector<Long> B(n + 1, INF);
	B[0] = -INF;
	
	Long best = 0;
	for(Long i = 0; i < n; i++){
		Long pos = upper_bound(B.begin(), B.end(), A[i]) - B.begin(); 
		//change to lower for strictly increasing 
		L[i] = pos;
		best = max(best , L[i]);
		B[pos] = A[i];
	}
	
	deque<Long> ans = {INF};
	for(Long i = n - 1; i >= 0; i--){
		if(L[i] == best && A[i] < ans.front()){
			ans.push_front(A[i]);
			best--;
		}
	}
	ans.pop_front();
	return ans;
}

int main() {
	return 0;
}

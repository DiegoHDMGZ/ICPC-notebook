#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long INF = 1e18;

Long LIS(vector<Long> &A){
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
	
	return best;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	

	vector<Long> A;
	Long x;
	while(cin >> x){
		A.pb(x);
	}

	cout << A.size() - LIS(A) << endl;

	return 0;
}

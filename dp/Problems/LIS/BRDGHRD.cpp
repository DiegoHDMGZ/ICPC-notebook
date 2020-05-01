#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://blog.asarkar.org/assets/docs/algorithms-curated/Longest%20Increasing%20Subsequence%20-%20Jan.pdf

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

void solve(){
	Long n;
	cin >> n;
	vector<pair<Long,Long>> A(n);
	
	for(Long i = 0 ; i < n ; i++){
		cin >> A[i].first;
	}
	for(Long i = 0; i < n ; i++){
		cin >> A[i].second;
	}
	sort(A.begin(), A.end());
	vector<Long> B;
	for(Long i = 0; i < n; i++){
		B.push_back(A[i].second);
	}
	cout << LIS(B) << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t, T )solve();


	return 0;
}

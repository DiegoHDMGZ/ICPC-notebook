#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

typedef vector<Long> polynomial;

polynomial operator *(const polynomial &a, const polynomial &b) {
	Long n = a.size();
	Long m = b.size();
	polynomial ans(n + m - 1 , 0);
	
	REP(i , n){
		REP(j , m){
			ans[i + j] += a[i] * b[j];
		}
	}

	return ans;
} 


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	return 0;
}

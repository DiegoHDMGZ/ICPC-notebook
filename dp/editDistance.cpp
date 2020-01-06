#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e3;

Long dp[MX][MX];
bool used[MX][MX];
string a , b;

Long editDistance(Long n = (Long)a.size()  , Long m = (Long)b.size() ){
	if(n == 0) return m;
	if(m == 0) return n;
	
	if(used[n][m]) return dp[n][m];
	used[n][m] = true;
	
	if(a[n - 1] == b[m - 1]){
		return dp[n][m] = editDistance(n - 1 , m - 1);
	} else {
		return dp[n][m] = 1 + min({editDistance(n - 1 , m - 1) , editDistance(n , m -1) , editDistance(n - 1 , m) });
	}
}

void clear(){
	Long n = a.size();
	Long m = b.size();
	REP(i , n + 1){
		REP(j , m + 1){
			used[i][j] = false;
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	a = "aabba";
	while(cin  >> b){
		cout << editDistance() << endl;
		clear();
	}
	
	
	return 0;
}

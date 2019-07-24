#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long DIGIT = 10;
const Long MAX = 90;
string s;
Long memo[DIGIT][2][MAX];
bool used[DIGIT][2][MAX];
Long f( Long pos, Long lower, Long sum) { //suma de todos los digitos del 1 al n
	if(pos == s.size() ) {
		return sum;
	}
	
	Long &ans = memo[pos][lower][sum];
	if(used[pos][lower][sum] ) {
		return ans;
	}
	
	used[pos][lower][sum] = true;
	ans = 0;
	Long d = s[pos] - '0';
	
	if(lower == 1) { //numero menor que s
		for(Long i = 0; i <= 9; i++) {
			ans += f( pos + 1 , lower , sum + i);
		}
	}
	else{
		for(Long i = 0; i < d; i++) {
			ans += f( pos + 1 , 1 , sum + i);
		}
		ans += f(pos + 1 , 0 , sum + d);
	}
	
	return ans;
}

int main() {

	return 0;
}




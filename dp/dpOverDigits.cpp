#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long DIGIT = 10;
const Long MXSUM = 9 * DIGIT;
string s;
Long dp[DIGIT][2][MXSUM];
bool used[DIGIT][2][MXSUM];
Long sumDigits(Long pos, bool lower, Long sum) { //sum of all digits from 1 to s
	if (pos == s.size()) {
		return sum;
	}
	Long &ans = dp[pos][lower][sum];
	if (used[pos][lower][sum]) {
		return ans;
	}
	used[pos][lower][sum] = true;
	ans = 0;
	Long d = s[pos] - '0';
	if (lower) {
		d = 10;
	}
	for (Long i = 0; i < d; i++) {
		ans += sumDigits(pos + 1 , 1 , sum + i);
	}
	if (!lower) {
		ans += sumDigits(pos + 1 , 0, sum + d);
	}
	return ans;
}

int main() {
	return 0;
}




#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

int getBit(int mask, int pos) {
	return (mask >> pos) & 1;
}

int changeBit(int mask, int pos) {
	return mask ^ (1 << pos);
}

//if subset == false, would be sum over supersets
vector<Long> sumOverSubsets(vector<Long> &A, bool subset = true) { //O(n * 2^n)
	//A have size 2^n
	int n = __builtin_ctz(A.size());
	vector<Long> ans = A;
	if (!subset) reverse(ans.begin(), ans.end());
	for (int i = 0; i < n; i++) {
		for (int mask = 0; mask < (1 << n); mask++) {
			if (getBit(mask, i)) {
				ans[mask] += ans[changeBit(mask, i)];
			}
		}
	}
	if (!subset) reverse(ans.begin(), ans.end());
	return ans;
}

int main() {
	return 0;
}

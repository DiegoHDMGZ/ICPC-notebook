#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 1000;

Long stirling[MX][MX];

void calculate() {
	stirling[0][0] = 1;
	for (Long n = 1; n < MX; n++) {
		stirling[n][0] = 0;
	}
	for (Long n = 1; n < MX; n++) {
		for (Long k = 1; k <= n; k++) {
			stirling[n][k] = stirling[n - 1][k - 1] + k * stirling[n - 1][k];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	calculate();
	Long n , k;
	cin >> n >> k;
	cout << stirling[n][k] << endl;
	
	return 0;
}

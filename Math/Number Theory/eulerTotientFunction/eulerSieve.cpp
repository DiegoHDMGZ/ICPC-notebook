#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const int MX = 1e6;
Long phi[MX];

void calculate() { //O(n log log n)
	phi[0] = 0;
	phi[1] = 1;
	for (int i = 2; i < MX; i++) {
		phi[i] = i;
	}
	for (int i = 2; i < MX; i++) {
		if (phi[i] == i) {
			for (int j = i; j < MX; j += i) {
				phi[j] -= phi[j] / i;
			}
		}
	}
}

int main() {
	return 0;
}

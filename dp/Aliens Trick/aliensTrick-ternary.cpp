#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long getBest(Long lambda); //returns P(lambda)

const Long INF = 1e18;
Long minimize() { //ternary search
	Long low = -INF;
	Long high = INF;
	while (high - low > 2) {
		Long m1 = low + (high - low) / 3;
		Long m2 = high - (high - low) / 3;
		if (getBest(m1) < getBest(m2)) low = m1;
		else high = m2;
	}
	Long maxi = getBest(low); 
	for (Long i = low + 1; i <= high; i++) {
		maxi = max(maxi, getBest(i));
	}
	return maxi;
}

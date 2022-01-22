#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long double Double;

const Double EPS = 1e-6;

Double f(Double x){
	return x * x;
}

bool check(Double mid, Double x) {
	return f(mid) >= x;
}

Double search(Double low, Double high, Double x) {
	//F F ... T T
	while (high - low > EPS) { //REP(i, 1000) {
		Double mid = (high + low) / 2.0;
		if (check(mid , x)) high = mid;
		else low = mid;
	}
	return high;
}

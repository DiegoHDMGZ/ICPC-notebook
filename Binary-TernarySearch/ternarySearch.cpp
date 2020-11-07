#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;
typedef long double Double;
const Double EPS = 1e-6;

Double f(Double x) {
	return -3 * x * x - 5 * x + 7;
}

Double ternarySearch(Double low, Double high) { //O(log n)
	while (high - low > EPS) { //for(Long i = 0; i < 200 ; i++)
		Double m1 = low + (high - low) / 3.0;
		Double m2 = high - (high - low) / 3.0;
		if (f(m1) < f(m2)) { //if minimum is needed, change to >
			low = m1;
		} else{
			high = m2;
		}
	}
	return f((low + high) / 2.0);
}

int main(){
	cout << fixed << setprecision(6) << ternarySearch(-200000,200000) << endl;
	return 0;
}

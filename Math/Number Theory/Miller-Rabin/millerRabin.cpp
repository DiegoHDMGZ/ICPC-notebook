#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

Long add(Long a, Long b, Long mod) {
	return (a + b ) % mod;
}

Long mult(Long a, Long b, Long mod) {
	//Use fastMult or 128-bit integer
	Long ans = 0;
	while (b > 0) {
		if (b & 1 == 1) { //b % 2 == 1
			ans = add(ans ,a , mod);
		}
		a = add(a , a , mod);
		b >>= 1; //b /= 2
	}
	return ans;
}

Long fastPow(Long a, Long b , Long mod) { //O(log b)
	Long ans = 1;
	while (b > 0) {
		if (b & 1 == 1) { //b % 2 == 1
			ans = mult(ans ,a , mod);
		}
		a = mult(a , a  , mod);
		b >>= 1; //b /= 2;
	}
	return ans;
}

bool checkComposite(Long a, Long d, Long s, Long n) {
	//O(log n) with 128 bit
	//O(log^2 n) with divide and conquer mult
	Long x = fastPow(a , d, n);
	if (x == 1 || x == n - 1) {
		return false;
	}
	for (int i = 1; i < s; i++) {
		x = mult(x, x, n);
		if (x == n - 1) {
			return false;
		}
	}
	return true;
}

bool isPrime(Long n) { 
	//O(log n * |base|) with 128-bit
	//O(log^2 n * |base|) with divide and conquer
	if (n <= 1) {
		return false;
	}
	Long d = n - 1;
	Long s = 0;
	while ((d & 1) == 0) {
		d >>= 1;
		s++;
	}
	//64-bit integer
	vector<Long> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	//2 3 5 7 for 32-bit integer
	for (Long a : base) {
		if (a >= n) break;
		if (checkComposite(a, d, s, n)) {
			return false;
		}
	}
	return true;
}

int main() {
	return 0;
}

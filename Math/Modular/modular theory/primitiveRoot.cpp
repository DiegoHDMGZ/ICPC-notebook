#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://napocaro.files.wordpress.com/2015/02/david_m-_burton_elementary_number_theory_sixth_bookfi-org.pdf

//g is a primitive root modulo n if and only if for any integer "a" such that gcd(a,n)=1, there exists an integer k such that:
// (g ^ k) ≡ a (mod n).

//Definition : Let n > 1 and gcd(a , n) = 1. The order of "a" modulo "n" is the smallest positive integer
//k such that (a ^ k) = 1 (mod n). 

//If g is primitive root modulo n, then gcd(g, n) = 1 and "g" is of order phi(n)
//Hence, to know if a number is a primitive root modulo n, we must check that there is no such a "p" (p < phi(n) ) that a ^ p = 1 (mod n)
//Additionally, if this "p" exists, it has to be a divisor of phi(n)
//Hence , we just have to check all the divisors of the form  phi(n) / pi  [pi prime factor of phi(n)] 
//because other divisor d satisfy : d |  phi(n) / pi

Long mult(Long a, Long b, Long mod) {
	a %= mod;
	b %= mod;
	return (a * b) % mod;
}

Long fastPow(Long a, Long b, Long mod) { //O(log b)
	Long ans = 1;
	while (b > 0) {
		if (b & 1) ans = mult(ans, a, mod);
		a = mult(a, a, mod);
		b >>= 1;
	}
	return ans;
}

Long primitiveRoot(Long mod) { //O( mod log mod log phi(mod) + sqrt(mod))  
	Long phi = mod - 1; // phi = euler(mod) for not prime mods
	//if( mod < 1e7 ) we can use extended Sieve to factorize
	Long n = phi;
	Long i = 2;
	vector<Long> v;
	while (i * i <= n) {
		if (n % i == 0) {
			v.push_back(phi / i);
			while (n % i == 0) n /= i;
		}
		i++;
	}
	if(n > 1) v.push_back(phi / n);
	for(Long ans = 2; ans <= mod; ans++) {
		bool ok = true;
		REP(i, v.size()) {
			if (fastPow(ans, v[i], mod) == 1) {
				ok = false;
				break;
			}
		}
		if (ok) {
			return ans;
		}
	}
	return -1;
}

int main() {
	return 0;
}

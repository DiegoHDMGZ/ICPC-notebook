#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://napocaro.files.wordpress.com/2015/02/david_m-_burton_elementary_number_theory_sixth_bookfi-org.pdf
//If g is primitive root modulo n, then gcd(a, n) = 1 and "a" is of order phi(n)
//Hence, to know if a number is a primitive root modulo n, we must check that there is no such a "p" (p < phi(n) ) that a ^ p = 1 (mod n)
//Additionally, if this "p" exists, it have to be a divisor of phi(n)
//We just have to check all of divisors of form  phi(n) / pi  [pi prime factor of phi(n)] because other divisor d satisfy : d |  phi(n) / pi

/*const Long MAX = 1e7;
bool isPrime[MAX];
Long fact[MAX];
vector<Long> primes;

void extSieve(){ //O(MAX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MAX , true);
	isPrime[1] = false;
	for(Long i = 2; i  < MAX; i++){
		if(isPrime[i]) {
			primes.pb(i);
			fact[i] = i;
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MAX; j++){
			isPrime[i * primes[j]] = false;
			fact[i * primes[j]] = primes[j];
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

Long euler(Long n) { //O(log n)
	Long ans = n;
	while(n > 1){
		Long f = fact[n];
		while(n % f == 0){
			n /= f;
		}
		ans -= ans / f;
	}
	return ans;
}*/

Long fastPow(Long a, Long b , Long c){ //O(logb)
	if(b == 0) return 1LL;
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	if(b%2==0) return temp;
	
	return (a*temp)%c;
}


Long primitiveRoot(Long mod) { //O( mod log n log phi(n) )  
	Long phi = mod - 1; // phi = euler(mod) for not prime mods
	//if( mod < 1e7 ) we can use extended Sieve to factorize
	
	Long n = phi;
	
	Long i = 2;
	vector<Long> v;
	while(i * i <= n ) {
		if(n % i == 0) {
			v.pb(phi / i);
			while(n % i == 0) {
				n /= i;
			}
		}
		
		i++;
	}
	
	if(n > 1) {
		v.pb(phi / n);
	}
	
	for(Long ans = 2; ans <= mod; ans++) {
		bool ok = true;
		REP(i , v.size()) {
			if(fastPow(ans , v[i] , mod) == 1) {
				ok = false;
				break;
			}
		}
		if(ok) {
			return ans;
		}
	}
	return -1;
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	debug(primitiveRoot(9  ));
	return 0;
}


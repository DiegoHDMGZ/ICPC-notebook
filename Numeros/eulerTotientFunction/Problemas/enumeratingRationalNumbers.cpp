#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e7;
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
}

const Long limit = 12160000000;

vector<Long> acum;

bool check( Long med , Long x){
	return x <= acum[med];
}


Long search(  Long ini , Long fin , Long x){ //O(logn)
	// F F F... V V V
	if(check(ini , x)) {
		return ini;
	}
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= (ini + fin) / 2;
		
		if(check( med, x )){
			fin=med;
		} 
		else {
			ini = med;
		}
	}

	//hay 2 valores ini es F y fin es V
	return fin;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	extSieve();
	
	acum.pb(2);
	
	while(acum[(Long)acum.size() - 1] < limit) {
		Long ant = acum[(Long)acum.size() - 1];
		acum.pb(ant + euler((Long)acum.size() + 1));
	}

	
	Long n;
	while(cin >> n ) {
		if(n == 0) {
			break;
		}
		if(n == 1) {
			cout << "0/1" << endl;
			continue;
		}
		if(n == 2) {
			cout << "1/1" << endl;
			continue;
		}
		Long d = search(0 , (Long) acum.size() - 1 , n) + 1;
		Long aux = n - acum[d - 2];
		Long cnt = 0;

		for(Long i = 1; i <= d; i++) {
			if(__gcd(i , d) == 1) {
				cnt++;
				if(cnt == aux) {
					cout << i << "/" << d << endl;
					break;
				}
			}
		}
		
	}
	return 0;
}


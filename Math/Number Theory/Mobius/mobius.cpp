#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5;

bool isPrime[MX];
Long fact[MX];
vector<Long> primes;

void extSieve(){ //O(MX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MX , true);
	isPrime[1] = false;
	for(Long i = 2; i  < MX; i++){
		if(isPrime[i]) {
			primes.pb(i);
			fact[i] = i;
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MX; j++){
			isPrime[i * primes[j]] = false;
			fact[i * primes[j]] = primes[j];
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

Long mu[MX];
void mobius() {
    mu[1] = 1;
    for(Long i = 2 ;i < MX; i ++) {
        if(fact[i] == i) {
            mu[i] = -1;
        } else {
            Long nx = i / fact[i];
            if(nx % fact[i] == 0) {
                mu[i] = 0;
            } else {
                mu[i] = -mu[nx];
            }
        }
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

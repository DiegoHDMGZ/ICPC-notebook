#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MAX = 2e6;
bool isPrime[MAX];
vector<Long> primes;

void sieve(){ //O(MAX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MAX , true);
	isPrime[0] = false;
	isPrime[1] = false;
	for(Long i = 2; i  < MAX; i++){
		if(isPrime[i]) {
			primes.pb(i);
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MAX; j++){
			isPrime[i * primes[j]] = false;
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

bool isPrimeR[MAX];

void segmentedSieve(Long l, Long r) { //O( (r - l) * log log (r - l) )

    fill(isPrimeR, isPrimeR + MAX , true);

    for(Long i = 0; i < primes.size(); i++) {
        if(primes[i] * primes[i] > r) {
            break;
        }
        Long k = max(l / primes[i] , 2LL);
        k = max(k , primes[i] );
        for(Long j = k; ; j++) {
            if(primes[i] * j < l) {
                continue;
            }
            if(primes[i] * j > r ) {
                break;
            }
            isPrimeR[primes[i] * j - l] = false;
        }
    }
    /*if(l == 1) {
        isPrimeR[0] = false;
    }*/
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	sieve();
	
	Long l , r;
	cin >> l >> r;
    segmentedSieve(l , r);
    
    Long x;
    cin >> x;
    if(isPrimeR[x - l]) {
    	cout << "es primo" << endl;
	}
	return 0;
}


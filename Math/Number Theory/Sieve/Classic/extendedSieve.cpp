#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 2e7;
bool isPrime[MX];
Long fact[MX];
vector<Long> primes;

//pending system test

void sieve(){ //O(MX log log MX)
	fill(isPrime, isPrime + MX , true);
	isPrime[0] = isPrime[1] = false;
	for(Long i = 2; i  < MX; i++){
		if(isPrime[i]) {
			primes.pb(i);
			fact[i] = i;
			if(i * i < MX){
				for(Long j = i * i; j < MX; j += i){
					isPrime[j] = false;
					fact[j] = i;
				}
			}
		}
	}
}

struct Factor{
	Long base,exp;
	Factor(){
	}
	Factor(Long b, Long e){
		base = b;
		exp = e;
	}
};
deque<Factor> factores;

void factorize(Long x){ //O(log x)
	factores.clear();
	while(x > 1){
		Long f = fact[x];
		Long exp = 0;
		while(x % f == 0){
			x /= f;
			exp++;
		}
		factores.push_front(Factor(f,exp));
	}
	
}

vector<Long> getDivisors(Long x) {
	vector<Long> ans = {1};
	while(x > 1) {
		Long f = fact[x];
		Long num = 1;
		Long sz = ans.size();
		while(x % f == 0) {
			num *= f;
			x /= f;
			
			for(Long i = 0; i < sz; i++) {
				ans.pb(num * ans[i]);
			}
		}
	}
	//sort(ans.begin(), ans.end());
	return ans;
}


int main() {
	sieve();
	return 0;
}



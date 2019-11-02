#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long Long;
 
const Long MX = 2e7;
bool isPrime[MX];
vector<Long> primes;

//https://codeforces.com/contest/230/problem/B

void sieve(){ //O(MX log log MX)
	fill(isPrime, isPrime + MX , true);
	isPrime[0] = isPrime[1] = false;
	for(Long i = 2; i  < MX; i++){
		if(isPrime[i]) {
			primes.pb(i);
			if(i * i < MX){
				for(Long j = i * i; j < MX; j += i){
					isPrime[j] = false;
				}
			}
		}
	}
}

Long A[MX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	long long n;
	cin >> n;
	
	
	for (long long i=0; i<n; i++){
		cin >> A[i];
	}
	sieve();
	for (int i=0; i<n; i++){
		long long p=(long long) sqrt(A[i]);
		if(p*p==A[i]){
			if(isPrime[p]==1) puts("YES");
			else puts("NO");
		}
		else puts("NO");
	}
 
 
	return 0;
}

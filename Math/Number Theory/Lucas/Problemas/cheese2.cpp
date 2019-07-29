#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MAX = 100;
Long fact[MAX];
Long inv[MAX];

Long fastPow(Long a, Long b, Long c){ //O(logb)
	if(b == 0){
		return 1;
	}
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	
	return (b%2 == 0)? temp : (a%c*temp)%c;
}

Long modInverse(Long a, Long m){ //O(logm)
	//m debe ser primo
	//if(__gcd(a,m) != 1) return -1;
	return fastPow(a,m-2,m);
}

void init(Long mod) {
	fact[0] = 1;
	inv[0] = 1;
	
	for(Long i = 1; i <= mod; i++) {
		fact[i] = (fact[i-1] * i) % mod;
		inv[i] = modInverse(fact[i] , mod);
	}
}

Long comb(Long N, Long M, Long mod) {
	if(N < M){
	  return 0;
	}
	
	return ( (fact[N] * inv[M]) % mod ) * inv[N-M] % mod; ;
}



Long lucas(Long N, Long M, Long mod) {
	//mod is prime
	init(mod);
	
	Long resp = 1;
	while(N > 0 || M > 0) {
		resp = (resp * comb(N % mod, M % mod , mod)) % mod;
		
		N /= mod;
		M /= mod; 
	}
	
	return resp;
}


Long gcd (Long a, Long b, Long & x, Long & y) { //O(max(loga,logb))
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    Long x1, y1;
    Long d = gcd (b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

Long modInverseGCD(Long a, Long m) { //O(max(loga,logb))
//a y m coprimes
	Long x,y;
	Long g = gcd(a,m,x,y);
	return (x%m+m)%m;
}


Long CRT(vector<Long> &d, vector<Long> &a) { //O( |d| log n)
	Long n = 1;
	
	Long k = d.size();
	for(Long i = 0; i < k; i++){
		n *= d[i];
	}
	
	Long x = 0;
	for(Long i = 0; i < k; i++){
		Long m = n / d[i];
		Long c = m * modInverseGCD(m , d[i]) % n;
		Long aux = c * a[i] % n;
		x = (x + aux) % n;
	}
	return x;
}

void doit() {
	Long N,M, mod;
	cin >> N >> M >> mod;
	
	vector<Long> d,r;
	Long i = 2;
	while(i*i <= mod) {
		if(mod % i == 0) {
			mod /= i;
			d.pb(i);
			r.pb(lucas(N,M,i));

		}
		i++;
	}
	
	if(mod > 1) {
		d.pb(mod);
		r.pb(lucas(N,M, mod));
	}
	
	cout << CRT(d, r) << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long T = 1;
	cin >> T;
	while(T--){
		doit();
	}
	return 0;
}




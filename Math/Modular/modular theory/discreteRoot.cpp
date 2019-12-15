#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;


// (x ^ a ) % m  = r , mod prime 

Long mult(Long a, Long b, Long mod){
	a %= mod;
	b %= mod;
	return (a * b ) % mod;
}

Long fastPow(Long a, Long b , Long mod){ //O(logb)
	Long ans = 1;
	while(b > 0){
		if(b & 1 == 1){ //b % 2 == 1
			ans = mult(ans ,a , mod);
		}
		a = mult(a , a  , mod);
		b >>= 1; //b /= 2;
	}
	return ans;
}


Long primitiveRoot(Long mod) { //O( mod log mod log phi(mod) + sqrt(mod))  
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

Long search(  vector<pair<Long, Long> > &v , Long x ){ //O(logn)
	// F F F... V V V
	Long ini = 0, fin = (Long)v.size() - 1;
	if(x < v[ini].second ) return -1; //todos F
	if(x > v[fin].second) return -1; //todos V
	
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= (ini + fin) / 2;
		
		if(x <= v[med].second ){
			fin=med;
		} 
		else {
			ini = med;
		}
	}

	//hay 2 valores ini es F y fin es V
	if(v[ini].second == x) {
		return v[ini].first;
	}
	if(v[fin].second == x) {
		return v[fin].first;
	}
	return -1;
}

bool cmp(pair<Long,Long> &p1, pair<Long,Long> &p2) {
	return p1.second < p2.second;
}

Long discreteLog(Long a , Long r , Long mod) {  //O(sqrt (mod) log mod)
	Long k = (Long)sqrt(mod) + 1;
	
	vector< pair<Long, Long> > f1;
	
	for(Long p = k; p >= 1; p--) {
		f1.pb({p , fastPow(a , p * k, mod)});
	}
	sort(f1.begin(),f1.end(), cmp); 
	
	for(Long q = 0; q <= k; q++) {
		Long cur = (r * fastPow(a , q , mod)) % mod;
		Long p = search(f1 , cur);
		if(p != -1) {
			return p * k - q; //solution could not be the smallest
			//if the smallest is needed, use modulo phi(mod)
		}
	}
	return -1;
}

Long discreteRoot(Long a , Long r , Long mod){
	Long g = primitiveRoot(mod);
	Long y = discreteLog(fastPow(g, a, mod) ,r, mod);
	return fastPow(g , y ,mod);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long exp , r , mod;
	cin >> exp >> r >> mod;
	debug(discreteRoot(exp, r, mod ));
	return 0;
}


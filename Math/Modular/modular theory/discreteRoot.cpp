#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

// (x ^ a ) % m  = r , mod prime 

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

Long search(vector<pair<Long, Long>> &v , Long x){ //O(log n)
	// F F F... T T T
	Long low = 0, high = (Long)v.size() - 1;
	if (x < v[low].second) return -1; //all F
	if(x > v[high].second) return -1; //all T
	while (high - low > 1){ 
		Long mid = low + (high - low) / 2;
		if (x <= v[mid].second) high = mid;
		else low = mid;
	}
	//2 values low -> F and high-> T
	if(v[low].second == x) return v[low].first;
	if(v[high].second == x) return v[high].first;
	return -1;
}

bool cmp(pair<Long,Long> &p1, pair<Long,Long> &p2) {
	return p1.second < p2.second;
}

Long discreteLog(Long a, Long r, Long mod) {  //O(sqrt (mod) log mod)
	Long k = (Long)sqrt(mod) + 1;
	vector<pair<Long, Long>> f1;
	for (Long p = k; p >= 1; p--) {
		f1.push_back({p, fastPow(a, p * k, mod)});
	}
	sort(f1.begin(),f1.end(), cmp); 
	for (Long q = 0; q <= k; q++) {
		Long cur = (r * fastPow(a, q, mod)) % mod;
		Long p = search(f1 , cur);
		if (p != -1) {
			return p * k - q; //solution may not be the smallest
			//if the smallest is needed, use modulo phi(mod)
		}
	}
	return -1;
}

Long discreteRoot(Long a, Long r, Long mod) {
	Long g = primitiveRoot(mod);
	Long y = discreteLog(fastPow(g, a, mod) ,r, mod);
	if (y == -1) return -1;
	return fastPow(g , y ,mod);
}

int main() {
	return 0;
}

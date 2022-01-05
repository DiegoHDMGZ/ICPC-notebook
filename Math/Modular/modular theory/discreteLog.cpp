#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

// (a ^ x ) % m  = r , gcd(a , m) = 1. Where x is the smallest solution
// because of Euler's theorem, x < phi(m)
// x = kp - q
// a ^ (kp) % m = (r * a ^ q ) % m  (using inverse modular)
// f1(p) = f2(q)
// k = sqrt(m) lead to the best complexity time
// Baby step - Gian Step Algorithm

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

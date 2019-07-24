#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;
//Chinese Remainder Theorem (Cormen)
//ai = x % di
//n = d1 * d2 * ... * dk
// di pairwise relatively prime
// Def : mi = n / di , ci = mi * invMod(mi , ni)
// => x = (a1 * c1 + a2 * c2 + ... + ak * ck) % n + n * t , t = 0, 1 , ...


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

int main() {
	Long k;
	cin >> k;
	
	vector<Long> a,d;
	for(Long i = 0; i < k ; i++){
		Long num;
		cin >> num;
		d.pb(num);
	}
	for(Long i = 0; i < k ; i++){
		Long num;
		cin >> num;
		a.pb(num);
	}
	cout << CRT(d,a) << endl;
	
	return 0;
}



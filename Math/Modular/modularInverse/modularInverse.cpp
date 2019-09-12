#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long fastPow(Long a, Long b, Long c){ //O(logb)
	if(b == 0){
		return 1;
	}
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	
	return (b%2 == 0)? temp : (a%c*temp)%c;
}

Long modInverse(Long a, Long m){ //O(logm)
	//m prime
	return fastPow(a,m-2,m);
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

Long modInverseGCD(Long a, Long m){ //O(max(loga,logb))
//a , m coprime
	Long x,y;
	Long g = gcd(a,m,x,y);
	return (x%m+m)%m;
}

int main() {
	Long mod = 1e9+7;
	return 0;
}

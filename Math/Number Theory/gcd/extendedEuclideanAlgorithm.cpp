#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//ax + by = gcd(a , b)
Long gcd (Long a, Long b, Long & x, Long & y) { //O(min(loga,logb))
	if(b == 0){
		x = 1;
		y = 0;
		return abs(a);
	}
	Long x2, y2;
	Long g = gcd(b, a % b , x2, y2);
	x = y2;
	y = x2 - (a / b) * y2;
	return g;
}

int main() {
	return 0;
}



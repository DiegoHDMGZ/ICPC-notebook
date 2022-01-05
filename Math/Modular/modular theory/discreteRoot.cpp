#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

// (x ^ a ) % m  = r , mod prime 
// Use discreteLog and primiteRoot files

Long discreteRoot(Long a, Long r, Long mod) {
	Long g = primitiveRoot(mod);
	Long y = discreteLog(fastPow(g, a, mod), r, mod);
	if (y == -1) return -1;
	return fastPow(g , y ,mod);
}

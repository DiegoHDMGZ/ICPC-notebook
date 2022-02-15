#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

// (x ^ e) % mod  = rem, mod prime 
// Use discreteLog and primiteRoot files

Long fastPow(Long a, Long b, Long mod);
Long primitiveRoot(Long mod);
Long discreteLog(Long base, Long rem, Long mod);

Long discreteRoot(Long e, Long rem, Long mod) {
	if (rem == 0) {
		//Assumption: 0^0 = 1
		if (e != 0 || mod == 1) return 0;
		else return -1;
	}
	Long g = primitiveRoot(mod);
	Long y = discreteLog(fastPow(g, e, mod), rem, mod);
	if (y == -1) return -1;
	return fastPow(g, y, mod);
}

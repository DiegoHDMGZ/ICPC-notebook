#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//ax + by = gcd(a , b)
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

int main() {
	return 0;
}



#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;

Long mod(Long a, Long b){
    Long r = a%b;
    if(r < 0) r+= b;
    return r;
}

Long divEnt(Long a, Long b){
    return (a-mod(a,b))/b;
}

Long gcd (Long a, Long b, Long & x, Long & y) { //O(max(loga,logb))

    if (a == 0) {
        if(b < 0){
            x = 0;
            y = -1;
            return -b;
        }
        x = 0;
        y = 1;
        return b;
    }
    Long x1, y1;
    Long d = gcd (mod(b,a), a, x1, y1);
    x = y1 - divEnt(b,a) * x1;
    y = x1;
    return d;
}

int main() {

	return 0;
}



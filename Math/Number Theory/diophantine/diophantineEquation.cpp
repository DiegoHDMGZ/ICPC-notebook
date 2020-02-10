#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long gcd(Long a, Long b, Long &x, Long &y) { //O(min(loga,logb))
	if(b == 0){
		if(a >= 0) {
			x = 1;
		} else {
			x = -1;
		}
		y = 0;
		return abs(a);
	}
	Long x2, y2;
	Long g = gcd(b, a % b , x2, y2);
	x = y2;
	y = x2 - (a / b) * y2;
	return g;
}

//ax + by = c
bool diophantine(Long a, Long b, Long c, Long &x, Long &y, Long &g) { //O(min(loga,logb))
    if(a == 0 && b == 0){
		if(c != 0) return false;
		else{
			x = y = g = 0;
			return true;
		}
	}
    g = gcd(a, b, x, y);
    if (c % g) {
        return false;
    }

    x *= c / g;
    y *= c / g;
    return true;
}

void shiftSolution(Long & x, Long & y, Long a, Long b, Long cnt) { //O(1)
    x += cnt * b;
    y -= cnt * a;
}

Long find_all_solutions(Long a, Long b, Long c, Long minx, Long maxx, Long miny, Long maxy) { //O(max(loga,logb))
    Long x, y, g;
    if (! diophantine(a, b, c, x, y, g)) return 0;
    a /= g;  b /= g;

    Long sign_a = a>0 ? +1 : -1;
    Long sign_b = b>0 ? +1 : -1;

    shiftSolution (x, y, a, b, (minx - x) / b);
    if (x < minx) shiftSolution (x, y, a, b, sign_b);
    if (x > maxx) return 0;
    Long lx1 = x;

    shiftSolution (x, y, a, b, (maxx - x) / b);
    if (x > maxx) shiftSolution (x, y, a, b, -sign_b);
    Long rx1 = x;

    shiftSolution (x, y, a, b, - (miny - y) / a);
    if (y < miny) shiftSolution (x, y, a, b, -sign_a);
    if (y > maxy) return 0;
    Long lx2 = x;

    shiftSolution (x, y, a, b, - (maxy - y) / a);
    if (y > maxy) shiftSolution (x, y, a, b, sign_a);
    Long rx2 = x;

    if (lx2 > rx2) swap (lx2, rx2);
    Long lx = max (lx1, lx2);
    Long rx = min (rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}

int main() {

	return 0;
}



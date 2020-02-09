#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

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

bool find_any_solution(Long a, Long b, Long c, Long &x0, Long &y0, Long &g) { //O(max(loga,logb))
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution (Long & x, Long & y, Long a, Long b, Long cnt) { //O(1)
    x += cnt * b;
    y -= cnt * a;
}

Long find_all_solutions (Long a, Long b, Long c, Long minx, Long maxx, Long miny, Long maxy) { //O(max(loga,logb))
    Long x, y, g;
    if (! find_any_solution (a, b, c, x, y, g)) return 0;
    a /= g;  b /= g;

    Long sign_a = a>0 ? +1 : -1;
    Long sign_b = b>0 ? +1 : -1;

    shift_solution (x, y, a, b, (minx - x) / b);
    if (x < minx) shift_solution (x, y, a, b, sign_b);
    if (x > maxx) return 0;
    Long lx1 = x;

    shift_solution (x, y, a, b, (maxx - x) / b);
    if (x > maxx) shift_solution (x, y, a, b, -sign_b);
    Long rx1 = x;

    shift_solution (x, y, a, b, - (miny - y) / a);
    if (y < miny) shift_solution (x, y, a, b, -sign_a);
    if (y > maxy) return 0;
    Long lx2 = x;

    shift_solution (x, y, a, b, - (maxy - y) / a);
    if (y > maxy) shift_solution (x, y, a, b, sign_a);
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



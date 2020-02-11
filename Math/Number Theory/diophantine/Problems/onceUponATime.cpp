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
bool diophantine(Long a, Long b, Long c, Long &x, Long &y, Long &g) { //O(min(loga,logb) + #solutions)
    if(a == 0 && b == 0){
		if(c != 0) return false;
		else{
			x = y = g = 0;
			return true;
		}
	}
    g = gcd(a, b, x, y);
    if (c % g != 0) {
        return false;
    }

    x *= c / g;
    y *= c / g;
    return true;
}

Long divDown(Long a, Long b){
    Long d = abs(a) / abs(b);
    if((a > 0 && b > 0) || (a < 0 && b < 0)){
        return d;
    } else {
        if(a % b == 0){
            return -d;
        } else {
            return -d - 1;
        }
    }
}
 
Long divUp(Long a, Long b){
    Long d = abs(a) / abs(b);
    if((a > 0 && b > 0) || (a < 0 && b < 0)){
        if(a % b == 0) return d;
        else return d + 1;
    } else {
        return -d;
    }
}

Long solve(Long a, Long b, Long c, Long lx, Long ly) { //O(min(loga,logb))
    Long x0, y0, g;
    if (!diophantine(a, b, c, x0, y0, g)) return -1;
    
	if(a == 0){
        if(b == 0){
			return lx;
        } else {
            if((ly <= c / b) ){
				return lx;
            } else {
                return -1;
            }
        }
    } else if(b == 0){
        if((lx <= c / a) ){
			return c / a ;
        } else {
            return -1;
        }
    }

	Long kMin, kMax;
	bool flagMin = false;
	bool flagMax = false;
    if(b > 0){
        kMin = divUp((lx - x0) * g , b);
        flagMin = true;
    } else {
        kMax = divDown((lx - x0) * g , b);
        flagMax = true;
    }
    if(a > 0){
		if(!flagMax) kMax = divDown((y0 - ly) * g , a);
		else kMax = min(kMax, divDown((y0 - ly) * g , a) );
		flagMax = true;
    } else {
		if(!flagMin) kMin = divUp((y0 - ly) * g , a);
        else kMin = max(kMin, divUp((y0 - ly) * g , a));
        flagMin = true;
    }
	
	if(flagMax && flagMin && kMin > kMax) return -1;
	
	if(b > 0){
		assert(flagMin);
		return x0 + kMin * (b / g);
	} else {
		assert(flagMax);
		return x0 + kMax * (b / g);
	}
}


//n + mx = ay + k
//mx - ay = k - n
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m , a , k;
	while(cin >> n >> m >> a >> k){
		if(abs(n) + abs(m) + abs(a) + abs(k) == 0) break;
		Long x = solve(m , -a , k - n , 0 , 1 );

		if(x == -1) cout << "Impossible\n";
		else cout << n + m * x << "\n";
	}

	return 0;
}

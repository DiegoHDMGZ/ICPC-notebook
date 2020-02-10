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

vector<pair<Long,Long> > getAllSolutions(Long a, Long b, Long c, Long lx, Long rx, Long ly, Long ry) { //O(min(loga,logb))
    Long x0, y0, g;
    if (!diophantine(a, b, c, x0, y0, g)) return {};

	Long kMinX, kMaxX;
    if(b > 0){
        kMinX = divUp((lx - x0) * g , b);
        kMaxX = divDown((rx - x0) * g , b);
    } else {
        kMinX = divUp((rx - x0) * g , b);
        kMaxX = divDown((lx - x0) * g , b);
    }
    Long kMinY, kMaxY;
    if(a > 0){
        kMinY = divUp((y0 - ry) * g , a);
        kMaxY = divDown((y0 - ly) * g , a);
    } else {
        kMinY = divUp((y0 - ly) * g , a);
        kMaxY = divDown((y0 - ry) * g , a);
    }
 
    Long kMin = max(kMinX, kMinY);
    Long kMax = min(kMaxX, kMaxY);
	
	if(kMin > kMax) return {};
	
	vector<pair<Long,Long>> ans;
	for(Long k = kMin; k <= kMax; k++){
		ans.push_back({x0 + k * (b / g) , y0 - k * (b / g)});
	}
	return ans;
}

int main() {

	return 0;
}



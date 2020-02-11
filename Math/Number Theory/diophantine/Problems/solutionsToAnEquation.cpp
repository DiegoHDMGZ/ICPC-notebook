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
 
Long getAllSolutions(Long a, Long b, Long c, Long lx, Long rx, Long ly, Long ry) { //O(min(loga,logb))
    Long x0, y0, g;
    if (!diophantine(a, b, c, x0, y0, g)) return 0;
   
    if(a == 0){
        if(b == 0){
            return (rx - lx + 1) * (ry - ly + 1);
        } else {
            if((ly <= c / b) && (c / b <= ry)){
                return rx - lx + 1;
            } else {
                return 0;
            }
        }
    } else if(b == 0){
        if((lx <= c / a) && (c / a <= rx)){
            return ry - ly + 1;
        } else {
            return 0;
        }
    }
   
	Long kMin, kMax;
    if(b > 0){
        kMin = divUp((lx - x0) * g , b);
        kMax = divDown((rx - x0) * g , b);
    } else {
        kMin = divUp((rx - x0) * g , b);
        kMax = divDown((lx - x0) * g , b);
    }
    if(a > 0){
        kMin = max(kMin , divUp((y0 - ry) * g , a));
        kMax = min(kMax, divDown((y0 - ly) * g , a) );
    } else {
        kMin = max(kMin, divUp((y0 - ly) * g , a));
        kMax = min(kMax, divDown((y0 - ry) * g , a));
    }
   
    if(kMin > kMax) return 0;
   
    return kMax - kMin + 1;
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Long T;
    cin >> T;
    REP(t, T){
        Long a, b , c, lx, rx, ly, ry;
        cin >> a >> b >> c >> lx >> rx >> ly >> ry;
        c = -c;
        cout << "Case " << t + 1 << ": " << getAllSolutions(a, b , c , lx, rx, ly, ry) << endl;
    }
 
    return 0;
}
 

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/problemset/problem/7/C

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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long a, b , c;
	cin >> a >> b >> c;
	c = -c;
	Long x , y , g; 
	if(!diophantine(a , b , c , x , y , g)){
		cout << -1 << endl;
	} else {
		cout << x << " " << y << endl;
	}

	return 0;
}

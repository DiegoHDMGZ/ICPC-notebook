#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://codeforces.com/blog/entry/61290

Long normalize(Long x, Long mod){
	return (x + mod) % mod;
}

Long gcd(Long a, Long b, Long &x, Long &y) { //O(max(loga,logb))
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    Long x1, y1;
    Long d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool CRT(pair<Long, Long > p1  , pair<Long , Long > p2, pair<Long , Long > &resp) {
	if(p1.second < p2.second) {
		swap(p1 , p2);
	}
	Long r = p1.second - p2.second;
	
	Long x,y;
	
	Long g = gcd(p1.first , p2.first , x , y);
	
	x *= -1;
	
	if(r % g != 0 ) {
		return false;
	}
	
	Long lcm = (p1.first / g ) * p2.first;
	
	//a1 + d1 * k1 = a2 + d2 * k2
	//num = (a1 + x * r * d1 / g) % lcm
	//Property : (ca) % (cb) = c * (a % b)
	//=> num = (a1 + ( (x * r / g) % (d2/g) ) * d1 ) % lcm
	
	Long aux = x* (r / g );
	Long den = p2.first / g;
	
	aux = (aux % den) * p1.first % lcm;
	aux = normalize(aux, lcm); //normalize
	aux = (aux + p1.second) % lcm;
	
	resp = make_pair(lcm , aux);
	
	return true;	
}

bool CRT(vector<Long> &d, vector<Long> &a, pair<Long, Long> &resp) { //O( |d| log LCM(d1, d2 , ... , ) )
	// ( lcm , mod)
	pair<Long , Long > ant = make_pair(d[0], a[0]);
	
	Long sz = d.size();
	for(Long i = 1; i < sz ; i++) {
		if( !CRT(ant , make_pair(d[i] , a[i]) , ant ) ) {
			return false;
		}
	}
	
	resp = ant;
	return true;
}

int main() {
	return 0;
}




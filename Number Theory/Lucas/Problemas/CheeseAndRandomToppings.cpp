#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MAX = 100;
Long fact[MAX];
Long inv[MAX];

Long fastPow(Long a, Long b, Long c){ //O(logb)
	if(b == 0){
		return 1;
	}
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	
	return (b%2 == 0)? temp : (a%c*temp)%c;
}

Long modInverse(Long a, Long m){ //O(logm)
	//m debe ser primo
	//if(__gcd(a,m) != 1) return -1;
	return fastPow(a,m-2,m);
}

void init(Long mod) {
	fact[0] = 1;
	inv[0] = 1;
	
	for(Long i = 1; i <= mod; i++) {
		fact[i] = (fact[i-1] * i) % mod;
		inv[i] = modInverse(fact[i] , mod);
	}
}

Long comb(Long N, Long M, Long mod) {
	if(N < M){
	  return 0;
	}
	
	return ( (fact[N] * inv[M]) % mod ) * inv[N-M] % mod; ;
}



Long lucas(Long N, Long M, Long mod) {
	//mod is prime
	init(mod);
	
	Long resp = 1;
	while(N > 0 || M > 0) {
		resp = (resp * comb(N % mod, M % mod , mod)) % mod;
		
		N /= mod;
		M /= mod; 
	}
	
	return resp;
}


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

void doit() {
	Long N,M, mod;
	cin >> N >> M >> mod;
	
	if(mod == 1){
		cout << 0 << endl;
		return;
	}
	vector<Long> d,r;
	Long i = 2;
	while(i*i <= mod) {
		if(mod % i == 0) {
			mod /= i;
			d.pb(i);
			r.pb(lucas(N,M,i));

		}
		i++;
	}
	
	if(mod > 1) {
		d.pb(mod);
		r.pb(lucas(N,M, mod));
	}
	
	pair<Long , Long> resp;
	CRT(d, r, resp);
	
	cout << resp.second << endl;
	
//	system("pause");
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long T = 1;
	cin >> T;
	while(T--){
		doit();
	}
	return 0;
}




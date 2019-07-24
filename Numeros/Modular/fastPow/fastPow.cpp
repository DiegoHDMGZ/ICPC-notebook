#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;

// (a^x)% mod = (a^r) % mod. Donde r = x % (mod-1) , mod primo

Long fastPow(Long a, Long b , Long c){ //O(logb)
	if(b == 0) return 1LL;
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	if(b%2==0) return temp;
	
	return (a*temp)%c;
}

Long modExp(Long a, Long b , Long mod){ //O(logb) 
	a = a %mod;
	
	b = b%(mod-1);
	
	return fastPow(a,b,mod);
}

int main() {
	return 0;
}



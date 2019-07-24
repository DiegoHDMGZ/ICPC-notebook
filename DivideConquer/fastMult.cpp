#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

Long fastMult(Long a, Long b, Long c){
	if(b == 0){
		return 0;
	}
	
	if(b%2==0){
		return 2 * fastMult(a  , b / 2, c) % c;
	}
	
	return (2 * fastMult( a , b / 2 , c) % c + a) % c;
}

int main() {
	
	cout << fastMult(8 , 7 , 15) << endl;
	return 0;
}



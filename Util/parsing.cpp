#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

vector<Long> v;

void parsing( string &s ){
	Long tokens;  
	stringstream entrada( s );
	
	while( entrada >> tokens ){
		v.push_back(tokens);
	}
}

int main() {

	return 0;
}



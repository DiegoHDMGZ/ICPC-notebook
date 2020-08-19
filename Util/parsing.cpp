#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

vector<Long> parsing( string &s ){
	Long tokens;  
	stringstream in( s );
	vector<Long> out;
	while( in >> tokens ){
		out.push_back(tokens);
	}
	return out;
}

int main() {

	return 0;
}



#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

vector<Long> v;

Long kadane(){
	Long maxSoFar = 0;
	Long maxEndingHere = 0;
	
	REP(i , v.size() ) {
		maxEndingHere = max(v[i],maxEndingHere+v[i]);
		maxSoFar = max(maxSoFar,maxEndingHere);
	}
	return maxSoFar;
}

int main() {

	return 0;
}




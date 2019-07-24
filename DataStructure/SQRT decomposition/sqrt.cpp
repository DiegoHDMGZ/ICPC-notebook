#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5 + 2;
const Long SQ = sqrt(MAX) + 5;

Long N;
Long sq; //sqrt(N)

Long block(Long i) {
	return i / sq;
}

Long lowLim(Long i) {
	return ( (i / sq)  ) * sq;
}

Long upperLim(Long i) {
	return min(lowLim(i) + sq - 1 , N - 1 );
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);



	return 0;
}


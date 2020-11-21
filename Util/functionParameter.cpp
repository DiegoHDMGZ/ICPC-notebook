#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long add(Long a, Long b) {
	return a + b;
}

Long sub(Long a, Long b) {
	return a - b;
}

Long operate(Long a, Long b, Long (*op)(Long, Long)) {
	return (*op)(a, b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cout << operate(5, 7 , add) << endl;
	cout << operate(5 , 7 , sub) << endl;

	return 0;
}

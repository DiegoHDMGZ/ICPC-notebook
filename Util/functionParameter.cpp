#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long add(Long a, Long b) {
	return a + b;
}

Long subs(Long a, Long b) {
	return a - b;
}

Long oper(Long a, Long b, Long (*oper)(Long, Long)) {
	return (*oper)(a, b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cout << oper(5, 7 , add) << endl;
	cout << oper(5 , 7 , subs) << endl;

	return 0;
}

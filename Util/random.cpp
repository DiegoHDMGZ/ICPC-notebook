#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(ll i = 0; i < n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

int main() {
	vector<Long> v;
	shuffle(v.begin() , v.end() , rng);
	return 0;
}



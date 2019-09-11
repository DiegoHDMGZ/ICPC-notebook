#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct PartialSum{
	Long A[MX];
	Long dif[MX + 5];
	
	void update(Long l, Long r, Long delta) {
		dif[l] += delta;
		dif[r + 1] -= delta;
	}

	void finalUpdate(Long n) {
		for(Long i = 1 ; i < n; i++) {
			dif[i] += dif[i - 1];
		}
		REP(i , n) {
			A[i] += dif[i];
		}
	}

	Long query(Long pos){
		return A[pos];
	}
	
}ps;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n ,q;
	cin >> n >> q;
	REP( i, q) {
		Long l , r ,d;
		cin >> l >> r >> d;
		ps.update(l , r , d);
	}
	ps.finalUpdate(n);
	
	REP(i , n) {
		cout << ps.query(i) << " , ";
	}
	cout << endl;
	
	return 0;
}

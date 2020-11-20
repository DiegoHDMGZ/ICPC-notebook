#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct PartialSum{
	Long dif[MX + 1];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			dif[i] = 0;
		}
	}
	
	void build(vector<Long> &v) {
		dif[0] = 0;
		for (Long i = 0; i < v.size(); i++) {
			dif[i + 1] = 0;
			update(i , i, v[i]);
		}
	}
	
	void update(Long l, Long r, Long delta) { //O(1)
		//a[i] += delta
		dif[l] += delta;
		dif[r + 1] -= delta;
	}

	void update(Long n) { //O(n)
		//last update before answering queries
		for (Long i = 1; i < n; i++) {
			dif[i] += dif[i - 1];
		}
	}
	
	Long query(Long pos) { //O(1)
		return dif[pos];
	}
}ps;

int main() {
	return 0;
}

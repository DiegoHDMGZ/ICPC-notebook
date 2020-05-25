#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;
typedef tree<pair<Long,Long>, null_type, less<pair<Long,Long> > , rb_tree_tag, tree_order_statistics_node_update> ordered_set;

//https://www.codechef.com/MARCH19A/problems/SUBPRNJL

//find_by_order(k) -> return iterator to the k-th largest element (0-indexed)
//order_of_key(num) -> # of items strictly smaller than num 

const Long MAX = 2005;
Long A[MAX];
Long cnt[MAX];
void test() {
	Long N,K;
	cin >> N >> K;
	
	REP(i , N) {
		cin >> A[i];
	}
	
	Long ans = 0;
	REP(l , N) {
		ordered_set s;
	
		for(Long r = l; r < N; r++) {
			cnt[A[r]]++;
			s.insert({A[r] , cnt[A[r]]});
			Long m = K / (r - l + 1);
			if(m * (r - l + 1) < K) {
				m++;
			}
			Long x = (K - 1) / m;
			Long num = (*s.find_by_order(x)).first;
			Long c = cnt[num];
			if(cnt[c] > 0) {
				ans++;
			}
		}
		for(Long r = l; r < N; r++) {
			cnt[A[r]]--;
		}
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	
	REP(i, T) {
		test();
	}
	return 0;
}

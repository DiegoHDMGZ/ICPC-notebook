#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/contest/276/problem/C
const Long MX = 1e5;

struct PartialSum{
	Long A[MX];
	Long dif[MX + 1];
	
	void build(vector<Long> &v){
		for(Long i = 0; i < v.size(); i++){
			update(i , i, v[i]);
		}
	}
	
	void update(Long l, Long r, Long delta) { //O(1)
		dif[l] += delta;
		dif[r + 1] -= delta;
	}

	void finalUpdate(Long n) { //O(n)
		A[0] = dif[0];
		for(Long i = 1; i < n; i++){
			A[i] = A[i - 1] + dif[i];
		}
	}
	Long query(Long pos){ //O(1)
		return A[pos];
	}
	
}partial;



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, Q;
	cin >> n >> Q;
	
	vector<Long> v(n);
	for(Long i = 0; i < n; i++){
		cin >> v[i];
	}
	
	for(Long q = 0; q < Q; q++){
		Long l , r;
		cin >> l >> r;
		l--;
		r--;
		partial.update(l , r, 1);
	}
	partial.finalUpdate(n);
	
	vector<Long> freq(n);
	for(Long i = 0; i < n; i++){
		freq[i] = partial.query(i);
	}
	sort(freq.begin(), freq.end());
	sort(v.begin(), v.end());
	
	Long ans = 0;
	for(Long i = 0; i < n; i++){
		ans += freq[i] * v[i];
	}
	cout << ans << endl;
	return 0;
}
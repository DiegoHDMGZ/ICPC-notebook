#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 4e5;
vector<Long> getDivisors(Long n) {
	vector<Long> v;
	for(Long i = 1; i * i <= n; i++) {
		if(n % i == 0) {
			if(i != 1) {
				v.pb(i);
			}
			if(i * i != n) {
				v.pb(n / i);
			}
			
			
		}
	}
	sort(v.begin() , v.end());
	/*debug(n);
	cout << "v = ";
	REP(i ,v.size()) {
		cout << v[i] << " ";
	}
	cout << endl;*/
	return v;
}

bool used[MAX];
Long dp[MAX];

Long mex(set<Long> &s){
	Long ans = 0;
	for(Long x : s){
		if(ans != x){
			return ans;
		}
		ans++;
	}
	return ans;
}

Long grundy(Long x) {
	
	if(x <= 2) {
		return false;
	}
	if(used[x]) {
		return dp[x];		
	}
	used[x] = true;
	vector<Long> v = getDivisors(2 * x);
	
	
	if(v.size() == 0) {
		return dp[x] = 0;
	}
	
	set<Long> s;
	for(Long n : v) {
		Long g = 0;
		if((2 * x / n + 1 - n) > 0 && (2 * x / n + 1 - n) % 2 == 0) {
			
			Long a =(2 * x / n + 1 - n) / 2;
			if(a == 0) {
				continue;
			}

			for(Long i = 0; i < n; i++) {
				g = g xor grundy(a + i);
			}

			s.insert(g);
			
		}
		
	}
	return dp[x] = mex(s);
} 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long x;
	cin >> x;
	

	if(grundy(x) > 0){
		vector<Long> v = getDivisors(2 * x);
		for(Long n : v) {
			Long g = 0;
			if((2 * x / n + 1 - n) > 0 && (2 * x / n + 1 - n) % 2 == 0) {
				
				Long a =(2 * x / n + 1 - n) / 2;
				if(a == 0) {
					continue;
				}

				for(Long i = 0; i < n; i++) {
					g = g xor grundy(a + i);
				}

				if(g == 0) {
					cout << n << endl;
					return 0;
				}
				
			}
			
		}
	} else {
		cout << -1 << endl;
	}
	
	return 0;
}

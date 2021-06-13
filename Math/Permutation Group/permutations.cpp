#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Permutations p of size n with 0 <= p[i] < n 

vector<int> compose(vector<int> a, vector<int> b) {
	int n = a.size();
	vector<int> c(n);
	for (int i = 0; i < n; i++) {
		c[i] = a[b[i]];
	}
	return c;
}

vector<vector<int>> getCycles(vector<int> p) {
	int n = p.size();
	vector<bool> used(n, false);
	vector<vector<int>> cycles;
	
	for (int i = 0; i < n; i++) {
		int x = i;
		if (used[x]) continue;
		vector<int> cycle;
		while (!used[x]) {
			used[x] = true;
			cycle.push_back(x);
			x = p[x];
		}
		cycles.push_back(cycle);
	}
	
	return cycles;
}

vector<int> getPermutation(vector<vector<int>> cycles) {
	int n = 0;
	for (int i = 0; i < cycles.size(); i++) {
		n += cycles[i].size();
	}
	vector<int> p(n);
	for (auto cycle : cycles) {
		int sz = cycle.size();
		for (int i = 0; i < sz; i++) {
			int prev = i - 1;
			if (i == 0) prev = sz - 1;
			p[cycle[prev]] = cycle[i];
		}
	}
	return p;
}

vector<int> inverse(vector<int> &p) {
	int n = p.size();
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[p[i]] = i;
	}
	return ans;
}

vector<vector<int>> inverse(vector<vector<int>> cycles) {
	auto ans = cycles;
	reverse(ans.begin(), ans.end());
	for (auto &cycle : ans) {
		reverse(cycle.begin(), cycle.end());
	}
	return ans;
}

vector<pair<int, int>> getTranspositions(vector<vector<int>> cycles) {
	//it wont be disjoint cycles anymore
	int n = 0;
	for (int i = 0; i < cycles.size(); i++) {
		n += cycles[i].size();
	} 
	assert(n >= 1);
	vector<pair<int, int>> ans;
	for (auto cycle : cycles) {
		int sz = cycle.size();
		if (sz == 1) {
			int other = 0;
			if (cycle[0] == other) {
				other++;
			}
			ans.push_back({cycle[0], other});
			ans.push_back({other, cycle[0]});
		} else {
			for (int i = sz - 1; i > 0; i--) {
				ans.push_back({cycle[0], cycle[i]});
			}
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const int MX = 1e5;
struct DSU{
	int parent[MX];
	vector<int> elements[MX];
	
	void build(int n) {
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
	}
	
	void make_set(int u) { 
		parent[u] = u;
		elements[u].push_back(u);
	}
	
	int find(int u) {
		return parent[u];
	}
	
	void join(int u, int v) { //O(log n) amortized
		u = parent[u];
		v = parent[v];
		if (u != v) {
			if (elements[u].size() > elements[v].size()) {
				swap(u , v);
			}
			for (int x : elements[u]) {
				elements[v].push_back(x);
				parent[x] = v;
			}
		}
	}
}dsu;
 

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
struct DSU{
	Long parent[MX];
	Long size[MX];
	Long parity[MX];
	bool bipartite;
	
	void make_set(Long u) { //O(1)
		parent[u] = u;
		size[u] = 1;
		parity[u] = 0;
	}
	
	void build(int n) { //O(n)
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
		bipartite = true;
	}
	
	pair<Long,Long> find(Long u) { //O(1) amortized
		if (parent[u] == u) {
			return {u, 0};
		} 
		auto p = find(parent[u]);
		parent[u] = p.first;
		parity[u] ^= p.second;
		return {parent[u] , parity[u]};
	}
	
	Long getParity(Long u) { //O(1) amortized
		return find(u).second;
	}
	
	void join(Long u, Long v) { //O(1) amortized
		auto pu = find(u);
		auto pv = find(v);
		u = pu.first;
		v = pv.first;
		if (u != v) {
			if (size[u] > size[v]) {
				swap(u, v);
			}
			parent[u] = v;
			size[v] += size[u];
			parity[u] ^= pu.second ^ pv.second ^ 1;
		} else {
			bipartite &= pu.second != pv.second;
		}
	}
}dsu;

int main() {
	return 0;
}

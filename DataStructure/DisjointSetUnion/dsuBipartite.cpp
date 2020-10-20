#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 3e5;
struct DSU{
	Long parent[MX];
	Long size[MX];
	Long parity[MX];
	
	void make_set(Long u) {
		parent[u] = u;
		size[u] = 1;
		parity[u] = 0;
	}
	
	void build(int n) {
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
	}
	
	pair<Long,Long> find(Long u) {
		if (parent[u] == u) {
			return {u, 0};
		} 
		auto p = find(parent[u]);
		parent[u] = p.first;
		parity[u] ^= p.second;
		return {parent[u] , parity[u]};
	}
	
	Long getParity(Long u) {
		return find(u).second;
	}
	
	bool join(Long u, Long v) {
		//true if is still bipartite after adding the edge
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
			return true;
		} else {
			return pu.second != pv.second;
		}
	}
}dsu;

int main() {
	return 0;
}


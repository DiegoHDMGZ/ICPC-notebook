#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long MX = 1e5;

struct DSU{
	Long parent[MX];
	Long size[MX];
	Long depth[MX];
	
	void make_set(Long u) { //O(1)
		parent[u] = u;
		size[u] = 1;
		depth[u] = 0;
	}
	
	void build(int n) { //O(n)
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
	}
	
	pair<Long, Long> find(Long u) { //O(1) amortized
		if (u == parent[u]) {
			return {u, 0};
		}
		auto p = find(parent[u]);
		parent[u] = p.first;
		depth[u] += p.second;
		return {parent[u], depth[u]};
	}
	
	Long getDepth(Long u) { //O(1) amortized
		return find(u).second;
	}
	
	void join(Long u, Long v) { //O(1) amortized
		u = find(u).first;
		v = find(v).first;
		if (u != v) {
			if (size[u] > size[v]) {
				swap(u, v);
			}
			parent[u] = v;
			size[v] += size[u];
			depth[u] = 1;
		}
	}
} dsu;

int main() {
	return 0;
}

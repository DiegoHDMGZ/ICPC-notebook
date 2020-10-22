#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long MX = 1e5;

struct DSU{
	Long parent[MX];
	Long size[MX];
	
	void make_set(Long u) { //O(1)
		parent[u] = u;
		size[u] = 1;
	}
	
	void build(int n) { //O(n)
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
	}
	
	Long find(Long u) { //O(1) amortized
		if (u == parent[u]) {
			return u;
		}
		return parent[u] = find(parent[u]);
	}
	
	void join(Long u, Long v) { //O(1) amortized
		u = find(u);
		v = find(v);
		if (u != v) {
			if (size[u] > size[v]) {
				swap(u, v);
			}
			parent[u] = v;
			size[v] += size[u];
		}
	}
} dsu;

int main() {
	return 0;
}

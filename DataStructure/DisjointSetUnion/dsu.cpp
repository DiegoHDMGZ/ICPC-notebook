#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long MX = 100000;

struct DSU{
	Long parent[MX];
	Long size[MX];
	
	void make_set(Long v){ //O(1)
		parent[v] = v;
		size[v] = 1;
	}
	
	void build(int n) {
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
	}
	
	Long find(Long u){ //O(1) amortized
		if(u == parent[u]){
			return u;
		}
		
		return parent[u] = find(parent[u]);
	}
	
	void join(Long u, Long v){ //O(1) amortized
		u = find(u);
		v = find(v);
		
		if(u != v){
			if(size[u] < size[v]){
				swap(u, v);
			}
			parent[v] = u;
			size[u] += size[v];
		}
	}
} dsu;

int main() {
	return 0;
}



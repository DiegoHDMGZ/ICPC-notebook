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
	
	void make_set(Long u) { //O(1)
		parent[u] = u;
		size[u] = 1;
	}
	
	void build(int n) {
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

struct Edge{
	Long u, v, w;
	Edge() {}
	Edge(Long u, Long v, Long w) : u(u) , v(v) , w(w) {}
	bool operator <(Edge const &other) const{
        return w < other.w;
    }
};

struct Graph{
	vector<Edge> edges;
	vector<pair<Long, Long>> tree[MX]; //node, weight
	
	void clear(Long n) { //O(n)
		for (int i = 0; i < n; i++) {
			tree[i].clear();
		}
		edges.clear();
	}
	
	void addEdge(Long u, Long v, Long w) {
		edges.push_back(Edge(u , v , w));
	}
	
	Long getMST(Long n) { //O(mlogn)
		Long totalWeight = 0;
		dsu.build(n);
		sort(edges.begin(),edges.end());
		for (Edge e : edges) {
			if (dsu.find(e.u) != dsu.find(e.v)) {
				totalWeight += e.w;
				tree[e.u].push_back({e.v, e.w});
				tree[e.v].push_back({e.u, e.w});
				dsu.join(e.u,e.v);				
			}
		}
		return totalWeight;
	}
} G;

int main() {
	return 0;
}

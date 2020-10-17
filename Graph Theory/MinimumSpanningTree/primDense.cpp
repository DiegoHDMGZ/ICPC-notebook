#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Endpoint{
	Long node , w;
	Endpoint(Long node, Long w): node(node), w(w) {}
};

struct Graph { 
	vector<Endpoint> adj[MX];
	Long minWeight[MX];
	Long parent[MX]; 

	void clear(Long n) { 
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}

	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back(Endpoint(v , w));
		adj[v].push_back(Endpoint(u , w));
	}

	Long getMST(Long n, Long root = 0) { //O(n^2)
		Long totalWeight = 0;
		vector<bool> onTree(n, false);
		fill(minWeight, minWeight + n, INF);
		minWeight[root] = 0;
		parent[root] = -1;
		
		for (Long nodes = 1; nodes <= n; nodes++) {
			Long choice = -1;
			for (Long u = 0; u < n; u++) {
				if (!onTree[u]) {
					if (choice == -1 || minWeight[u] < minWeight[choice]) {
						choice = u;
					}
				}
			}
			if (minWeight[choice] == INF) {
				//graph is not connected
				return -1;
			}
			totalWeight += minWeight[choice];
			onTree[choice] = true;
			for (Endpoint e : adj[choice]) {
				if (!onTree[e.node] && e.w < minWeight[e.node]) {
					minWeight[e.node] = e.w;
					parent[e.node] = e.w;
				}
			}
		}
		return totalWeight;
	}
} G;

int main() {
	return 0;
}

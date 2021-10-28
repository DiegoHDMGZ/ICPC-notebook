#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)

using namespace std;

typedef long long Long;
const Long MX = 1e5;

//In a directed graph, a Strongly connected component (SCC) is a maximal subgraph 
//such that each vertex is reachable from every other vertex
//The graph can be condensed in their scc to form a DAG

struct Graph {
	vector<vector<int>> adj;
	vector<vector<int>> rev;
	vector<bool> vis;
	vector<int> order, scc;
	int numComponent;
	
	Graph(int n) {
		adj.resize(n);
		rev.resize(n);
	}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		rev[v].push_back(u);
	}
	
	void dfs(int u) { //O(V + E)
		vis[u] = true;
		for (int v : adj[u]) {
			if (!vis[v]) dfs(v);
		}
		order.push_back(u);
	}
	
	void findComponent(int u) { //O(V + E)
		scc[u] = numComponent;
		for (int v : rev[u]) {
			if (scc[v] == -1) findComponent(v);
		}
	}
	
	void calculateSCC() { //O(V + E)
		int n = adj.size();
		order.clear();
		numComponent = 0;
		vis.resize(n, false);
		scc.resize(n, -1);
		for (int u = 0; u < n; u++) {
			if (!vis[u]) dfs(u);
		}
		for (int i = 0; i < n; i++) {
			int u = order[n - 1 - i];
			if (scc[u] == -1) {
				findComponent(u);
				numComponent++;
			}
		}
	}
};

int main() {
	return 0;
}

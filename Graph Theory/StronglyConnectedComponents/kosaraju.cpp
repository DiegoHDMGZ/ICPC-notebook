#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)

using namespace std;

typedef long long Long;
const Long MX = 1e5;

//In a directed graph , a Strongly connected component (SCC) is a maximal subgraph 
//such that each vertex is reachable from every other vertex
//The graph can be condensed in their scc to form a DAG

struct Graph {
	vector<Long> adj[MX];
	vector<Long> rev[MX];
	bool vis1[MX];
	bool vis2[MX];
	vector<Long> order,component;
	Long numComponent = 0;
	Long scc[MX];
	
	void clear(Long n) {
		REP(i , n) {
			adj[i].clear();
			rev[i].clear();
			vis1[i] = vis2[i] = false;
		}
		order.clear();
		component.clear();
		numComponent = 0;
	}
	
	void addEdge(Long u, Long v) {
		adj[u].push_back(v);
		rev[v].push_back(u);
	}
	
	void dfs1(Long u){ //O(V + E)
		vis1[u] = true;
		for (Long v : adj[u]) {
			if (!vis1[v]) {
				dfs1(v);
			}
		}
		order.push_back(u);
	}
	
	void dfs2(Long u) { //O(V + E)
		vis2[u] = true;
		component.push_back(u);
		for (Long v : rev[u]) {
			if (!vis2[v]) {
				dfs2(v);
			}
		}
	}
	
	void calculateSCC(Long n) { //O(V + E)
		REP(i, n) {
			if (!vis1[i]) dfs1(i);
		}
		REP(i, n) {
			Long u = order[n - 1 - i];
			if (!vis2[u]) {
				dfs2(u);
				for (Long v : component) {
					scc[v] = numComponent;
				}
				numComponent++;
				//all nodes in "component" form a scc
				component.clear();
			}
		}
	}
} G;

int main() {
	return 0;
}

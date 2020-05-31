#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;
const Long MX = 1e5;

// In a directed graph , a Strongly connected component (SCC) is a maximal subgraph 
//such that each vertex is reachable from every other vertex
//The graph can be condensed in their scc to form a DAG

struct Graph {
	vector <Long> adj[MX];
	vector <Long> rev[MX];
	bool vis1[MX];
	bool vis2[MX];
	vector<Long> order,component;
	Long numComponent = 0;
	Long scc[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			rev[i].clear();
			vis1[i] = vis2[i] = false;
		}
		order.clear();
		component.clear();
		numComponent = 0;
	}
	
	void addEdge(Long u, Long v) {
		adj[u].pb(v);
		rev[v].pb(u);
	}
	
	void dfs1(Long u){ //O(N + M)
		vis1[u] = true;
		for(Long v : adj[u]) {
			if(!vis1[v]) {
				dfs1(v);
			}
		}
		order.pb(u);
	}
	
	void dfs2(Long u) { //O(N + M)
		vis2[u] = true;
		component.pb(u);
		for(Long v : rev[u]) {
			if(!vis2[v]) {
				dfs2(v);
			}
		}
	}
	
	void calculateSCC(Long N) { //O(N + M)
		REP(i, N){
			if(!vis1[i]) dfs1(i);
		}
		REP(i , N ) {
			Long u = order[N - 1 - i];
			if(!vis2[u]) {
				dfs2(u);
				
				for(Long v : component) {
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

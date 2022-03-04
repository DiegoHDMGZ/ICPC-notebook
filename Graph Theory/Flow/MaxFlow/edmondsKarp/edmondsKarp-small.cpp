#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

//This implementation is for small graphs G(V, E) (|V| <= 3000 aprox)
//where O(|V|^2) memory will fit the memory limit.

const int MX = 3000;
const Long INF = 1e18;

struct Graph{
	vector<int> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool added[MX][MX];
	int parent[MX];
	
	void clear(int n){
		for (int i = 0; i < n; i++){
			adj[i].clear();
			for(int j = 0; j < n; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		if(!added[u][v]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			added[u][v] = added[v][u] = true;
		}
		cap[u][v] += w;
		if (!dir) cap[v][u] += w;
	}
	
	void pushFlow(int s, int t, Long inc) {
		int v = t;
		while (v != s){
			int u = parent[v];
			flow[u][v] += inc;
			flow[v][u] -= inc;
			v = u;
		}
	}
	
	Long bfs(int s, int t, int n) { //O(E)
		fill(parent, parent + n, -1);
		vector<Long> residualCap(n, 0);
		queue<int> q({s});
		parent[s] = -2;
		residualCap[s] = INF;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (u == t) {
				pushFlow(s, t, residualCap[t]);
				return residualCap[t];
			}
			for (int v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				if (parent[v] == -1 && cf > 0) {
					parent[v] = u;
					residualCap[v] = min(residualCap[u], cf);
					q.push(v);
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(int s, int t, int n) { //O(E * min(E * V , |F|))
		Long ans = 0;
		while (Long inc = bfs(s, t, n)) ans += inc;
		return ans;
	}
} G;

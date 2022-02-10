#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

//This implementation is for small graphs (n <= 3000 aprox)
//where O(n^2) memory will fit the memory limit.

const int MX = 3000;
const Long INF = 1e18;

struct Graph{
	vector<int> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool vis[MX];
	bool added[MX][MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			vis[i] = false;
			for (int j = 0; j < n; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		if (!added[u][v]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			added[u][v] = added[v][u] = true;
		}
		cap[u][v] += w;
		if (!dir) cap[v][u] += w;
	}
	
	Long dfs(int u, int t, Long f) { //O(E)
		if (u == t) return f;
		if (vis[u]) return 0;
		vis[u] = true;
		for (int v : adj[u]) {
			Long cf = cap[u][v] - flow[u][v];
			if (cf == 0) continue;
			Long ret = dfs(v, t, min(f, cf));
			if (ret > 0) {
				flow[u][v] += ret;
				flow[v][u] -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(int s, int t, int n) { //O(E |F|) = O(E * nU)
		Long ans = 0;
		while (true) { //O(|F|) iterations
			fill(vis, vis + n, false);
			Long inc = dfs(s, t, INF);
			if (inc == 0) break;
			ans += inc;
		}
		return ans;
	}
} G;

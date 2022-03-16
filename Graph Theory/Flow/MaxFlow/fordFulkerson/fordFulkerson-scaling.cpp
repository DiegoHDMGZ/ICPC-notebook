#include <bits/stdc++.h>
using namespace std;

typedef long long Cap;

const int MX = 3000;
const Cap INF = 1e18;

struct Edge {
	int to;
	Cap flow, cap;
	int rev; //index of the backward edge in the adj list
	Edge(int to, Cap cap, int rev): 
		to(to), flow(0), cap(cap), rev(rev) {}
};

struct Graph {
	vector<Edge> adj[MX]; 
	bool vis[MX];
	Cap maxCap = 0;
	Cap lowFlow;
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) adj[i].clear();
		maxCap = 0;
	}
	
	void addEdge(int u, int v, Cap w, bool dir) {
		adj[u].push_back(Edge(v, w, adj[v].size()));
		adj[v].push_back(Edge(u, dir ? 0 : w, adj[u].size() - 1));
		maxCap = max(maxCap, w);
	}
	
	Cap dfs(int u, int t, Cap f) { //O(E)
		if (u == t) return f;
		if (vis[u]) return 0;
		vis[u] = true;
		for (Edge &e : adj[u]) {
			int v = e.to;
			Edge &rev = adj[v][e.rev];
			Cap cf = e.cap - e.flow;
			if (cf < lowFlow) continue;
			Cap ret = dfs(v, t, min(f, cf));
			if (ret > 0) {
				e.flow += ret;
				rev.flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Cap maxFlow(int s, int t, int n) { //O(E^2 * log U)
		//All capacities must be integers in order to apply scaling
		if (maxCap == 0) return 0;
		int lg = 63 - __builtin_clzll(maxCap);
		Cap ans = 0;
		for (lowFlow = (1LL << lg); lowFlow >= 1; lowFlow >>= 1) {
			while (true) { //O(E) iterations
				fill(vis, vis + n, false);
				Cap inc = dfs(s, t, INF);
				if (inc == 0) break;
				ans += inc;
			}
		}
		return ans;
	}
} G;

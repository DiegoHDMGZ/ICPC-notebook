#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 3000;
const Long INF = 1e18;

struct Edge{
	int to;
	Long flow, cap;
	int rev; //index of the backward edge in the adj list
	Edge(int to, Long cap, int rev): 
		to(to), flow(0), cap(cap), rev(rev) {}
};

struct Graph{
	vector<Edge> adj[MX]; 
	bool vis[MX];
	Long maxCap = 0;
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) adj[i].clear();
		maxCap = 0;
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		maxCap = max(maxCap, w);
		adj[u].push_back(Edge(v, w, adj[v].size()));
		adj[v].push_back(Edge(u, dir ? 0 : w, adj[u].size() - 1));
	}
	
	Long dfs(int u, int t, Long f, Long lim) { //O(E)
		if (u == t) return f;
		if (vis[u]) return 0;
		vis[u] = true;
		for (Edge &e : adj[u]) {
			int v = e.to;
			Edge &rev = adj[v][e.rev];
			Long cf = e.cap - e.flow;
			if (cf < lim) continue;
			Long ret = dfs(v, t, min(f, cf), lim);
			if (ret > 0) {
				e.flow += ret;
				rev.flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(int s, int t, int n) { //O(E^2 * log U)
		if (maxCap == 0) return 0;
		int lg = 64 - __builtin_clzll(maxCap);
		Long ans = 0;
		for (Long lim = (1LL << lg); lim >= 1; lim >>= 1) {
			while (true) { //O(E) iterations
				fill(vis, vis + n, false);
				Long inc = dfs(s, t, INF, lim);
				if (inc == 0) break;
				ans += inc;
			}
		}
		return ans;
	}
} G;

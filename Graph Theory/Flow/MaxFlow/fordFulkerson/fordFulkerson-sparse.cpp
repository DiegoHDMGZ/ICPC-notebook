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
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) adj[i].clear();
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		adj[u].push_back(Edge(v, w, adj[v].size()));
		adj[v].push_back(Edge(u, dir ? 0 : w, adj[u].size() - 1));
	}
	
	Long dfs(int u, int t, Long f) { //O(E)
		if (u == t) return f;
		if (vis[u]) return 0;
		vis[u] = true;
		for (Edge &e : adj[u]) {
			int v = e.to;
			Edge &rev = adj[v][e.rev];
			Long cf = e.cap - e.flow;
			if (cf == 0) continue;
			Long ret = dfs(v, t, min(f, cf));
			if (ret > 0) {
				e.flow += ret;
				rev.flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(int s, int t, int n) { //O(E * |F|)
		//O(|F|) = O(m * U)
		//If there is no multi edge, O(|F|) = O(n * U)
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

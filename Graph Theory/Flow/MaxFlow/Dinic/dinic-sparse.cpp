#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 5000;
const Long INF = 1e18;

struct Edge{
	int to;
	Long flow, cap;
	int rev; //index of the backward edge in the adj list of to
	Edge(int to, Long cap, int rev): 
		to(to), flow(0), cap(cap), rev(rev) {}
};

struct Graph{
	vector<Edge> adj[MX];  
	int level[MX];
	int nextEdge[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) adj[i].clear();
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		adj[u].push_back(Edge(v, w, adj[v].size()));
		adj[v].push_back(Edge(u, dir ? 0 : w, adj[u].size() - 1));
	}
	
	Long dfs(int u, int t, Long f) { 
		if (u == t) return f;
		for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
			Edge &e = adj[u][i];
			int v = e.to;
			Edge &rev = adj[v][e.rev];
			Long cf = e.cap - e.flow;
			if (cf == 0 || level[v] != level[u] + 1) continue;
			Long ret = dfs(v, t, min(f, cf));
			if (ret > 0) {
				e.flow += ret;
				rev.flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	bool bfs(int s, int t, int n) { //O(E)
		fill(level, level + n, -1);
		queue<int> q({s}); 
		level[s] = 0;
		while (!q.empty()) {
			int u = q.front();
			nextEdge[u] = 0;
			q.pop();
			if (u == t) return true;
			for (Edge e : adj[u]) {
				int v = e.to;
				Long cf = e.cap - e.flow;
				if (level[v] == -1 && cf > 0) {
					level[v] = level[u] + 1;
					q.push(v);
				}
			}
		}
		return false;
	}
	
	Long maxFlow(int s, int t, int n) {
		//General: O(E * V^2), O(E * V + V * |F|)
		//Unit Cap: O(E * min(E^(1/2) , V^(2/3)))
		//Unit Network: O(E * V^(1/2))
		//In unit network, all the edges have unit capacity
		//and for any vertex except s and t either the 
		//incoming or outgoing edge is unique.
		Long ans = 0;
		while (bfs(s, t, n)) { //O(V) iterations
			//after bfs, the graph is a DAG
			while (Long inc = dfs(s, t, INF)) ans += inc;
		}
		return ans;
	}
} G;

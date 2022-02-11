#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 5000;
const Long INF = 1e18;

struct Edge{
	int from, to;
	Long flow, cap;
	int rev; //index of the backward edge in the adj list of to
	Edge(int from, int to, Long cap, int rev): 
		from(from), to(to), cap(cap), flow(0), rev(rev) {}
};


struct Graph{
	vector<Edge> adj[MX]; 
	int parentEdge[MX];
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		Edge forward(u, v, w, adj[v].size());
		Edge backward(v, u, 0, adj[u].size());
		if (!dir) backward.cap = w;
		adj[u].push_back(forward);
		adj[v].push_back(backward);
	}
	
	void pushFlow(int s, int t, Long inc) {
		int v = t;
		while (v != s) {
			Edge &backward = adj[v][parentEdge[v]];
			int u = backward.to;
			Edge &forward = adj[u][backward.rev];
			forward.flow += inc;
			backward.flow -= inc;
			v = u;
		}
	}
	
	Long bfs(int s, int t) { //O(E)
		deque<pair<int, Long>> q; //<node, flow>
		q.push_back({s, INF});
		parentEdge[s] = -2;
		while (!q.empty()) {
			int u = q.front().first;
			Long curFlow = q.front().second;
			q.pop_front();
			if (u == t) {
				pushFlow(s, t, curFlow);
				return curFlow;
			}
			for (auto e : adj[u]){
				int v = e.to;
				Long cf = e.cap - e.flow;
				if (parentEdge[v] == -1 && cf > 0) {
					parentEdge[v] = e.rev;
					Long newFlow = min(curFlow, cf);
					q.push_back({v, newFlow});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(int s, int t, int n) { //O(E * min(E * V , |F|))
		Long ans = 0;
		while (true){ //O(min(E * V, |F|)) iterations
			fill(parentEdge, parentEdge + n, -1);
			Long inc = bfs(s, t);
			if (inc == 0) break;
			ans += inc;
		}
		return ans;
	}
} G;

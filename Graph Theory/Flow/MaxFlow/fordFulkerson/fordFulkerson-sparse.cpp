#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 3000;
const Long INF = 1e18;

struct Edge{
	int to;
	Long flow, cap;
	Edge(int to, Long cap) : to(to), cap(cap), flow(0) {}
};

struct Graph{
	vector<Edge> edges;
	vector<int> adjInd[MX]; 
	//'adjInd' stores the position of the edge in the vector 'edges'
	bool vis[MX];
	
	void clear(int n) {
		edges.clear();
		for (int i = 0 ; i < n; i++) {
			adjInd[i].clear();
			vis[i] = false;
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		Edge forward(v, w);
		Edge backward(u, 0);
		adjInd[u].push_back(edges.size());
		edges.push_back(forward);
		adjInd[v].push_back(edges.size());
		edges.push_back(backward);
		if (!dir) addEdge(v, u, w, true);
	}
	
	Long dfs(int u, int t, Long f) { //O(E)
		if (u == t) return f;
		if (vis[u]) return 0;
		vis[u] = true;
		for (int ind : adjInd[u]) {
			Edge &e = edges[ind];
			Edge &rev = edges[ind ^ 1];
			int v = e.to;
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

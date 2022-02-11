#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

//Find the maximum flow that has minimum cost.
//Costs can be negative but there must be no negative cycle initially.

//This implementation is for small graphs G(V, E) (|V| <= 3000 aprox)
//where O(|V|^2) memory will fit the memory limit.
//So a 2D array can be used to speed up the algorithm a little bit.
//WARNING: No multi-edges allowed. 
//No antiparallel edges allowed i.e. No (u, v) (v, u) at the same time

const int MX = 2005;
const Long INF = 1e18;

typedef pair<Long, Long> Pair;

struct Path{
	int node;
	Long weight;
	Path(){}
	Path(int node, Long weight): node(node) , weight(weight) {}
	bool operator >(const Path &P) const{
		return weight > P.weight;
	}
};

struct Graph{
	vector<int> adj[MX];
	Long cap[MX][MX];
	Long cost[MX][MX];
	Long flow[MX][MX];
	int parent[MX];
	Long pot[MX];
	bool inQueue[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			pot[i] = 0;
			parent[i] = -1;
			for (int j = 0; j < n; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				cost[i][j] = 0;
			}
		}
	}
	
	void addEdge(int u, int v, Long w, Long c) {
		adj[u].push_back(v);
		adj[v].push_back(u);
		cap[u][v] = w;
		cost[u][v] = c;
		cost[v][u] = -c;
	}
	
	void spfa(int s, int n){ //O(E V)
		for (int i = 0; i < n; i++) pot[i] = INF;
		queue<int> q;
		pot[s] = 0;
		inQueue[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inQueue[u] = false;
			for (int v : adj[u]) {
				if (cap[u][v] - flow[u][v] > 0 && pot[u] + cost[u][v] < pot[v]){
					pot[v] = pot[u] + cost[u][v];
					if (!inQueue[v]) q.push(v);
					inQueue[v] = true;
				}
			}
		}
	}
	
	Pair dijkstra(int s, int t, int n){ //O(E log V)
		//<flow, cost>
		priority_queue<Path, vector<Path>, greater<Path>> q;
		vector<Long> d(n, INF);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		q.push(Path(s, d[s]));
		while (!q.empty()) {
			Path p = q.top();
			q.pop();
			int u = p.node;
			if (p.weight != d[u]) continue;
			for (int v : adj[u]) {
				Long cf = cap[u][v] - flow[u][v];
				Long c = cost[u][v] + pot[u] - pot[v];
				if (cf > 0 && d[u] + c < d[v]) {
					assert(c >= 0);
					d[v] = d[u] + c;
					q.push(Path(v, d[v]));
					residualCap[v] = min(residualCap[u], cf);
					parent[v] = u;
				}
			}
		}
		if(d[t] == INF) return {0, 0};
		for (int i = 0; i < n; i++) pot[i] += d[i];
		Long cf = residualCap[t];
		int cur = t;
		while (true) {
			flow[parent[cur]][cur] += cf;
			flow[cur][parent[cur]] -= cf;
			cur = parent[cur];
			if (cur == s) break;
		}
		return {cf, pot[t] * cf};
	}
	
	/*
	//For dense graph, the quadratic version can be used
	Pair dijkstra(int s, int t, int n) { //O(V^2)
		//<flow, cost>
		vector<Long> d(n , INF);
		vector<bool> vis(n , false);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		for (int i = 0; i < n; i++) {
			int u = -1;
			for (int j = 0; j < n; j++) {
				if (!vis[j] && (u == -1 || d[j] < d[u])) u = j;
			}
			if (u == -1 || d[u] == INF) break;
			vis[u] = true;
			for (int v : adj[u]) {
				Long cf = cap[u][v] - flow[u][v];
				Long c = cost[u][v] + pot[u] - pot[v];
				if (cf > 0 && d[u] + c < d[v]) {
					d[v] = d[u] + c;
					residualCap[v] = min(residualCap[u], cf);
					parent[v] = u;
				}
			}
		}
		//... (the same as the normal dijkstra here)
	}
	*/
	
	Pair minCostFlow(int s, int t, int n) { 
		//O(E log V *  maxFlow)
		//maxFlow <= V * U, where U is the maximum capacity
		//Initially no negative cycles
		//<maxFlow, minCost>
		spfa(s, n); //not necessary if there is no negative edges
		Pair inc;
		Long f = 0;
		Long c = 0;
		do {
			inc = dijkstra(s, t, n);
			f += inc.first;
			c += inc.second;
		} while (inc.first > 0);
		return {f, c};
	}
} G;

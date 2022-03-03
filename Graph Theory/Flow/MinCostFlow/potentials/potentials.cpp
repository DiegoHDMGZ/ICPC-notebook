#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

//Find the maximum flow that has minimum cost.
//Costs can be negative but there must be no negative cycle initially.

const int MX = 5000;
const Long INF = 1e18;
 
typedef pair<Long, Long> Pair;

struct Edge{
	int to;
	Long flow, cap, cost;
	int rev; //index of the backward edge in the adj list of to
	Edge(int to, Long cap, Long cost, int rev) : 
		to(to), flow(0), cap(cap), cost(cost), rev(rev){}
};
 
struct Graph{
	vector<Edge> adj[MX];
	int parentEdge[MX];
	Long pot[MX];
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) {
			adj[i].clear();
			pot[i] = 0;
		}
	}
	
	void addEdge(int u, int v, Long w, Long cost, bool dir) {
		adj[u].push_back(Edge(v, w, cost, adj[v].size()));
		adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
		if (!dir) addEdge(v, u, w, cost, true);
	}
	
	void spfa(int s, int n) { //O(E V)
		vector<bool> inQueue(n, false);
		for (int i = 0; i < n; i++) pot[i] = INF;
		queue<int> q;
		pot[s] = 0;
		inQueue[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inQueue[u] = false;
			for (Edge e : adj[u]) {
				int v = e.to;
				if (e.cap - e.flow > 0 && pot[u] + e.cost < pot[v]) {
					pot[v] = pot[u] + e.cost;
					if (!inQueue[v]) q.push(v);
					inQueue[v] = true;
				}
			}
		}
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
	
	Pair dijkstra(int s, int t, int n) { //O(E log V)
		//<flow, cost>
		typedef pair<Long, int> Path; //<weight, node>
		priority_queue<Path, vector<Path>, greater<Path>> q;
		vector<Long> d(n, INF);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		q.push(Path(d[s], s));
		while (!q.empty()) {
			Path p = q.top();
			q.pop();
			int u = p.second;
			if (p.first != d[u]) continue;
			for (Edge e : adj[u]) {
				int v = e.to;
				Long cf = e.cap - e.flow;
				Long cost = e.cost + pot[u] - pot[v];
				if (cf > 0 && d[u] + cost < d[v]) {
					d[v] = d[u] + cost;
					q.push(Path(d[v], v));
					residualCap[v] = min(residualCap[u], cf);
					parentEdge[v] = e.rev;
				}
			}
		}
		if (d[t] == INF) return {0, 0};
		for (int i = 0; i < n; i++) pot[i] += d[i];
		Long cf = residualCap[t];
		pushFlow(s, t, cf);
		return {cf, pot[t] * cf};
	}
	
	Pair minCostFlow(int s, int t, int n) {
		//O(E log V * maxFlow)
		//maxFlow <= V * U, where U is the maximum capacity
		//Assumption: Initially no negative cycles
		//<maxFlow, minCost>
		spfa(s, n); //not necessary if there is no negative edges
		Pair inc; 
		Long flow = 0;
		Long cost = 0;
		do {
			inc = dijkstra(s, t, n);
			flow += inc.first;
			cost += inc.second;
		} while(inc.first > 0);
		return {flow, cost};
	}
} G;

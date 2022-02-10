#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 5000;
const Long INF = 1e18;
 
struct Edge{
	int from, to;
	Long cap, flow, cost;
	int rev; //index of the backward edge in the adj list of to
	Edge() {}
	Edge(int from, int to, Long cap, Long cost, int rev) : 
		from(from), to(to), cap(cap), flow(0), cost(cost), rev(rev){}
};
 
struct Path{
	int node;
	Long weight;
	Path(){}
	Path(int node, Long weight) : node(node), weight(weight) {}
	bool operator >(const Path &P) const{
		return weight > P.weight;
	}
};
 
struct Graph{
	vector<Edge> adj[MX];
	int parentEdge[MX];
	Long pot[MX];
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) {
			adj[i].clear();
			parentEdge[i] = -1;
			pot[i] = 0;
		}
	}
	
	void addEdge(int u, int v, Long w, Long cost, bool dir) {
		Edge forward(u, v, w, cost, adj[v].size());
		Edge backward(v, u, 0, -cost, adj[u].size());
		adj[u].push_back(forward);
		adj[v].push_back(backward);
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
	
	pair<Long, Long> dijkstra(int s, int t, int n) { //O(E log V)
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
			for (Edge e : adj[u]) {
				int v = e.to;
				Long cf = e.cap - e.flow;
				Long cost = e.cost + pot[u] - pot[v];
				if (cf > 0 && d[u] + cost < d[v]) {
					d[v] = d[u] + cost;
					q.push(Path(v, d[v]));
					residualCap[v] = min(residualCap[u],cf);
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
	
	pair<Long, Long> minCostFlow(int s, int t, int n) {
		//O(E log V * maxFlow)
		//maxFlow <= V * U, where U is the maximum capacity
		//Initially no negative cycles
		//<maxFlow, minCost>
		spfa(s, n); //not necessary if there is no negative edges
		pair<Long, Long> inc; 
		pair<Long, Long> ans = {0, 0};
		do {
			inc = dijkstra(s, t, n);
			ans.first += inc.first;
			ans.second += inc.second;
		} while(inc.first > 0);
		return ans;
	}
} G;

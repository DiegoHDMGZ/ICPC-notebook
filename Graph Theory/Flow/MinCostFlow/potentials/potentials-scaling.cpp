#include <bits/stdc++.h>
using namespace std;

/*Find the maximum flow that has minimum cost.
This algorithm DOES work even when the initial graph has negative 
cycles*/

typedef long long Cap;
typedef long long Cost;

const int MX = 5000;
const Cap INF_CAP = 1e18;
const Cost INF_COST = 1e18;

struct Edge {
	int to;
	Cap flow, cap;
	Cost cost;
	int rev; //index of the backward edge in the adj list of to
	Edge(int to, Cap cap, Cost cost, int rev) : 
		to(to), flow(0), cap(cap), cost(cost), rev(rev){}
};
 
struct Graph {
	vector<Edge> adj[MX];
	int parentEdge[MX];
	Cost pot[MX];
	Cap maxCap = 0;
	Cap lowFlow;
	
	void clear(int n) {
		maxCap = 0;
		for (int i = 0 ; i < n; i++) {
			adj[i].clear();
			pot[i] = 0;
		}
	}
	
	void addEdge(int u, int v, Cap w, Cost cost, bool dir) {
		adj[u].push_back(Edge(v, w, cost, adj[v].size()));
		adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
		if (u == v) adj[u].end()[-2].rev++;
		maxCap = max(maxCap, w);
		if (!dir) addEdge(v, u, w, cost, true);
	}
	
	void pushFlow(int s, int t, Cap inc) {
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
	
	void updatePotentials(int s, int t, Cost tsCost, vector<Cost> &d) {
		int n = d.size();
		Cost infPot = 0;
		for (int u = 0; u < n; u++) {
			if (d[u] == INF_COST) {
				for (auto e : adj[u]) {
					int v = e.to;
					Cap cf = e.cap - e.flow;
					Cost cost = e.cost + pot[u] - pot[v];
					if (d[v] != INF_COST && cf >= lowFlow && cost >= 0) {
						infPot = max(infPot, d[v] - cost);
					}
				}
			}
		}
		if (d[t] == INF_COST) infPot = max(infPot, d[s] - tsCost);
		for (int u = 0; u < n; u++) {
			if (u == s) continue;
			if (d[u] != INF_COST) pot[u] += d[u] - pot[s];
			else pot[u] += infPot - pot[s];
		}
		pot[s] = d[s];
	}
	
	pair<Cap, Cost> dijkstra(int s, int t, int n, Cap tsCap = 0, Cost tsCost = 0) {
		//O(E log V)
		//tsCap > 0 and tsCost < 0 means we are looking for negative 
		//cycle from s to t to form a negative circulation
		typedef pair<Cost, int> Path; //<weight, node>
		priority_queue<Path, vector<Path>, greater<Path>> q;
		vector<Cost> d(n, INF_COST);
		vector<Cap> residualCap(n, 0);
		d[s] = tsCost;
		residualCap[s] = INF_CAP;
		q.push(Path(d[s], s));
		while (!q.empty()) {
			auto [dist, u] = q.top();
			q.pop();
			if (dist != d[u]) continue;
			for (Edge e : adj[u]) {
				int v = e.to;
				Cap cf = e.cap - e.flow;
				Cost cost = e.cost + pot[u] - pot[v];
				if (cf >= lowFlow && cost >= 0 && d[u] + cost < d[v]) {
					d[v] = d[u] + cost;
					q.push(Path(d[v], v));
					residualCap[v] = min(residualCap[u], cf);
					parentEdge[v] = e.rev;
				}
			}
		}
		updatePotentials(s, t, tsCost, d);
		if (d[t] == INF_COST) return {0, 0};
		if (tsCap > 0 && d[t] >= 0) return {0, 0};
		Cap cf = residualCap[t];
		if (tsCap > 0) cf = min(cf, tsCap);
		pushFlow(s, t, cf);
		if (tsCap == 0) return {cf, pot[t] * cf};
		else return {cf, d[t] * cf};
	}
	
	pair<Cap, Cost> minCostFlow(int s, int t, int n) {
		//O(E^2 * log V * log U) where U is the maximum capacity
		//<maxFlow, minCost>
		if (maxCap == 0) return {0, 0};
		int lg = 63 - __builtin_clzll(maxCap);
		pair<Cap, Cost> inc; 
		Cap totalFlow = 0;
		Cost totalCost = 0;
		for (lowFlow = (1LL << lg); lowFlow >= 1; lowFlow >>= 1) {
			//push flow through negative cycles
			for (int u = 0; u < n; u++) {
				for (auto &e : adj[u]) {
					Cap cf = e.cap - e.flow;
					int v = e.to;
					if (cf >= lowFlow && cf < 2 * lowFlow) {
						Cost cost = e.cost + pot[u] - pot[v];
						if (cost < 0) {
							inc = dijkstra(v, u, n, cf, cost);
							Edge &rev = adj[v][e.rev];
							e.flow += inc.first;
							rev.flow -= inc.first;
							totalCost += inc.second;
						}
					}
				}
			}
			//normal shortest augmenting path
			do {
				inc = dijkstra(s, t, n);
				totalFlow += inc.first;
				totalCost += inc.second;
			} while (inc.first > 0);
		}
		return {totalFlow, totalCost};
	}
} G;

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Find the maximum flow that has minimum cost.
//Costs can be negative but there must be no negative cycle initially.

const Long MX = 5000;
const Long INF = 1e18;

typedef pair<Long, Long> Pair;

struct Edge{
	int from, to;
	Long cap, flow, cost;
	int rev; //index of the backward edge in the adj list of to
	Edge() {}
	Edge(int from, int to, Long cap, Long cost, int rev) : 
		from(from), to(to), cap(cap), flow(0), cost(cost), rev(rev){}
};

struct Graph{
	vector<Edge> adj[MX];
	vector<Edge> edges;
	int parentEdge[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
		edges.clear();
	}
	
	void addEdge(int u, int v, Long w, Long cost, bool dir) {
		Edge forward(u, v, w, cost, adj[v].size());
		Edge backward(v, u, 0, -cost, adj[u].size());
		adj[u].push_back(forward);
		adj[v].push_back(backward);
		edges.push_back(forward);
		edges.push_back(backward);
		if (!dir) addEdge(v, u, w, cost, true);
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
	
	Pair spfa(int s, int t, int n) { //O(E V)
		//<flow, cost>
		vector<Long> d(n, INF);
		vector<bool> inQueue(n, false);
		vector<Long> residualCap(n, 0);
		queue<int> q;
		d[s] = 0;
		residualCap[s] = INF;
		inQueue[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inQueue[u] = false;
			for (Edge e : adj[u]) {
				int v = e.to;
				Long cf = e.cap - e.flow;
				if (cf > 0 && d[u] + e.cost < d[v]){
					d[v] = d[u] + e.cost;
					if (!inQueue[v]) q.push(v);
					parentEdge[v] = e.rev;
					residualCap[v] = min(residualCap[u], cf);
					inQueue[v] = true;
				}
			}
		}
		if (d[t] == INF) return {0, 0};
		Long cf = residualCap[t];
		pushFlow(s, t, cf);
		return {cf, d[t] * cf};
	}
	
	Pair minCostFlow(int s, int t, int n) { 
		//O(E * V * maxFlow )
		//maxFlow <= V * U, where U is the maximum capacity
		//Assumption: Initially no negative cycles
		//<maxFlow, minCost>
		Pair inc;
		Pair ans = {0, 0};
		do {
			inc = spfa(s, t, n);
			ans.first += inc.first;
			ans.second += inc.second;
		} while (inc.first > 0);
		return ans;
	}
} G;

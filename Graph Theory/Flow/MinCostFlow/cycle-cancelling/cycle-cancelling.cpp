#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
The algorithm first use Dinic to find any max flow. Then, it finds 
the minimum circulation finding negative cycles in the residual graph.

This algorithm DOES work even when the initial graph has negative 
cycles.
*/

const Long MX = 5000;
const Long INF = 1e18;

typedef pair<Long, Long> Pair;

struct Edge{
	int to;
	Long flow, cap, cost;
	int rev; //index of the backward edge in the adj list of to
	Edge() {}
	Edge(int to, Long cap, Long cost, int rev) : 
		to(to), flow(0), cap(cap), cost(cost), rev(rev){}
};
 
struct Graph{
	vector<Edge> adj[MX];
	int level[MX];
	int nextEdge[MX];
	int parentEdge[MX];
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) adj[i].clear();
	}
	
	void addEdge(int u, int v, Long w, Long cost, bool dir) {
		adj[u].push_back(Edge(v, w, cost, adj[v].size()));
		adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
		if (u == v) adj[u].end()[-2].rev++;
		if (!dir && u != v) addEdge(v, u, w, cost, true);
	}
	
	//******** Dinic's Algorithm ********
	Pair dfs(int u, int t, Long f) { 
		//<flow, sumCost>
		if (u == t) return {f , 0};
		for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
			Edge &e = adj[u][i];
			int v = e.to;
			Edge &rev = adj[v][e.rev];
			Long cf = e.cap - e.flow;
			if (cf == 0 || level[v] != level[u] + 1) continue;
			Pair ans = dfs(v, t, min(f, cf));
			Long flow = ans.first;
			Long sumCost = ans.second;
			if (flow > 0) {
				e.flow += flow;
				rev.flow -= flow;
				Long cost = e.cost * flow;
				return {flow , cost + sumCost};
			}
		}
		return {0, 0};
	}
	
	bool bfs(int s, int t, int n){ //O(E)
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
	
	Pair maxFlow(int s, int t, int n){
		Long flow = 0;
		Long cost = 0;
		while (bfs(s, t, n)) { //O(V) iterations
			//after bfs, the graph is a DAG
			Pair inc;
			do {
				inc = dfs(s, t, INF);
				flow += inc.first;
				cost += inc.second;
			} while (inc.first > 0);
		}
		return {flow, cost};
	}
	//******** End Dinic's Algorithm ******** 
	
	Long costCycle(int v, int n) {
		//go back n times to find a cycle
		for (int i = 0; i < n; i++) v = adj[v][parentEdge[v]].to;
		Long cf = INF;
		int start = v;
		do {
			Edge backward = adj[v][parentEdge[v]];
			int u = backward.to;
			Edge forward = adj[u][backward.rev];
			cf = min(cf, forward.cap - forward.flow);
			v = u;
		} while (v != start);
		start = v;
		Long cost = 0;
		do {
			Edge &backward = adj[v][parentEdge[v]];
			int u = backward.to;
			Edge &forward = adj[u][backward.rev];
			cost += cf * forward.cost;
			forward.flow += cf;
			backward.flow -= cf;
			v = u;
		} while (v != start);
		return cost;
	}
	
	Long spfa(int n) { //O(E V)
		vector<Long> d(n, 0);
		queue<int> q;
		vector<bool> inQueue(n, true);
		for (int u = 0; u < n; u++) q.push(u);
		int phase = 0;
		while (!q.empty() && phase < n) {
			int sz = q.size();
			REP(i, sz) {
				int u = q.front();
				q.pop();
				inQueue[u] = false;
				for (Edge e : adj[u]) {
					int v = e.to;
					Long cf = e.cap - e.flow;
					Long w = e.cost;
					if (cf > 0 && d[u] + w < d[v]) {
						d[v] = d[u] + w;
						parentEdge[v] = e.rev;
						if (!inQueue[v]) {
							q.push(v);
							inQueue[v] = true;
						}
					}
				}
			}
			phase++;
		}
		if (!q.empty()) return costCycle(q.front(), n);
		// no negative cycle
		return 0;
	}
	
	Pair minCostFlow(int s, int t, int n) { 
		//O(dinic + EV * |totalCost|)
		//|totalCost| <= E * U * C, where U is max cap and C max cost
		//<maxFlow, minCost>
		Pair ans = maxFlow(s, t, n);
		Long flow = ans.first;
		Long cost = ans.second;
		Long inc;
		do {
			inc = spfa(n);
			cost += inc;
		} while(inc < 0);
		return {flow, cost};
	}
} G;

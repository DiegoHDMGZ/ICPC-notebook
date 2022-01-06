#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 5000;
const Long INF = 1e18;
 
struct Edge{
	Long from, to, cap, flow, cost;
	Edge() {}
	Edge(Long from, Long to, Long cap, Long cost) : 
		from(from), to(to), cap(cap), flow(0), cost(cost){}
};
 
struct Path{
	Long node, weight;
	Path(){}
	Path(Long node, Long weight) : node(node), weight(weight) {}
	bool operator >(const Path &P) const{
		return weight > P.weight;
	}
};
 
struct Graph{
	vector<Edge> adj[MX];
	vector<int> indRev[MX];
	int parent[MX];
	int parentInd[MX];
	Long pot[MX];
	bool inQueue[MX];
	
	void clear(int n){
		for (int i = 0 ; i < n; i++) {
			adj[i].clear();
			indRev[i].clear();
			parent[i] = parentInd[i] = -1;
			pot[i] = 0;
		}
	}
	
	void addEdge(Long u, Long v, Long w, Long cost, bool dir) {
		Edge forward(u, v, w, cost);
		Edge backward(v, u, 0, -cost);
		indRev[u].push_back(adj[v].size());
		indRev[v].push_back(adj[u].size());
		adj[u].push_back(forward);
		adj[v].push_back(backward);
	
		if (!dir) {
			indRev[u].push_back(adj[v].size());
			indRev[v].push_back(adj[u].size());
			adj[v].push_back(forward);
			adj[u].push_back(backward);
		}
	}
	
	void spfa(int s, int n) { //O(E V)
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
					if (!inQueue[v]) {
						q.push(v);
					}
					inQueue[v] = true;
				}
			}
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
			for (int i = 0; i < adj[u].size(); i++) {
				Edge e = adj[u][i];
				int v = e.to;
				Long cf = e.cap - e.flow;
				Long cost = e.cost + pot[u] - pot[v];
				if (cf > 0 && d[u] + cost < d[v]) {
					d[v] = d[u] + cost;
					q.push(Path(v, d[v]));
					residualCap[v] = min(residualCap[u],cf);
					parent[v] = u;
					parentInd[v] = i;
				}
			}
		}
		if (d[t] == INF) return {0, 0};
		for (int i = 0; i < n; i++) pot[i] += d[i];
		Long cf = residualCap[t];
		int cur = t;
		while (true) {
			int p = parent[cur];
			int indP = parentInd[cur];
			adj[p][indP].flow += cf;
			int to = adj[p][indP].to;
			int indTo = indRev[p][indP];
			adj[to][indTo].flow -= cf;
			cur = adj[p][indP].from;
			if (cur == s) break;
		}
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

int main() {
	return 0;
}

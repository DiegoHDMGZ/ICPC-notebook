#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
const int MX = 2005;
const Long INF = 1e18;

struct Path{
	Long node, weight;
	Path(){}
	
	Path(Long node,Long weight) : 
		node(node) , weight(weight) {}

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
		for (int i = 0 ; i < n; i++) {
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
	
	void addEdge(int u, int v, Long w, Long c){
		adj[u].push_back(v);
		adj[v].push_back(u);
		cap[u][v] = w;
		cost[u][v] = c;
		cost[v][u] = -c;
	}
	
	void spfa(int s , int n){ //O(E V)
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
	
	
	pair<Long, Long> dijkstra(int s, int t, int n){ //O(E log V)
		//<flow, cost>
		priority_queue<Path , vector<Path> , greater<Path>> q;
		vector<Long> d(n , INF);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		q.push(Path(s , d[s]));
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
					q.push(Path(v , d[v]));
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
	
	
	pair<Long, Long> minCostFlow(int s, int t, int n) { 
		//O(E log V *  maxFlow)
		//maxFlow <= V * U, where U is the maximum capacity
		//Initially no negative cycles
		//<maxFlow, minCost>
		spfa(s , n); //not necessary if there is no negative edges
		pair<Long, Long> inc;
		pair<Long, Long> ans = {0, 0};
		do {
			inc = dijkstra(s, t , n);
			ans.first += inc.first;
			ans.second += inc.second;
		} while (inc.first > 0);
		return ans;
	}
} G;

int main() {
	return 0;
}

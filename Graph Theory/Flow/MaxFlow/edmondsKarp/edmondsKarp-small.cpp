#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 3000;
const Long INF = 1e18;

struct Graph{
	vector<int> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool added[MX][MX];
	int parent[MX];
	
	void clear(int n){
		for (int i = 0 ; i < n; i++){
			adj[i].clear();
			parent[i] = -1;
			for(int j = 0; j < n; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		if(!added[u][v]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			added[u][v] = added[v][u] = true;
		}
		cap[u][v] += w;
		if (!dir) cap[v][u] += w;
	}
	
	void pushFlow(int s, int t, Long inc) {
		int v = t;
		while (v != s){
			int u = parent[v];
			flow[u][v] += inc;
			flow[v][u] -= inc;
			v = u;
		}
	}
	
	Long bfs(int s, int t) { //O(E)
		deque<pair<int, Long>> q; //<node, flow>
		q.push_back({s, INF});
		parent[s] = s;
		while (!q.empty()) {
			int u = q.front().first;
			Long curFlow = q.front().second;
			q.pop_front();
			if (u == t) {
				pushFlow(s, t, curFlow);
				return curFlow;
			}
			for (int v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				if (parent[v] == -1 && cf > 0) {
					parent[v] = u;
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
			fill(parent, parent + n, -1);
			Long inc = bfs(s, t);
			if (inc == 0) break;
			ans += inc;
		}
		return ans;
	}
} G;

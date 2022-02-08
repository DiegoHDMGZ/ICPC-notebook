#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 3000;
const Long INF = 1e18;

struct Graph{
	vector<int> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool added[MX][MX];
	int level[MX];
	int nextEdge[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			for (int j = 0; j < n; j++) {
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
	
	Long dfs(int u, int t ,Long f) { //O(E)
		if(u == t) return f;
		for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
			int v = adj[u][i];
			Long cf = cap[u][v] - flow[u][v];
			if(cf == 0 || level[v] != level[u] + 1) continue;
			Long ret = dfs(v, t, min(f, cf));
			if (ret > 0) {
				flow[u][v] += ret;
				flow[v][u] -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	bool bfs(int s, int t) { //O(E)
		deque<int> q; 
		q.push_back(s);
		level[s] = 0;
		while(!q.empty()){
			int u = q.front();
			q.pop_front();
			for (int v : adj[u]) {
				Long cf = cap[u][v] - flow[u][v];
				if (level[v] == -1 && cf > 0) {
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	Long maxFlow(int s, int t, int n) {
		//General: O(E * V^2)
		//Unit Cap: O(E * min(E^(1/2) , V^(2/3)))
		//Unit Network: O(E * V^(1/2))
		//In unit network, all the edges have unit capacity
		//and for any vertex except s and t either the 
		//incoming or outgoing edge is unique.
		Long ans = 0;
		while (true) { //O(V) iterations
			fill(level, level + n, -1);
			if (!bfs(s, t)) break;
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n, 0);
			Long inc;
			do{
				inc = dfs(s, t, INF);
				ans += inc;
			} while (inc > 0);
		}
		return ans;
	}
} G;

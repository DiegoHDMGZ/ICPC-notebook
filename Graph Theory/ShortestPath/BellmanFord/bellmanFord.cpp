#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
const Long MX = 1e4;
const Long INF = 1e18;

struct Graph{
	vector<pair<Long,Long>> adj[MX];
	Long d[MX];
	Long parent[MX];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}

	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back({v, w});
	}
	
	void dfs(Long u) {
		d[u] = -INF;
		for (auto e : adj[u]) {
			Long v = e.first;
			if (d[v] != -INF) {
				dfs(v);
			}
		}
	}
	
	bool bellmanFord(Long s , Long n){ //O(VE)
		//true : negative cycle found
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			parent[i] = -1;
		}
		d[s] = 0;
		vector<bool> cycle(n, false);
		bool tense;
		for (Long i = 0; i < n; i++) {
			tense = false;
			for (Long u = 0; u < n; u++) {
				for (auto e : adj[u]) {
					Long v = e.first;
					Long w = e.second;
					if (d[u] != INF && d[u] + w < d[v]) { //tense
						d[v] = d[u] + w; //relax
						parent[v] = u;
						tense = true;
						if (i == n - 1) {
							cycle[v] = true;
						}
					}
				}
			}
			if(!tense) {
				break;
			}
		}
		for (int u = 0; u < n; u++) {
			if (cycle[u] && d[u] != -INF) {
				dfs(u);
			}
		}
		return tense;
	}
	
	vector<Long> getNegativeCycle(Long u, Long n){
		//go back n times to find a cycle
		assert(d[u] == -INF);
		for (int i = 0; i < n; i++) {
			u = parent[u]; 
		}
		vector<Long> cycle = {u};
		u = parent[u];
		while (u != cycle[0]) {
			cycle.push_back(u);
			u = parent[u];
		}
		return cycle;
	}
	
	vector<Long> getPath(Long u){
		if (d[u] == INF) {
			return {};
		}
		vector<Long> path;
		while(u != -1){
			path.push_back(u);
			u = parent[u];
		}
		reverse(path.begin(), path.end());
		return path;
	}
} G;

int main() {
	return 0;
}

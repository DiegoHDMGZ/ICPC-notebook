#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e4;
const Long INF = 1e18;

struct Graph{
	vector<pair<Long ,Long>> adj[MX];
	Long d[MX];
	int parent[MX];
	int reachedBy[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(int u, int v, Long w) {
		adj[u].push_back({v, w});
	}
	
	void dfs(int u, int root) {
		d[u] = -INF;
		reachedBy[u] = root;
		for (auto e : adj[u]) {
			int v = e.first;
			if (d[v] != -INF) {
				dfs(v, root);
			}
		}
	}
	
	bool spfa(int s, int n){ //O(VE)
		for(int i = 0; i < n; i++){
			d[i] = INF;
			parent[i] = -1;
		}
		queue<int> q;
		vector<bool> inQueue(n , false);
		vector<bool> cycle(n, false);
		d[s] = 0;
		inQueue[s] = true;
		q.push(s);
		int phase = 0;
		while(!q.empty() && phase < n){
			int sz = q.size();
			REP(i, sz) {
				int u = q.front();
				q.pop();
				inQueue[u] = false;
				for(auto e : adj[u]){
					int v = e.first;
					Long w = e.second;
					if(d[u] + w < d[v]){
						d[v] = d[u] + w;
						parent[v] = u;
						if(!inQueue[v]){
							q.push(v);
							inQueue[v] = true;
						}
						if (phase == n - 1) {
							cycle[v] = true;
						}
					}
				}
			}
			phase++;
		}
		if (phase < n) {
			return false;
		}
		for (int u = 0; u < n; u++) {
			if (cycle[u] && d[u] != -INF) {
				dfs(u, u);
			}
		}
		return true;
	}
	
	vector<Long> getNegativeCycle(Long u, Long n){
		assert(d[u] == -INF);
		u = reachedBy[u];
		//go back n times to find a cycle
		for (int i = 0; i < n; i++) {
			u = parent[u]; 
		}
		vector<Long> cycle = {u};
		u = parent[u];
		while (u != cycle[0]) {
			cycle.push_back(u);
			u = parent[u];
		}
		cycle.push_back(cycle[0]);
		reverse(cycle.begin(), cycle.end()); //directed cycle
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

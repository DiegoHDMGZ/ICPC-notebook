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
	
	bool spfa(Long s, Long n){ //O(VE)
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			parent[i] = -1;
		}
		queue<Long> q;
		vector<bool> inQueue(n , false);
		vector<Long> cnt(n, 0);
		d[s] = 0;
		inQueue[s] = true;
		q.push(s);
		bool negativeCycle = false;
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			cnt[u]++;
			if(cnt[u] >= n){
				negativeCycle = true;
				break;
			}
			for(auto e : adj[u]){
				Long v = e.first;
				Long w = e.second;
				if(d[u] + w < d[v]){
					d[v] = d[u] + w;
					parent[v] = u;
					if(!inQueue[v]){
						q.push(v);
						inQueue[v] = true;
					}
				}
			}
		}
		if (!negativeCycle) {
			return false;
		}
		vector<bool> cycle(n , false);
		for (int u = 0; u < n; u++) {
			for (auto e : adj[u]) {
				Long v = e.first;
				Long w = e.second;
				if (d[u] != INF && d[u] + w < d[v]) {
					cycle[v] = true;
				}
			}
		}
		for (int u = 0; u < n; u++) {
			if (cycle[u] && d[u] != -INF) {
				dfs(u);
			}
		}
		return true;
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

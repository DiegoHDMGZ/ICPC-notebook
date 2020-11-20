#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

typedef pair<Long, Long> Path;
const Long MX = 1e5;
const Long INF = 1e18;

struct Graph{
	vector<pair<Long,Long>> adj[MX];
	Long parent[MX];
	Long d[MX];
	Long reachedBy[MX];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back({v , w});
		adj[v].push_back({u , w}); 
	}
	
	Long dijkstra(vector<Long> &root, Long n){ //O(E log V)
		//return the minimum distance between nodes in root set
		for(Long i = 0; i < n; i++){
			parent[i] = -1;
			d[i] = INF;
			reachedBy[i] = -1;
		}
		priority_queue<Path, vector<Path> , greater<Path>> q;
		for (Long s : root) {
			d[s] = 0;
			q.push(Path(d[s], s));
			reachedBy[s] = s;
		}
		
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			Long u = p.second;
			Long weight = p.first;
			if (weight != d[u]) {
				continue;
			}
			for(auto e : adj[u]){
				Long v = e.first;
				Long w = e.second;
				if(d[u] + w < d[v]){
					d[v] = d[u] + w;
					parent[v] = u;
					reachedBy[v] = reachedBy[u];
					q.push({d[v], v});
				}
			}
		}
		Long minDist = INF;
		for (int u = 0; u < n; u++) {
			if (reachedBy[u] == -1) {
				continue;
			}
			for (auto e : adj[u]) {
				Long v = e.first;
				Long w = e.second;
				if (reachedBy[v] == -1) {
					continue;
				}
				if (reachedBy[u] != reachedBy[v]) {
					minDist = min(minDist, d[u] + d[v] + w);
				} 
			}
		}
		return minDist;
	}
} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	return 0;
}

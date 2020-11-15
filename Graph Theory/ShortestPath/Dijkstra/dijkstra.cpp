#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Path;
const Long MX = 1e5;
const Long INF = 1e18;

struct Graph{
	vector<pair<Long,Long>> adj[MX];
	Long parent[MX];
	Long d[MX];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back({v , w});
		adj[v].push_back({u , w}); 
	}
	
	void dijkstra(Long s, Long n){ //O(E log V)
		for(Long i = 0; i < n; i++){
			parent[i] = -1;
			d[i] = INF;
		}
		priority_queue<Path, vector<Path> , greater<Path>> q;
		d[s] = 0;
		q.push({d[s], s});
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
					q.push({d[v], v});
				}
			}
		}
	}
	
	vector<Long> retrievePath(Long v){
		if(parent[v] == -1){
			return {};
		}
		vector<Long> path;
		while(v != -1){
			path.push_back(v);
			v = parent[v];
		}
		reverse(path.begin(), path.end());
		return path;
	}
} G;

int main() {
	return 0;
}

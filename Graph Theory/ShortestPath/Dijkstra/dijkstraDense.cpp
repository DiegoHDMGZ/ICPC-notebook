#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e5;
const Long INF = 1e18;

struct Graph{
	vector<pair<Long, Long>> adj[MX];
	bool vis[MX];
	Long d[MX];
	Long parent[MX];
	
	void clear(Long n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back({v , w});
		adj[v].push_back({u , w});
	}
	
	void dijkstra(Long s, Long n){ //O(V^2)
		for(Long i = 0; i < n; i++){
			vis[i] = false;
			parent[i] = -1;
			d[i] = INF;
		}
		d[s] = 0;
		for(Long i = 0; i < n; i++){
			Long u = -1;
			for(Long j = 0; j < n; j++){
				if(!vis[j] && (u == -1 || d[j] < d[u])){
					u = j;
				}
			}
			if(u == -1 || d[u] == INF){
				break;
			}
			vis[u] = true;
			for(auto e : adj[u]){
				Long v = e.first;
				Long w = e.second;
				if(d[u] + w < d[v]){
					d[v] = d[u] + w;
					parent[v] = u;
				}
			}
		}
	}
	
	deque<Long> retrievePath(Long v){
		if(parent[v] == -1){
			return {};
		}
		deque<Long> path;
		while(v != -1){
			path.push_front(v);
			v = parent[v];
		}
		return path;
	}
} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n , m;
	cin >> n >> m;
	G.clear(n);
	REP( i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		G.addEdge(u - 1 , v - 1 , w);
	}
	G.dijkstra(0, n);

	deque<Long> path = G.retrievePath(n - 1);
	if(path.empty()){
		cout << -1 << endl;
	} else {
		for(Long u : path){
			cout << u + 1 << " ";
		}
		cout << endl;
	}
	return 0;
}

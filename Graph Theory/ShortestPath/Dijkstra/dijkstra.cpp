#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e5;
const Long INF = 1e18;

struct Path{
	Long node, weight;
	Path(){
	}
	
	Path(Long node,Long weight) : node(node) , weight(weight) {}

	bool operator <(const Path &P) const{
		if(weight == P.weight){
			return node > P.node;
		}
		return weight > P.weight;
	}
};

struct Graph{
	vector<Path> adj[MX];
	bool vis[MX];
	Long d[MX];
	Long parent[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			d[i] = INF;
			parent[i] = -1;
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].pb(Path(v , w) );
		adj[v].pb(Path(u , w));
	}
	
	void dijkstra(Long root, Long N){ //O(nlogm + mlogn)
		priority_queue<Path> q;
		REP(i , N){
			d[i] = INF;
			vis[i] = false;
			parent[i] = -1;
		}

		d[root] = 0;
	
		q.push(Path(root , d[root]));
		
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			int u = p.node;
			if(vis[u]){
				continue;
			}
			if(p.weight != d[u]){
				continue;
			}
	
			vis[u] = true;
			for( Long i = 0; i < adj[u].size(); i++){
				Path x = adj[u][i];
				Long v = x.node;
				if(vis[v]){
					continue;
				}
				
				if(d[u] + x.weight < d[v]){
					d[v] = d[u] + x.weight;
					q.push(Path(v , d[v]));
					parent[v] = u;
				}
			}
		}
	}
} G;

int main() {
	Long n , m;
	cin >> n >> m;
	G.clear(n);
	REP( i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		G.addEdge(u , v , w);
	}
	G.dijkstra(0, n);
	REP(i , n){
		cout << G.d[i] << endl;
	}
	return 0;
}

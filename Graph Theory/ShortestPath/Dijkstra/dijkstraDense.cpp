#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e5;
const Long INF = 1e18;

struct Endpoint{
	Long node, weight;
	Endpoint(){}
	
	Endpoint(Long node, Long weight) : node(node) , weight(weight) {}

	bool operator >(const Endpoint &P) const{
		if(weight == P.weight){
			return node > P.node;
		}
		return weight > P.weight;
	}
};

struct Graph{
	vector<Endpoint> adj[MX];
	bool vis[MX];
	Long d[MX];
	Long parent[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].pb(Endpoint(v , w) );
		adj[v].pb(Endpoint(u , w));
	}
	
	void dijkstra(Long root, Long n){ //O(n^2)
		for(Long i = 0; i < n; i++){
			vis[i] = false;
			parent[i] = -1;
			d[i] = INF;
		}
		
		d[root] = 0;
		
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
			for(Endpoint e : adj[u]){
				Long v = e.node;
				if(vis[v]){
					continue;
				}
				if(d[u] + e.weight < d[v]){
					d[v] = d[u] + e.weight;
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

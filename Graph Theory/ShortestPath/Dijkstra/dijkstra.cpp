#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MAX = 1e5;
const Long INF = 1e18;

struct Path{
	Long nodo,cost;
	Path(){
	}
	
	Path(Long n,Long p){
		nodo = n;
		cost = p;
	}
	bool operator <(const Path &P) const{
		return cost > P.cost;
	}
};

struct Graph{
	vector<Long> adj[MAX];
	vector<Long> cost[MAX];	
	bool vis[MAX];
	Long d[MAX];
	Long padre[MAX];
	
	void clear(Long N = MAX) {
		REP( i , N) {
			adj[i].clear();
			cost[i].clear();
			vis[i] = false;
			d[i] = INF;
			padre[i] = -1;
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
		cost[u].pb(w);
		cost[v].pb(w);
	}
	
	void dijkstra(Long root, Long N){ //O(nlogm + mlogn)
		priority_queue<Path> q;
		REP(i , N){
			d[i] = INF;
		}
		Path inicio;
		inicio.nodo = root;
		inicio.cost = 0;
		d[root] = 0;
	
		q.push(inicio);
		
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			int u = p.nodo;
			if(vis[u]){
				continue;
			}
			if(p.cost != d[u]){
				continue;
			}
	
			vis[u] = true;
			Long i = 0;
			for( Long v : adj[u]){
				if(vis[v]){
					i++;
					continue;
				}
				
				if(d[u]+cost[u][i] < d[v]){
					d[v] = d[u]+cost[u][i];
					padre[v] = u;
					Path nuevoPath(v,d[v]);
					q.push(nuevoPath);
				}
				i++;
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

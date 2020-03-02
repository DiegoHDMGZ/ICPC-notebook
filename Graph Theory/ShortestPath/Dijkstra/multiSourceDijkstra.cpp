#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 3e5;

struct EndPoint{
	Long node, w;
	EndPoint(){}
	EndPoint(Long node, Long w) : node(node), w(w) {}
};

 
struct Path{
	Long node, weight, ini;
	Path(){}
	Path(Long node , Long weight, Long ini) : node(node), weight(weight) , ini(ini){}
	bool operator > (const Path &P) const{
		if(weight == P.weight){
			return node > P.node;
		}
		return weight > P.weight;
	}
};
 
const Long INF = 1e18;

struct Graph2{
	vector<EndPoint> adj[MX];
	void addEdge(Long u , Long v , Long w){
		adj[u].pb(EndPoint(v , w));
		adj[v].pb(EndPoint(u , w));
	}
}G2;
 
struct Graph{
	vector<Path> adj[MX];
	bool vis[MX];
	Long reachedBy[MX];
	Long d[MX];
	
 
	void clear(Long n = MX){
		REP(i , n){
			adj[i].clear();
		}
	}
	
	Graph(){
		clear();
	}
	
	void addEdge(Long u, Long v, Long w ){
		adj[u].pb(Path(v, w, -1));
		adj[v].pb(Path(u, w, -1));
	}
	
	void dijkstra(vector<Long> &root, Long n ){
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			vis[i] = false;
			reachedBy[i] = -1;
		}
		priority_queue<Path, vector<Path>, greater<Path>> q;

		for(Long u  : root){
			d[u] = 0;
			reachedBy[u] = u;
			q.push(Path(u, d[u] , u));
		}
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			Long u = p.node;
			if(vis[u]) {
				continue;
			}
			
			vis[u] = true;
			for(Path x : adj[u]){
				Long v = x.node;
				if(p.ini != reachedBy[v] && reachedBy[v] != -1){
					G2.addEdge(reachedBy[v] , p.ini , x.weight + d[v] + p.weight);
				}
				if(vis[v]) {
					continue;
				}
				if(d[u] + x.weight < d[v]){
					d[v] = d[u] + x.weight;
					q.push(Path(v , d[v] , p.ini));
					reachedBy[v] = p.ini;
				} 
			}
		}
		
	}
}G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

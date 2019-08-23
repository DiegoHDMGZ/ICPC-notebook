#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e5;
const Long INF = 1e18;

//https://codeforces.com/contest/20/problem/C

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
	Long parent[MX];
	Long d[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			d[i] = INF;
			parent[i] = -1;
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		u--;
		v--;
		adj[u].pb(Path(v , w) );
		adj[v].pb(Path(u , w));
	}
	
	void dijkstra(Long root, Long N){ //O(nlogm + mlogn)
		priority_queue<Path> q;
		REP(i , N){
			d[i] = INF;
			vis[i] = false;
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
	
	void retrievePath(Long v){
		if(parent[v] == -1){
			cout << -1 << endl;
			return;
		}
		deque<Long> q;
		while(v != -1){
			q.push_front(v);
			v = parent[v];
		}
		REP(i , q.size()){
			cout << q[i] + 1 << " ";
		}
		cout << endl;
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
		G.addEdge(u , v , w);
	}
	G.dijkstra(0, n);

	G.retrievePath(n - 1);
	return 0;
}

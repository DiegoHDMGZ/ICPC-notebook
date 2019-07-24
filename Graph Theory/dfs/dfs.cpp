#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;
const Long MAX = 1e5;

struct Graph {
	vector <Long> adj[MAX];
	bool vis[MAX];
	Long comp[MAX];
	Long p[MAX];
	bool ciclo = false;
	
	void clear(Long N = MAX) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			p[i] = -1;
		}
	}
	
	void addEdge(Long u, Long v) {
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void dfs(Long u, Long curComp){
		vis[u] = true;
		comp[u] = curComp;
		
		for(Long v : adj[u]){
			if(!vis[v]){
				dfs(v, curComp);
				p[v] = u; //padre de v es u;
			}
			else{
				if( v != p[u]){
					ciclo = true; //ancestro ya visitado (back edge)
				}
			} 
		}
	}
} G;

int main() {
	return 0;
}



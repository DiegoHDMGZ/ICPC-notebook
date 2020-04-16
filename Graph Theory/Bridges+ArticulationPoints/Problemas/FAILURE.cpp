#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

struct Edge{
	int u, v;
	Edge(int u , int v) : u(min(u , v)) , v(max(u,v)){
	}
	Edge(){
	}
	
	bool operator == (const Edge &E) const {
		return E.u == u && E.v == v;
	}
	
	bool operator != (const Edge &E) const {
		return !(E == *this);
	}
};

const int MX = 1e5;

const Long INF = 1e18;



struct Graph{
	vector <Long> adj[MX];
	bool vis[MX];
	Long tIn[MX];//tiempo de entrada al nodo
	Long low[MX];//minimo tiempo al que puede ir ese nodo o uno de sus descendientes por medio de cualquier arista(tree o back edge) 
	Long timer = 0;
	Long isArticulation[MX];
	bool ciclo = false;
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			tIn[i] = 0;
			low[i] = 0;
			isArticulation[i] = 0;
		}
		timer = 0;
	}
	
	void addEdge(Long u, Long v) {
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void dfs(Long u, Long p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		Long children = 0;
		for(Long v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
				ciclo = true;
			} else {
				dfs(v , u);
				low[u] = min(low[u] , low[v]);
				if(low[v] >= tIn[u] && p != -1) {
					isArticulation[u]++;
				}
				children++;
				if(p == -1 && children > 1){
					isArticulation[u]++;
				}
			}	
		}
		
	}
	
	Long buildBicomponents(Long n, Long m){
		Long ans = INF;
		ciclo = false;
		Long cnt = 0;
		for(Long i = 0; i < n; i++){
			if(!vis[i]){
				dfs(i);
				cnt++;
			}
		}
		if(!ciclo){
			return -1;
		}
		for(Long u = 0; u < n; u++){
			if(m - (Long)adj[u].size()== n - cnt - isArticulation[u] - 1){
				ans = min(ans , u + 1);
			}		
		}
		
		if(ans == INF) ans = -1;
		return ans;
	}
	
} G;

void solve(){
	Long n , m;
	cin >> n >> m;
	G.clear(n);
	REP(i , m){
		Long u , v;
		cin >> u >> v;
		u--;
		v--;
		G.addEdge(u , v);
	}
	
	cout << G.buildBicomponents(n, m) << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t, T) solve();

	return 0;
}

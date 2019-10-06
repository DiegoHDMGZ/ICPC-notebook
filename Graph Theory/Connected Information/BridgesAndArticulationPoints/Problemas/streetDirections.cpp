#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 4e5;  

struct Edge{
	Long u, v;
	Edge(Long u , Long v) : u(u) , v(v){
	}
	Edge(){
	}
};

struct Graph {
	vector <Long> adj[MX];
	bool vis[MX];
	Long tIn[MX];//tiempo de entrada al nodo
	Long low[MX];//minimo tiempo al que puede ir ese nodo o uno de sus descendientes por medio de cualquier arista(tree o back edge) 
	Long timer = 0;
	vector<Edge> bridge;
	vector<Long> articulation;
	bool isArticulation[MX];
	map<Long,bool> isBridge[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			isArticulation[i] = false;
			isBridge[i].clear();
		}
		bridge.clear();
		articulation.clear();
		timer = 0;
	}
	
	void addEdge(Long u, Long v) {
		u--;
		v--;
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
			} else {
				dfs(v , u);
				low[u] = min(low[u] , low[v]);
				if(low[v] > tIn[u]) {
					bridge.pb(Edge(u , v));
					isBridge[min(u,v)][max(u,v)] = true;
				}
				if(low[v] >= tIn[u] && p != -1 && !isArticulation[u]) {
					articulation.pb(u);
					isArticulation[u] = true;
				}
				children++;
				if(p == -1 && children > 1){
					if(!isArticulation[u]){
						isArticulation[u] = true;
						articulation.push_back(u);
					}
				}
			}
		}
	}
	
	void calculate(Long n) { //O(N + M)
		for(Long i = 0; i < n; i++) {
			if(!vis[i]) {
				dfs(i);
			}
		}
	}
} G;

bool vis[MX];

vector<pair<Long,Long> > ans;

map<Long , bool> processed[MX];
void dfs(Long u ){
	vis[u] = true;
	for(Long v : G.adj[u]){
		if(processed[min(u , v)][max(u , v)]) continue;
		processed[min(u , v)][max(u , v)] = true;
		if(!vis[v]){
			if(G.isBridge[min(u , v)][max(u , v)]){
				ans.pb({u + 1 , v + 1});
				ans.pb({v + 1 , u + 1});
			} else {
				ans.pb({u + 1, v + 1});
				dfs(v );
			}
		} else {
			ans.pb({u + 1, v + 1});
		}
		
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	Long T = 1;
	while(!(n == 0 && m == 0)){
		G.clear(n);
		ans.clear();
		REP(i , n){
			vis[i] = false;
			processed[i].clear();
		}
		REP(i , m){
			Long u , v;
			cin >> u >> v;
			G.addEdge(u , v);
		}
		G.calculate(n);
		REP(i  , n ){
			if(!vis[i]) dfs(i);
		}
		cout << T++ << "\n\n";
		REP(i , ans.size()){
			cout << ans[i].first << " " << ans[i].second << "\n";
		}
		cout << "#\n";
		cin >> n >> m;
	}
	
	return 0;
}

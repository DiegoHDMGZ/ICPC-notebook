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
	Long component[MX];
	
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
	
	void dfs(Long u, Long c , Long p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		Long children = 0;
		component[u] = c;
		for(Long v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
			} else {
				dfs(v , c , u);
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
		Long T = 1;
		for(Long i = 0; i < n; i++) {
			if(!vis[i]) {
				dfs(i, T++ );
			}
		}
	}
} G1 , G2;



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long N, M, Q;
	cin >> N >> M >> Q;
	while(!(N == 0 && M == 0 && Q == 0)){
		G1.clear(N);
		G2.clear(N);
		vector<pair<Long,Long> > edges;
		REP(i , M){
			Long u , v;
			cin >> u >> v;
			G1.addEdge(u , v);
			edges.pb({u - 1 , v - 1});
		}
		G1.calculate(N);
		
		REP(i , M){
			if(G1.isBridge[edges[i].first][edges[i].second]){
				G2.addEdge(edges[i].first + 1 , edges[i].second + 1);
			}
		}
		G2.calculate(N);

		REP(i , Q){
			Long u , v;
			cin >> u >> v;
			u--;
			v--;
			if( (G1.component[u] != G1.component[v]) || (G2.component[u] != G2.component[v])){
				cout << "N\n";
			} else {
				cout << "Y\n";
			}
		}
		cout << "-\n";
		cin >> N >> M >> Q;
	}
	return 0;
}

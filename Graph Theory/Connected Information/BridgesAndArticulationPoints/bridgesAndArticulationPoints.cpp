#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 4e5;  

struct Edge{
	Long u, v;
	Edge(Long u , Long v) : u(u) , v(v){
	}
	Edge(){
	}
};

struct Graph {
	vector <Long> adj[MAX];
	bool vis[MAX];
	Long tIn[MAX];//tiempo de entrada al nodo
	Long low[MAX];//minimo tiempo al que puede ir ese nodo o uno de sus descendientes por medio de cualquier arista(tree o back edge) 
	Long timer = 0;
	vector<Edge> bridge;
	vector<Long> articulation;
	bool isArticulation[MAX];
	unordered_map<Long,bool> isBridge[MAX];
	
	void clear(Long N = MAX) {
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
	
	void printBridges() {
		cout << "Bridges = ";
		REP(i , bridge.size()){
			cout << "( " << bridge[i].u + 1 << " - " << bridge[i].v + 1 << " ) ; ";
		}
	} 	
	
	void printArticulations() {
		cout << "Articulations = ";
		REP(i , articulation.size()) {
			cout << articulation[i] + 1 << " ";
		}
		cout << endl;
	}
} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	REP(i , m) {
		Long u , v;
		cin >> u >> v;
		G.addEdge(u , v);
	}
	G.calculate(n);
	G.printArticulations();
	G.printBridges();
	
	return 0;
}


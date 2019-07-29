#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737

const Long MAX = 4e5;  

struct Edge{
	Long u, v;
	Edge(Long u , Long v) : u(u) , v(v){
	}
	Edge(){
	}
};

bool cmp(const Edge &E1, const Edge &E2) {
	if(E1.u == E2.u) return E1.v < E2.v;
	return E1.u < E2.u;
}

set<pair<Long,Long> > edges;

struct Graph {
	vector <Long> adj[MAX];
	bool vis[MAX];
	Long tIn[MAX];//tiempo de entrada al nodo
	Long low[MAX];//minimo tiempo al que puede ir ese nodo o uno de sus descendientes por medio de cualquier arista(tree o back edge) 
	Long timer = 0;
	vector<Edge> bridge;
	
	void clear(Long N = MAX) {
		edges.clear();
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			tIn[i] = -1;
			low[i] = -1;
		}
		timer = 0;
		bridge.clear();
	}
	
	void addEdge(Long u, Long v) {
		adj[u].pb(v);
		//adj[v].pb(u);
		edges.insert({u , v});
	}
	
	void dfsBridge(Long u, Long p = -1){
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		for(Long v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
			} else {
				dfsBridge(v , u);
				low[u] = min(low[u] , low[v]);
				if(low[v] > tIn[u]) {
					bridge.pb(Edge(min(u, v) , max(u , v)));
					
				}
			}
		}
	}
	
	void findBridges(Long n) {
		for(Long i = 0; i < n; i++) {
			if(!vis[i]) {
				dfsBridge(i);
			}
		}
		sort(bridge.begin(), bridge.end(), cmp);
	} 	
} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	while(cin >> n) {
		/*if(primero) {
			primero = false;
		} else {
			cout << endl;
		}*/
		G.clear(n);
		REP(i , n) {
			Long u;
			cin >> u;
			string s;
			cin >> s;
			
			Long c = 0;
			for(Long i = 1 ; i + 1 < s.size(); i++) {
				c = c * 10 + (s[i] - '0');
			}
			
			REP(i , c) {
				Long v;
				cin >> v;
				G.addEdge(u , v);
			}
			
		}
		G.findBridges(n);
		cout << G.bridge.size() << " critical links" << endl;
		REP(i , G.bridge.size()) {
			cout << G.bridge[i].u << " - " << G.bridge[i].v << endl;
		}
		cout << endl;
	}	
	return 0;
}

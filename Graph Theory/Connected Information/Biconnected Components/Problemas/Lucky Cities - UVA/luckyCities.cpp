#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 2e5;
vector<Long> biconnectedComponent[MX];

Long color[MX];

set<Long> ans;
bool dfs2(Long u, Long c) {
	color[u] = c;
	c = (c + 1) % 2;
	for(Long v : biconnectedComponent[u]) {
		
		if(color[v] != 2 ) {
			if(color[v] != c) {
				return false;
			} else {
				continue;
			}
		}
		if(!dfs2(v , c )) {
			return false;
		}
		
	} 
	
	return true;
}

struct Edge{
	Long u, v;
	Edge(Long u , Long v) : u(u) , v(v){
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


struct Graph{
	vector<Long> adj[MX];
	bool vis[MX];
	Long tIn[MX];
	Long low[MX];
	Long timer = 0;
	stack<Edge> edges;
	
	void clear(Long N){
		REP(i , N) {
			adj[i].clear();
			vis[i] = false;
			tIn[i] = low[i] = -1;
		}
		timer = 0;
		ans.clear();
	}
	
	void addEdge(Long u , Long v){
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void addBiconnectedComponent(Edge e){
		if(edges.empty()) return;
		
		unordered_set<Long> s;
		vector<Edge> aux;
		
		while(!edges.empty()){
			Edge cur = edges.top();
			Long u = cur.u;
			Long v = cur.v;
			s.insert(u);
			s.insert(v);
			aux.pb(cur);
			edges.pop();
			if(cur == e){
				break;
			}
		}
		
		for(Long u : s){
			biconnectedComponent[u].clear();
			color[u] = 2;
		}
		
		REP(i , aux.size()) {
			biconnectedComponent[aux[i].u].pb(aux[i].v);
			biconnectedComponent[aux[i].v].pb(aux[i].u);
		}
		
		
		if(!dfs2(aux[0].u , 0)) {
			for(Long u : s) {
				ans.insert(u);
			}
		}
	}
	
	void dfs(Long u = 0, Long p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		Long children = 0;
		for(Long v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
				if(tIn[v] < tIn[u]){
					edges.push(Edge(u , v));
				}
			} else {
				edges.push(Edge(u , v));
				dfs(v , u );
				low[u] = min(low[u] , low[v]);

				if(low[v] >= tIn[u] && p != -1 ) {
					addBiconnectedComponent(Edge(u,v));
				}
				children++;
				if(p == -1 && children > 1){
					addBiconnectedComponent(Edge(u,v));
				}
			}
		}
		if(p == -1 ) {
			addBiconnectedComponent(Edge(-1,-1));
		} 
	}

} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t ,T ) {
		
		Long n , m ;
		cin >> n >> m;
		G.clear(n);
		REP(i , m) {
			Long u, v;
			cin >> u >> v;
			G.addEdge(u , v );
		}
		REP(i , n) {
			if(!G.vis[i]) {
				G.dfs(i);
			}
		}
		cout << ans.size() << endl;
	}
	
	return 0;
}

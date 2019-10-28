#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;
 
typedef long long Long;
 
const Long MX = 3000;
const Long INF = 1e18;
 

struct FlowGraph{
	vector<Long> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool vis[MX];
	bool added[MX][MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			vis[i] = false;
			for(Long j = 0; j < N; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir ){
		if(!added[min(u, v)][max(u , v)]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		added[min(u , v)][max(u , v)] = true;
		cap[u][v] += w;
		if(!dir){
			cap[v][u] += w;
		}
		
	}
	
	Long dfs(Long u, Long t ,Long f){ //O(E)
		if(u == t) return f;
		if(vis[u]) return 0;
		vis[u] = true;
		
		for( Long v : adj[u] ) {
			Long cf = cap[u][v] - flow[u][v];
			if(cf == 0) continue;
			
			Long ret = dfs(v, t, min(f, cf) );
			
			if(ret > 0){
				flow[u][v] += ret;
				flow[v][u] -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t, Long n){ //O((E |F|)
		while(true){ // O(|F|) iterations
			fill(vis, vis + n, false);
			Long inc = dfs(s, t, INF);
			if(inc == 0) break;
		}
		Long ans = 0;
		for(Long i = 0; i < n; i++){
			if(flow[s][i] > 0){
				ans += flow[s][i];
			}
			
		}
		return ans;
	}
	
} GF;

 
 
struct Edge{
	Long u,v,w;
	Edge() {}
	Edge(Long u, Long v, Long w) : u(u) , v(v) , w(w) {}
	bool operator <(Edge const &other) const{
        return w < other.w;
    }
};


struct Graph{
	vector<Edge> edges;
	
	
	void addEdge(Long u, Long v, Long w) {
		edges.pb(Edge(u , v , w));
	}

	Long kruskal(Long N) { //O(mlogn)
		sort(edges.begin(), edges.end());

		Long ans = 0;
		
		Long i = 0;
		while(i < edges.size()){
			vector<Edge> aux;
			aux.pb(edges[i]);
			ans += GF.maxFlow(edges[i].u, edges[i].v, N);
			i++;
			
			while(i < edges.size() && edges[i].w == aux[i].w){
				ans += GF.maxFlow(edges[i].u, edges[i].v, N);
				aux.pb(edges[i]);
				i++;
			}
			for(Edge e : aux){
				GF.addEdge(e.u , e.v, 1 , false);
			}
		}
		
		return ans;
	}
	

} G;
 
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		u--;
		v--;
		G.addEdge(u , v , w);
	}

	cout << G.kruskal(n) << endl;
	return 0;
}

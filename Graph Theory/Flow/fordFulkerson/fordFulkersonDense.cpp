#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 5000;
const Long INF = 1e18;

struct Graph{
	vector<Long> adj[MX];
	unordered_map<Long, Long> cap[MX]; //capacity
	bool vis[MX];
	unordered_map<Long , bool> added[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			cap[i].clear();
			added[i].clear();
			vis[i] = false;
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir = false){
		u--;
		v--;
		if(!added[min(u , v)][max(u, v)]){
			adj[u].push_back(v);
			adj[v].push_back(u);
		} 	
		added[min(u, v)][max(u, v)] = true;
		cap[u][v] += w;
		if(!dir){
			cap[v][u] += w;
		}
		
	}
	
	Long dfs(Long u, Long t ,Long f){ //O(E)
		//t = target
		if(u == t) return f;
		if(vis[u]) return 0;
		vis[u] = true;
		
		for( Long v : adj[u] ) {
			if(cap[u][v] == 0) continue;
			Long ret = dfs(v,t, min(f,cap[u][v]) );
			if(ret > 0){
				cap[u][v] -= ret;
				cap[v][u] += ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t){ //O(E |F| )
		Long flow = 0;
		while(true){
			fill(vis, vis + MX, false);
			Long inc = dfs(s, t, INF);
			if(inc == 0) break;
			flow += inc;
		}
		return flow;
	}
	
} G;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long n,m;
	cin >> n >> m;
	
	REP( i , m){
		Long u,v,c;
		cin >> u >> v >> c;
		u--; v--;
		G.addEdge(u,v,c);//directed
		//addEdge(u,v,c,c); //undirected
	}
	
	Long s,t;
	cin >> s >> t;
	Long resp = G.maxFlow(s,t);
	
	return 0;
}

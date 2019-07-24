#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 5000;
const Long INF = 1e18;

struct Graph{
	vector<Long> adj[MAX];
	Long cap[MAX][MAX]; //capacidad
	bool vis[MAX];
	bool M[MAX][MAX];
	
	void build(Long N = MAX){
		REP(i , N){
			adj[i].clear();
			REP(j , N) {
				cap[i][j] = 0;
				M[i][j] = false;
				vis[i] = false;
			}
		}
	}
	
	Long dfs(Long u, Long t ,Long f){
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
	
	Long fordFulkerson(Long s, Long t){ //O((n+m)|F|
		Long flow = 0;
		while(true){
			fill(vis, vis + MAX, false);
			Long inc = dfs(s,t,INF);
			if(inc == 0) break;
			flow += inc;
		}
		return flow;
	}
	
	void addEdge(Long u, Long v, Long uv, Long vu = 0){
		if(!M[u][v]) adj[u].pb(v);
		if(!M[v][u]) adj[v].pb(u);
		
		M[u][v] = M[v][u] = true;
		cap[u][v] += uv;
		cap[v][u] += vu;
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
	Long resp = G.fordFulkerson(s,t);
	
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 5000;
const Long INF = 1e18;

struct Edge{
	Long to, cap, flow;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long to, Long cap) : to(to), cap(cap), flow(0), rev(NULL) {}
};

struct Graph{
	vector<Edge *> adj[MX];
	bool vis[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			vis[i] = false;
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir ){
		Edge *forward = new Edge(v , w);
		Edge *backward = new Edge(u , 0);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].pb(forward);
		adj[v].pb(backward);

		if(!dir){
			forward = new Edge(u , w);
			backward = new Edge(v , 0);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].pb(forward);
			adj[u].pb(backward);
		}
	}
	
	Long dfs(Long u, Long t ,Long f){ //O(E)
		if(u == t) return f;
		if(vis[u]) return 0;
		vis[u] = true;
		
		for( Edge * e : adj[u] ) {
			Long v = e->to;
			Long cf = e->cap - e->flow;
			if(cf == 0) continue;
			
			Long ret = dfs(v, t, min(f, cf) );
			
			if(ret > 0){
				e->flow += ret;
				e->rev->flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t, Long n){ //O((E |F|)
		Long ans = 0;
		while(true){ // O(|F|) iterations
			fill(vis, vis + n, false);
			Long inc = dfs(s, t, INF);
			if(inc == 0) break;
			ans += inc;
		}
		return ans;
	}
	
} G;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n, m;

	while(cin >> n >> m){
		if(n == 0 && m == 0) break;
		Long s = 0;
		Long t = n + 1;
		G.clear(t + 1);
		REP(i , n){
			Long w;
			cin >> w;
			if(w == 1){
				G.addEdge(s , i + 1 , 1, false);
			} else {
				G.addEdge(i + 1 , t , 1 , false);  
			}
		}
		REP(i , m){
			Long u , v;
			cin >> u >> v;
			G.addEdge(u , v , 1 , false);
		}
		cout << G.maxFlow(s , t , t + 1) << "\n";
	}
	return 0;
}

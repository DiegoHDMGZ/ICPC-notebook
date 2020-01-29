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
	
	Long Q;
	cin >> Q;
	REP(q , Q){
		Long n , m , v , maxT;
		cin >> n >> m >> v >> maxT;
		vector<pair<Long,Long> > person(n);
		vector<pair<Long,Long> > taxi(m);
		Long s = 0;
		Long t = n + m + 1;
		G.clear(t + 1);
		REP(i , n){
			G.addEdge(m + i + 1 , t ,1 , true );
			cin >> person[i].first >> person[i].second;
		}
		REP(i , m){
			G.addEdge(s , i + 1, 1 , true);
			cin >> taxi[i].first >> taxi[i].second;
		}
		REP(i , m){
			REP(j , n){
				if(( abs(taxi[i].first - person[j].first) + abs(taxi[i].second - person[j].second) ) * 200 <= maxT * v){
					G.addEdge(i + 1 , j + m + 1 , 1 , true);
				}
			}
		}
		cout << G.maxFlow(s , t , t + 1) << endl;
	}
	
	return 0;
}

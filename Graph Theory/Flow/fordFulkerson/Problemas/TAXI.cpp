#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;


const Long MX = 5000;
const Long INF = 1e18;


struct Graph{
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

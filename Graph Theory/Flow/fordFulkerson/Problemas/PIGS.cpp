#include <iostream>
#include <vector>
#include <deque>
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
		
		REP(i , adj[u].size()) {
			Long v = adj[u][i];
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
vector<Long> clients[MX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	Long t = m + n + 1;
	Long s = 0;
	for(Long i= 1 ; i <= n; i++){
		Long w;
		cin >> w;
		if(w > 0){
			G.addEdge(m + i  , t , w, true);
		}
		
	}
	for(Long i = 1; i <= m; i++){
		Long K;
		cin >> K;
		vector<Long> batch;
		REP(k , K){
			Long u;
			cin >> u;
			batch.pb(u);
			G.addEdge(i , m + u , INF, true);
			for(Long t = 0; t < clients[u].size(); t++){
				Long c = clients[u][t];
				G.addEdge(i , c , INF, true);
			}
		}
		REP(t, batch.size()){
			Long u = batch[t];
			clients[u].pb(i);
		}
		Long w;
		cin >> w;
		if(w > 0){
			G.addEdge(s , i , w , true );
		}
	}
	cout << G.maxFlow(s , t , n + m + 2) << endl;
	return 0;
}

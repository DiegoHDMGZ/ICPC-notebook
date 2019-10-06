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
		/*debug(u );
		debug(v );
		debug(w);
		cout << endl;*/
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
	
	Long N;
	while(cin >> N){
		
		vector<pair<Long,Long> > v;
		REP(i , N){
			Long a , b;
			cin >> a >> b;
			v.pb({a,b});
		}
		Long ans = 0;
		Long s = 0;
		Long t = 2 * N + 1;
		REP(i , N){
			G.clear(2 * N + 2);
			Long k = 0;
			for(Long j = 0; j < N; j++){
				if(v[j].first - 1 == i || v[j].second - 1 == i){
					k++;
				}
			}
			if(k <= 1){
				ans++;
				continue;
			}
			for(Long j = 0; j < N; j++){
				if(v[j].first - 1 != i && v[j ].second - 1 != i && i != j){
					G.addEdge(j + 1 , v[j].first + N, 1, true);
					G.addEdge(j + 1, v[j ].second + N , 1, true);
					G.addEdge(s , j + 1, 1, true);
					
				}
				if(j != v[i].first - 1 && j != v[i].second - 1){
					G.addEdge(j + 1 + N , t , k - 1 , true);
				} else {
					G.addEdge(j + 1 + N , t , k - 2  , true);
				}
				
			}
			if(G.maxFlow(s , t , 2 * N + 2) < N - k - 1){
				ans++;
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}

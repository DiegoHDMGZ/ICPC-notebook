#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;
typedef long double Double;

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

Double dist(pair<Double, Double> a, pair<Double,Double> b){
	return (b.second - a.second)* (b.second - a.second) + (b.first - a.first) * (b.first - a.first);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m , maxTime ,v;
	while(cin >> n >> m >> maxTime >> v){
		vector<pair<Double,Double> > gopher(n);
		vector<pair<Double,Double> > hole(m);
		Long s = 0 , t = n + m + 1;
		G.clear(t + 1);
		REP(i , n){
			cin >> gopher[i].first >> gopher[i].second;
			G.addEdge(s , i + 1 , 1 , true);
		}
		REP(i , m){
			cin >> hole[i].first >> hole[i].second;
			G.addEdge(i + 1 + n , t , 1 , true);
		}
		REP(i , n){
			REP(j , m){
				if(dist(gopher[i], hole[j]) <= (maxTime * v) * (maxTime * v)){
					G.addEdge(i + 1 , j + n + 1 , 1 , true);
				}
			}
		}
		cout << n - G.maxFlow(s ,t , t + 1) << endl;
	}
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 3000;
const Long INF = 1e18;
struct Graph{
	vector<Long> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool added[MX][MX];
	Long level[MX];
	Long nextEdge[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			for(Long j = 0; j < N; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir){
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
	
	Long dfs(Long u, Long t ,Long f){ 
		if(u == t) return f;
		
		for(Long &i = nextEdge[u]; i < adj[u].size(); i++){
			Long v = adj[u][i];
			Long cf = cap[u][v] - flow[u][v];
			if(cf == 0 || level[v] != level[u] + 1) continue;
			
			Long ret = dfs(v, t, min(f, cf) );
			
			if(ret > 0){
				flow[u][v] += ret;
				flow[v][u] -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	bool bfs(Long s, Long t ){ //O(E)
		deque<Long> q; 
		q.push_back(s);
		level[s] = 0;
		while(!q.empty()){
			Long u = q.front();
			q.pop_front();
			for(Long v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				if(level[v] == -1 && cf > 0){
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	Long maxFlow(Long s, Long t, Long n){//General: O(E * V^2), Unit Cap: O(E * min(E^(1/2) , V^(2/3))), Unit Network: O(E * V^(1/2))
		//unit network is a network in which all the edges have unit capacity,
		//and for any vertex except s and t either incoming or outgoing edge is unique.
		Long ans = 0;
		while(true){ //O(V) iterations
			fill(level, level + n, -1);
			if(!bfs(s, t) ){
				break;
			}
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n , 0);
			Long inc;
			do{
				inc = dfs(s , t , INF);
				ans += inc;
			} while (inc > 0);
		}
		return ans;
	}
} G;


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(q, T){
		cout << "Case " << q + 1 << ": ";
		Long n, m;
		cin >> n;
		
		vector<Long> a(n);
		REP(i , n){
			cin >> a[i];
		}
		cin >> m;
		vector<Long> b(m);
		REP(i , m){
			cin >> b[i];
		}
		Long s = 0;
		Long t = n + m + 1;
		G.clear(t + 1);
		REP(i , n){
			G.addEdge(s , i + 1, 1 , true);
		}
		REP(i , m){
			G.addEdge(i + 1 + n , t, 1 , true);
		}
		REP(i , n){
			REP(j , m){
				if(a[i] == 0) {
					if(b[j] == 0){
						G.addEdge(i + 1 , j + n + 1 , 1 , true);
					}
				} else {
					if(b[j] % a[i] == 0 ){
						G.addEdge(i + 1 , j + n + 1 , 1 , true);
					}
				}
			}
		}
		cout << G.maxFlow(s,t , t + 1) << "\n";
	}
	
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;


const Long MX = 5e4;
const Long INF = 1e18;

struct Graph{
	vector<Long> adj[MX];
	map<Long,Long> cap[MX]; 
	map<Long,Long> flow[MX];
	map<Long,bool> added[MX];
	Long level[MX];
	Long nextEdge[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			cap[i].clear();
			flow[i].clear();
			added[i].clear();
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

const Long MX2 = 200;


Long val[MX2][MX2];

Long n;
void solve(){
	assert(n <= 100);
	Long ind = 0;
	REP(i , n){
		string A;
		cin >> A;
		REP(j , n){
			if(A[j] == 'X'){
				val[i][j] = ++ind;
			} else {
				val[i][j] = 0;
			}
		}
		val[i][n] = ++ind;
		val[n][i] = ++ind;
	}
	
	Long s = 0;
	Long t = 2 * ind + 1;
	G.clear(t + 1);
	
	for(Long i = 1 ; i <= ind; i++){
		G.addEdge(s, i , 1 , true);
		G.addEdge(i + ind , t , 1 , true);
	}
	
	REP(i , n){
		REP(j , n){
			if(val[i][j] == 0){
				Long row = -1;
				Long column = -1;
				for(Long k = j + 1; k <= n; k++){
					if(val[i][k] > 0){
						row = val[i][k];
						break;
					}
				}
				for(Long k = i + 1; k <= n; k++){
					if(val[k][j] > 0){
						column = val[k][j];
						break;
					}
				}
				G.addEdge(row , column + ind, 1 , true);
			}
		}
	}
	cout << G.maxFlow(s, t , t + 1) << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while(cin >> n){
		solve();
	}

	return 0;
}

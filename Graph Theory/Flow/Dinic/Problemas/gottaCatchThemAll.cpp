#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://csacademy.com/ieeextreme-practice/task/gotta-catch-em-all/

const Long MX = 5000;
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
Long d[MX][MX];

Long n , m , minDiglet, digTime;
bool check( Long maxTime){
	Long s = 0;
	Long t = n + 3 * m + 1 ;
	G.clear(t + 1);
	for(Long i = 1 ; i <= n; i++){
		G.addEdge(s , i  , 1 , true);
	} 
	for(Long i = 1 ; i <= m; i++){
		G.addEdge(n + i , n + 2 * m + i , 1 , true);
	}
	
	for(Long i = 1; i <= m; i++){
		G.addEdge(n + m + i , n + 2 * m + i , 1 , true);
	}
	
	for(Long i = 1; i <= m; i++){
		G.addEdge(n + 2 * m + i , t , 2 , true);
	}
	
	REP(i , n){
		REP(j , m){
			if(d[i][j] <= maxTime){
				G.addEdge(i + 1, n + j + 1 , 1,  true);
			}
			if(d[i][j] + digTime <= maxTime){
				G.addEdge(i + 1 , n + m + j + 1 , 1 , true);
			}
		}
	}
	
	return G.maxFlow(s , t , t + 1) >= minDiglet;
}

Long search(  Long ini , Long fin ){ //O(logn)
	// F F F... V V V
	if(check(ini)) return ini; //todos V
	
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= ini + (fin - ini) / 2;
		
		if(check( med )){
			fin = med;
		} 
		else {
			ini = med;
		}
	}

	//hay 2 valores ini es F y fin es V
	return fin;
}

void doit(){
	
	cin >> m >> n >> minDiglet>> digTime;
	
	REP(i , n){
		REP(j , m){
			cin >> d[i][j];
		}
	}
	
	cout << search(1 , 5e4) << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t, T){
		doit();
	}
	return 0;
}

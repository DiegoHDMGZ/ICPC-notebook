#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 2010;
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

bool possible(vector<Long> &hA, vector<Long> &hB , Long n , Long d){
	Long a = hA.size();
	Long b = hB.size();
	Long s = 0;
	Long t = 2 * a + 2 * b + 1;
	G.clear(t + 1);
	
	for(Long i = 1 ; i <= n; i++){
		G.addEdge(s , i  , 1 , true);
	}
	
	for(Long i = 1; i <= a; i++){
		G.addEdge(i , i + a , 1, true); 
	}
	for(Long i = 2 * a + 1; i <= 2 * a + b; i++){
		G.addEdge(i , i + b , 1, true);
	}
	
	for(Long i = 2 * a + b + 1; i <= 2 * a + b + n; i++){
		G.addEdge(i , t, 1 , true);
	}
	
	REP(i , a){
		REP(j , b){
			if( abs(hA[i] - hB[j]) < d){
				G.addEdge(i + 1 + a , 2 * a + j + 1, 1 , true);
				G.addEdge(2 * a + b + j + 1 , i + 1, 1 ,true);
			}
		}
	}
	
	return G.maxFlow(s , t , t + 1) == n; 
} 


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n ,a , b , d;
	cin >> n >> a >> b >> d;
	vector<Long> hA(a);
	REP(i , a){
		cin >> hA[i];
	}
	vector<Long> hB(b);
	REP(i , b){
		cin >> hB[i];
	}
	sort(hA.rbegin(), hA.rend());
	sort(hB.begin(), hB.end());

	
	if(possible(hA, hB, n , d) ){
		cout << "S\n";
	} else {
		sort(hB.rbegin(), hB.rend());
		sort(hA.begin(), hA.end());
		if(possible(hB, hA, n , d)){
			cout << "S\n";
		} else {
			cout << "N\n";
		}
	}
	return 0;
}
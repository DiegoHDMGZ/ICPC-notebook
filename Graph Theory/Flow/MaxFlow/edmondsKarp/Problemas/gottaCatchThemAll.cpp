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
	bool vis[MX];
	bool added[MX][MX];
	Long parent[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			vis[i] = false;
			parent[i] = -1;
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
	
	void transition(Long s , Long t, Long inc){
		Long cur = t;
		
		while(cur != s){
			Long prev = parent[cur];
			flow[prev][cur] += inc;
			flow[cur][prev] -= inc;
			cur = prev;
		}
	}
	
	Long bfs(Long s, Long t ){ //O(E)
		deque<pair<Long,Long> > q; //< node, capacity>
		q.push_back({s , INF});
		vis[s] = true;
		while(!q.empty()){
			Long u = q.front().first;
			Long c = q.front().second;
			q.pop_front();
			if(u == t){
				return c;
			}
			for(Long v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				if(!vis[v] && cf > 0){
					parent[v] = u;
					vis[v] = true;
					Long x = min(c , cf);
					q.push_back({v , x});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t , Long n){ //O(E * min(E * V , |F|))
		Long ans = 0;
		while(true){ //O( min (E * V , |F| ) ) iterations
			fill(vis, vis + n, false);
			fill(parent, parent + n, -1);
			Long inc = bfs(s, t);
			if(inc == 0) break;
			ans += inc;
			transition(s , t , inc);
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
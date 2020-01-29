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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	while(cin >> n){
		G.clear(2 * n + 2);
		for(Long i = 1 ;i <= n; i++){
			Long w;
			cin >> w;
			G.addEdge(2 * i - 1 , 2 * i  , w , true);
		}
		Long m;
		cin >> m;
		REP(i , m){
			Long u , v , w;
			cin >> u >> v >> w;
			G.addEdge(2 * u , 2 * v - 1, w , true);
		}
		Long B, D;
		cin >> B >> D;
		REP(i , B){
			Long x;
			cin >> x;
			G.addEdge(0 , 2 * x - 1 , INF, true);
		}
		REP(i , D){
			Long x;
			cin >> x;
			G.addEdge(2 * x , 2 * n + 1 , INF, true);
		}
		cout << G.maxFlow(0 , 2 * n + 1 , 2 * n + 2) << endl;
	}
	
	return 0;
}

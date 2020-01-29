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
	bool added[MX][MX];
	Long parent[MX];
	
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
		q.push_back(make_pair(s , INF));
		parent[s] = -2;
		while(!q.empty()){
			Long u = q.front().first;
			Long c = q.front().second;
			q.pop_front();
			if(u == t){
				return c;
			}
			REP(i, adj[u].size()){
				Long v = adj[u][i];
				Long cf = cap[u][v] - flow[u][v];
				if(parent[v] == -1 && cf > 0){
					parent[v] = u;
					Long x = min(c , cf);
					q.push_back(make_pair(v , x));
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t , Long n){ //O(E * min(E * V , |F|))
		Long ans = 0;
		while(true){ //O( min (E * V , |F| ) ) iterations
			fill(parent, parent + n, -1);
			Long inc = bfs(s, t);
			if(inc == 0) break;
			ans += inc;
			transition(s , t , inc);
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

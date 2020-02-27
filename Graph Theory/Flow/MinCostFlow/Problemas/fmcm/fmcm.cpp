#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;
 
typedef int Long;
 
const Long MX = 350;
const Long INF = 1e9;
 
struct Edge{
	Long from , to, cap, flow, cost;
	Edge(){}
	Edge(Long from , Long to, Long cap, Long cost) : from(from) , to(to), cap(cap), flow(0), cost(cost) {}
};
 
 
struct Graph{
	vector<Long> adj[MX];
	Long cap[MX][MX];
	Long cost[MX][MX];
	Long flow[MX][MX];
	Long parent[MX];
	Long pot[MX];
	bool inQ[MX];
	
	void addEdge(Long u, Long v, Long w, Long c, bool dir){
		adj[u].push_back(v);
		adj[v].push_back(u);
		cap[u][v] += w;
		cost[u][v] = c;
		cost[v][u] = -c;
	}
	
	void bellmanFord(Long s, Long t, Long n){
		vector<Long> d(n , INF);
		d[s] = 0;
		queue<int> Q;
		for (Q.push(s), inQ[s] = 1; !Q.empty(); Q.pop())
		{
			vector<int> :: iterator it;
			int u = Q.front();
			inQ[u] = 0;
		   
			for (Long v : adj[u]){
				if (cap[u][v] - flow[u][v] > 0 && d[u] + cost[u][v] < d[v]){
					d[v] = d[u] + cost[u][v];
					if (inQ[v])
						continue;
	 
					inQ[v] = true;
					Q.push(v);
				}
			}
				
		}
		for(Long i = 0; i < n; i++){
			pot[i] = d[i];
		}
	}
	
	
	bool dijkstra(Long s, Long t, Long n, Long &ans){ //O(nlogm + mlogn)
		//<flow, cost>
		priority_queue<pair<Long,Long> ,vector<pair<Long,Long>> , greater<pair<Long,Long>>> q;
		
		vector<Long> d(n , INF);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		q.push({d[s], s});
		
		while(!q.empty()){
			
			pair<Long,Long> p = q.top();
			q.pop();
			int u = p.second;
			if(p.first != d[u]){
				continue;
			}
	
			for( Long v: adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				Long c = cost[u][v] + pot[u] - pot[v];
				
				if(cf > 0 && d[u] + c < d[v]){
					d[v] = d[u] + c;
					q.push({d[v], v});
					residualCap[v] = min(residualCap[u], cf);
					parent[v] = u;
				}
			}
		}
		if(d[t] == INF){
			return false;
		}
		for(Long i = 0; i < n; i++){
			pot[i] += d[i];
		}
		Long cf = residualCap[t];
		
		Long cur = t;
		while(true ){
			flow[parent[cur]][cur] += cf;
			flow[cur][parent[cur]] -= cf;
			cur = parent[cur];
			if(cur == s){
				break;
			}
		}
		ans = pot[t] * cf;
		return true;
	}
	
	
	Long minCostFlow(Long s, Long t, Long n){ 
		//O(m log n *  |f| ) = O(m log n *(nU))
		//<maxFlow, minCost>
		bellmanFord(s , t , n); //not necessary if there is no negative edges
		Long ans = 0;
		while(true){
			Long c;
			bool x = dijkstra(s , t , n , c );
			if(!x) break;
			
			ans += c;
		}
		
		return ans;
	}
} G;
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	freopen("fmcm.in", "r", stdin);
	freopen("fmcm.out", "w", stdout);
	Long n, m , s, t;
	cin >> n >> m >> s >> t;
	
	s--;
	t--;
	REP(i , m){
		Long u , v , w , c;
		cin >> u >> v >> w >> c;
		u--;
		v--;
		G.addEdge(u , v , w , c, true);
	}
	cout << G.minCostFlow(s , t , n) << endl;
 
	return 0;
}

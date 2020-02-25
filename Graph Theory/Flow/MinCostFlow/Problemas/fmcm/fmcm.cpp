	
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
	vector<Edge> E;
	
	void addEdge(Long u, Long v, Long w, Long c, bool dir){
		adj[u].push_back(v);
		adj[v].push_back(u);
		cap[u][v] += w;
		cost[u][v] = c;
		cost[v][u] = -c;
		E.pb(Edge(u , v , w, c));
	}
	
	void bellmanFord(Long s , Long t, Long n){ //O(nm)
		vector<Long> d(n, INF);
		d[s] = 0;
		Long m = E.size();
		Long negaCycle; //negative cycle flag
		
		REP(i , n) {
			negaCycle = -1; 
			REP ( j , m ) {
				if (d[E[j].from] < INF && E[j].cap - E[j].flow > 0) {
					if (d[E[j].to] > d[E[j].from] + E[j].cost) {
						d[E[j].to] = max(-INF ,d[E[j].from] + E[j].cost); //avoiding overflow
						negaCycle = E[j].to;
					}
				}
			}
			if(negaCycle == -1) break;
		}
		for(Long i = 0; i < n; i++){
			pot[i] = d[i];
		}
		assert(negaCycle == -1); //(!) algorithm doesnt apply
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

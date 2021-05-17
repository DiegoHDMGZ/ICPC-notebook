#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 350;
const Long INF = 1e9;

struct Graph{
	vector<Long> adj[MX];
	Long cap[MX][MX];
	Long cost[MX][MX];
	Long flow[MX][MX];
	Long parent[MX];
	Long pot[MX];
	bool inQueue[MX];
	
	void addEdge(Long u, Long v, Long w, Long c){
		adj[u].push_back(v);
		adj[v].push_back(u);
		cap[u][v] = w;
		cost[u][v] = c;
		cost[v][u] = -c;
	}
	
	void spfa(Long s , Long n){ //O(nm)
		for(Long i = 0; i < n; i++){
			pot[i] = INF;
		}
		queue<Long> q;
		pot[s] = 0;
		inQueue[s] = true;
		q.push(s);
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			for(Long v : adj[u]){
				if (cap[u][v] - flow[u][v] > 0 && pot[u] + cost[u][v] < pot[v]){
					pot[v] = pot[u] + cost[u][v];
					if(!inQueue[v]){
						q.push(v);
					}
					inQueue[v] = true;
				}
			}
		}
	}
	
	
	pair<Long,Long> dijkstra(Long s, Long t, Long n){ //O(n^2)
		//<flow, cost>
		
		vector<Long> d(n , INF);
		vector<bool> vis(n , false);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		
		for(Long i = 0; i < n; i++){
			Long u = -1;
			for(Long j = 0; j < n; j++){
				if(!vis[j] && (u == -1 || d[j] < d[u])){
					u = j;
				}
			}
			if(u == -1 || d[u] == INF){
				break;
			}
			
			vis[u] = true;
			for(Long v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				Long c = cost[u][v] + pot[u] - pot[v];
				
				if(cf > 0 && d[u] + c < d[v]){
					d[v] = d[u] + c;
					residualCap[v] = min(residualCap[u], cf);
					parent[v] = u;
				}
			}
		}
		
		if(d[t] == INF){
			return {0,0};
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
		return {cf,pot[t] * cf} ;
	}
	
	
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O(n^2 *  |f| ) = O(n^2 *(nU))
		//Initially no negative cycles
		//<maxFlow, minCost>
		spfa(s  , n); //not necessary if there is no negative edges
		pair<Long,Long> inc;
		pair<Long,Long> ans = {0,0};
		do{
			inc = dijkstra(s , t , n );
			ans.first += inc.first;
			ans.second += inc.second;
		}while(inc.first > 0);
		
		return ans;
	}
} G;

int main() {
	return 0;
}

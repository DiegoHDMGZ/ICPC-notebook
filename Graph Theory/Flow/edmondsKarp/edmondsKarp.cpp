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
	Long cap[MX][MX]; //capacity
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
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir = false){
		u--;
		v--;
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
			cap[prev][cur] -= inc;
			cap[cur][prev] += inc;
			cur = prev;
		}
	}
	
	Long bfs(Long s, Long t , Long n){ //O(E)
		fill(vis, vis + n, false);
		fill(parent, parent + n, -1);
		
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
				if(!vis[v] && cap[u][v] > 0){
					parent[v] = u;
					vis[v] = true;
					Long x = min(c , cap[u][v]);
					q.push_back({v , x});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t , Long n){ //O( V * E ^ 2)
		Long flow = 0;
		while(true){
			Long inc = bfs(s, t, n);
			if(inc == 0) break;
			flow += inc;
			transition(s , t , inc);
		}
		return flow;
	}
	
} G;



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

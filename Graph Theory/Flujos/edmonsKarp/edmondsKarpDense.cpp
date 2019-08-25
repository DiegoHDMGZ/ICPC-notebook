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
	unordered_map<Long, Long> cap[MX]; //capacity
	bool vis[MX];
	unordered_map<Long , bool> added[MX];
	Long parent[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			vis[i] = false;
			parent[i] = -1;
			cap[i].clear();
			added[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long uv, Long vu = 0){
		if(!added[min(u, v)][max(u , v)]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		added[min(u , v)][max(u , v)] = true;
		cap[u][v] += uv;
		cap[v][u] += vu;
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
	
	Long bfs(Long s, Long t ){ //O(E)
		fill(vis, vis + MX, false);
		fill(parent, parent + MX, false);
		
		deque<pair<Long,Long> > q; //< node, capacity>
		q.push_back({s , INF});
		while(!q.empty()){
			Long u = q.front().first;
			Long c = q.front().second;
			q.pop_front();
			for(Long v : adj[u]){
				if(!vis[v] && cap[u][v] > 0){
					parent[v] = u;
					vis[v] = true;
					Long x = min(c , cap[u][v]);
					if(s == t){
						return x;
					}
					q.push_back({v , x});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t){ //O( V * E ^ 2)
		Long flow = 0;
		while(true){
			Long inc = bfs(s, t);
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

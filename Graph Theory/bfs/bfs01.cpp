#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;
const Long INF = 1e18;

struct Graph{
	Long d[MAX];
	bool used[MAX];
	vector<Long> adj[MAX];
	vector<Long> cost[MAX];
	
	void clear(Long N = MAX) {
		REP(i, N) {
			used[i] = false;
			adj[i].clear();
			cost[i].clear();
			d[i] = INF;
		}
	}
	
	void addEdge(Long u , Long v, Long w) {
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
		cost[u].pb(w);
		cost[v].pb(w);
	}
	
	void bfs01(Long s){ //O(n+m)
		d[s] = 0;
		deque<Long> Q;
		Q.pb(s);
		
		while(!Q.empty()){
			Long u = Q.front();
			Q.pop_front();
			if(used[u]) {
				continue;
			}
			used[u] = true;
			Long i = 0;
			for (Long v : adj[u] ) {
				if(d[u] + cost[u][i] < d[v]) {
					d[v] = d[u] + cost[u][i];
					if(cost[u][i] == 0){
						Q.push_front(v);
					}
					else{
						Q.pb(v);
					}
				}
				i++;
			}
		} 
	}
	
} G;

int main() {
    return 0;
}

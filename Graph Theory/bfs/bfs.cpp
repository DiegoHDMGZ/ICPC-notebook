#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long INF= 1e7;
const Long MAX = 1e5;

struct Graph{
	Long d[MAX];
	vector<Long> adj[MAX];
	
	void clear(Long N = MAX) {
		REP(i , N) {
			adj[i].clear();
			d[i] = INF;
		}
	}
	
	void addEdge(Long u, Long v) {
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void bfs(Long s){ //O(n+m)
		d[s] = 0;
		deque<Long> Q;
		Q.push_back(s);
		
		while(!Q.empty()){
			Long u = Q.front();
			Q.pop_front();
			
			for (Long v : adj[u] ) {
				if(d[v] == INF){
					d[v] = d[u] + 1;
					Q.push_back(v);
				}
			}
		}
	}

}G;

void doit(){
	Long N;
	cin >> N;
	
	REP(i , N) {
		Long u,v;
		cin >> u >> v;
		G.addEdge(u , v);
	}
	
	G.bfs(0);
}

int main() {
	Long T = 1;
	cin >> T;
	while(T--){
		doit();
	}
	return 0;
}



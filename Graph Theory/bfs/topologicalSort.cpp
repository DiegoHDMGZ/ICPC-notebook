#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e6;
const Long INF = 1e18;

struct Graph {
	vector<Long> adj[MX];
	Long indegree[MX]; 
	
	void clear(Long N = MX) {
		REP(i , N){
			indegree[i] = 0;
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v) {
		adj[u].pb(v);
		indegree[v]++;
	}
	
	vector<Long> bfs(Long N){ //O(n+m)
		deque<Long> Q;
		vector<Long> sol;
		
		REP ( i , N ) {
			if (indegree[i] == 0) {
				Q.pb(i);
			}
		}
		
		while( !Q.empty() ) {
			Long u = Q.front();
			sol.pb(u);
			Q.pop_front();
			for ( Long v : adj[u] ) {
				indegree[v]--;
				if(indegree[v] == 0){
					Q.pb(v);
				} 
			}
		}
		
		return sol;
	}
}G ;

int main() {

	return 0;
}



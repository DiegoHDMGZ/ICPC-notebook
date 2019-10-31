#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct EndPoint{
	Long node, w;
	EndPoint(){}
	EndPoint(Long node, Long w) : node(node), w(w) {}
};

struct Graph{
	Long d[MX];
	bool used[MX];
	vector<EndPoint> adj[MX];
	
	void clear(Long N = MX) {
		REP(i, N) {
			used[i] = false;
			adj[i].clear();
			d[i] = INF;
		}
	}
	
	Graph(){
		clear();
	}
	
	void addEdge(Long u , Long v, Long w) {
		adj[u].pb(EndPoint(v , w));
		adj[v].pb(EndPoint(u , w));
	}
	
	void bfs01(Long s, Long n){ //O(n+m)
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
			for (EndPoint e : adj[u] ) {
				Long v = e.node;
				if(d[u] + e.w < d[v]) {
					d[v] = d[u] + e.w;
					if(e.w == 0){
						Q.push_front(v);
					}
					else{
						Q.push_back(v);
					}
				}
			}
		} 
	}
	
} G;

int main() {
    return 0;
}

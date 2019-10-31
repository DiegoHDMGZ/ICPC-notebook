#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.codechef.com/problems/REVERSE

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
	
	void addEdge(Long u , Long v, Long w) {
		adj[u].pb(EndPoint(v , w));
	}
	
	void bfs01(Long s, Long n){ //O(n+m)
		for(Long u = 0; u < n; u++){
			d[u] = INF;
		}
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	REP( i , m){
		Long u , v;
		cin >> u>> v;
		G.addEdge(u - 1, v - 1 , 0);
		G.addEdge(v - 1 , u - 1 , 1);
		
	}
	G.bfs01(0 , n);
	if(G.d[n - 1] == INF) cout << -1 << endl;
	else cout << G.d[n - 1] << endl;
	

	return 0;
}

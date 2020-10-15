#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;
const Long loga = 32 - __builtin_clz(MX);

struct Graph{
	vector<pair<int, Long>> adj [MX];
	pair<Long, Long> st[MX][loga]; //st[i][j] : min/max edge starting at i and ending at anc[i][j]
	int anc[MX][loga]; //anc[i][j] : ancestor of i at distance 2^j
	int depth[MX]; 
	int tIn[MX];
	int tOut[MX];
	int timer;
	
	void clear(int n) {
		for(int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(int u , int v, Long w) {
		adj[u].push_back({v , w});
		adj[v].push_back({u , w});
	}
	
	void dfs(int u = 0){ //O(n)
		tIn[u] = timer++;
		for(auto e : adj[u]){
			int v = e.first;
			Long w = e.second;
			if(anc[u][0] != v){
				anc[v][0] = u;
				st[v][0] = {w, w};
				depth[v] = depth[u] + 1;
				dfs(v);
			}
		}
		tOut[u] = timer++;
	}
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return {min(a.first,b.first) , max(a.second, b.second)}; 
	}
	
	
	void precalculate(Long n, Long root = 0){ //O(nlogn)
		anc[root][0] = -1;
		depth[root] = 0;
		timer = 0;
		dfs(root);
		
		for(int j = 1; (1 << j) < n; j++){
			for(int i = 0; i < n; i++){
				if(anc[i][j - 1] != -1){
					anc[i][j] = anc[anc[i][j - 1]][j - 1];
					st[i][j] = f(st[i][j - 1],st[anc[i][j - 1]][j - 1]);
				} else {
					anc[i][j] = -1;
				}
			}
		}
	}
	
	bool isAncestor(int u, int v){ //is u ancestor of v ?
		return tIn[u] <= tIn[v] && tOut[u] >= tOut[v];
	}	
	
	pair<Long,Long> lift(int u, int v) { //O(log n)
		//lift vertex u to the lca(u , v)
		pair<Long, Long> ans = {INF, -INF};;
		int bits = 31 - __builtin_clz(depth[u]);
		if (!isAncestor(u , v)) {
			for (int i = bits; i >= 0; i--) {
				if (anc[u][i] != -1 && !isAncestor(anc[u][i] , v)) {
					ans = f(ans , st[u][i]); 
					u = anc[u][i];
				}
			} 
			ans = f(ans , st[u][0]);
			u = anc[u][0];
		}
		return ans;
	}
	
	pair<Long,Long> query(Long u, Long v){ //O(logn) <min, max>
		return f(lift(u ,v), lift(v, u));
	}
} G;

int main() {
	return 0;
}



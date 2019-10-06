#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;
const Long loga = log2(MX)+1;

struct Graph{
	vector<Long> adj [MX];
	vector<Long> cost[MX];
	
	Long anc[MX][loga]; //anc[i][j] : ancestor of i at distance 2^j
	Long height[MX]; 
	pair<Long,Long> st[MX][loga]; //st[i][j] : min/max edge starting at i and ending at anc[i][j]
	int tIn[MX];
	int tOut[MX];
	int timer = 0;
	
	void clear(Long N) {
		for(Long i = 0; i < N; i++) {
			adj[i].clear();
			cost[i].clear();
		}
		timer = 0;
	}
	
	void addEdge(Long u , Long v, Long w) {
		adj[u].push_back(v);
		adj[v].push_back(u);
		cost[u].push_back(w);
		cost[v].push_back(w);
	}
	
	void dfs(Long u = 0){ //O(n+m)
		tIn[u] = timer++;

		for ( Long i = 0; i < adj[u].size(); i++) {
			Long v = adj[u][i];
			Long w = cost[u][i];
			if(anc[u][0] != v){
				anc[v][0] = u;
				st[v][0] = {w, w};
				height[v] = height[u] + 1;
				dfs(v);
			}
		}
		tOut[u] = timer++;
	}
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return {min(a.first,b.first) , max(a.second, b.second)}; 
	}
	
	
	void precalculate(Long N, Long root = 0){ //O(nlogn)
		anc[root][0] = -1;
		height[root] = 0;
		dfs(root);
		
		for(int j = 1; (1 << j) < N; j++){
			for(int i = 0; i < N; i++){
				if(anc[i][j-1] != -1){
					anc[i][j] = anc[anc[i][j-1]][j-1];
					st[i][j] = f(st[i][j-1],st[anc[i][j-1]][j-1]);
				} else {
					anc[i][j] = -1;
				}
			}
		}
	}
	
	pair<Long,Long> bestOnPath(Long u, Long v){ //O(logn) <min, max>
		if(height[u] < height[v]){
			swap(u,v);
		}
		int lg = 31 - (__builtin_clz(height[u]));
		
		pair<Long,Long> bestU,bestV;
		bestU = bestV = {INF, -INF}; //cambiar para min
		for(Long i = lg; i >= 0; i--){
			if(height[u] - (1 << i) >= height[v]){
				bestU = f(bestU,st[u][i]);
				u = anc[u][i];
			}
		}
		
		if(u == v){
			return bestU;
		}
		
		for(int i = lg; i >= 0; i--){
			if(anc[u][i] != anc[v][i]){
				bestU = f(bestU,st[u][i]);
				bestV = f(bestV,st[v][i]);
				u = anc[u][i], v = anc[v][i];
			}
		}
		bestU = f(bestU , st[u][0]);
		bestV = f(bestV , st[v][0]); 
		return f( bestU, bestV );
	}
	
	bool isAncestor(Long u, Long v){ //is u ancestor of v ?
		return tIn[u] < tIn[v] && tOut[u] > tOut[v];
	}	
} G;

int main() {
	return 0;
}



#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MAX = 2e5;
const Long loga = 18;

struct Graph {
	vector<int> adj[MAX];
	int anc[MAX][loga];
	int height[MAX];
	int tIn[MAX];
	int tOut[MAX];
	int timer = 0;
	
	void addEdge(int u , int v){
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void dfs(int u = 0){ //O(n+m)
		tIn[u] = timer++;
		for ( int v : adj[u] ) {
			if(anc[u][0] != v){
				anc[v][0] = u;
				height[v] = height[u] + 1;
				dfs(v);
			}
		}
		tOut[u] = timer++;
	}

	void precalculate(int N, int root = 0){ //O(nlogn)
		anc[root][0] = -1;
		dfs(root);
		for(int j = 1; (1 << j) < N; j++){
			for(int i = 0; i < N; i++){
				if(anc[i][j-1] != -1){
					anc[i][j] = anc[anc[i][j-1]][j-1];
				} else {
					anc[i][j] = -1;
				}
			}
		}
	}
	
	int lca(int u, int v){ //O(logn)
		if(height[u] < height[v]){
			swap(u,v);
		}
		int lg = 31 - (__builtin_clz(height[u]));
		for(int i = lg; i >= 0; i--){
			if(height[u] - (1 << i) >= height[v]){
				u = anc[u][i];
			}
		}
		
		if(u == v){
			return u;
		}
		for(int i = lg; i >= 0; i--){
			if(anc[u][i] != anc[v][i]){
				u = anc[u][i], v = anc[v][i];
			}
		}
		return anc[u][0];
	}
	
	bool isAncestor(Long u, Long v){ //is u ancestor of v ?
		return tIn[u] < tIn[v] && tOut[u] > tOut[v];
	}	
	Long query(Long r , Long u , Long v){
		r--;
		u--;
		v--;
		Long x = lca(u , v);
		Long y = lca(r , u);
		Long z = lca(r, v);
		if(isAncestor(y , x)){
			return x + 1;
		}
		if(y == x ) {
			return z + 1;
		}
		return y + 1;
	}	
} G;


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long N;
	cin >> N;
	for(Long i = 0; i < N - 1; i++){
		Long u , v;
		cin >> u >> v;
		G.addEdge(u , v);
	}
	G.precalculate(N);

	Long Q;
	cin >> Q;
	for(Long q = 0; q < Q; q++){
		Long r, u , v;
		cin >> r >> u >> v;
		cout << G.query(r, u , v) << "\n";
	} 
	return 0;
}

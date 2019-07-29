#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://www.spoj.com/problems/LCA/
const Long MAX = 1e5;
const Long loga = log2(MAX)+1;

struct Graph {
	vector<int> adj[MAX];
	int anc[MAX][loga]; //anc[i][j] : ancestor of i at distance 2^j
	int height[MAX];
	int tIn[MAX];
	int tOut[MAX];
	Long inDegree[MAX];
	int timer = 0;
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
			inDegree[i] = 0;
		}
		timer = 0;
	}
	
	void addEdge(int u , int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
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
	
	Long getRoot(Long n) {
		REP(i , n){
			if(inDegree[i] == 0) return i;
		}
		return -1;
	}
	void precalculate(int N, int root = 0){ //O(nlogn)
		anc[root][0] = -1;
		height[root] = 0;
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
} G;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t , T){
		cout << "Case " << t + 1 << ":\n";
		Long n;
		cin >> n;
		G.clear(n);
		REP(u , n){
			Long k;
			cin >> k;
			REP( j ,k){
				Long v;
				cin >> v;
				v--;
				G.addEdge(u , v);
			}
		}
		G.precalculate(n, G.getRoot(n));
		Long q;
		cin >> q;
		REP(i , q){
			Long u ,v;
			cin >> u >> v;
			u--, v--;
			cout << G.lca( u ,v) + 1 << "\n";
		}
	}
	
	return 0;
}

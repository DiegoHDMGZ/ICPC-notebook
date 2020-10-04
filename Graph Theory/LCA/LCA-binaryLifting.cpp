#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long loga = 32 - __builtin_clz(MX);

struct Graph {
	vector<int> adj[MX];
	int depth[MX];
	int tIn[MX];
	int tOut[MX];
	int timer;
	int anc[MX][loga];
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
		}
	}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int u) {
		tIn[u] = timer++;
		for (int v : adj[u]) {
			if (v != anc[u][0]) {
				anc[v][0] = u;
				depth[v] = depth[u] + 1;
				dfs(v);
			}
		}
		tOut[u] = timer++;
	}
	
	void precalculate(int n, int root = 0){ //O(n log n)
		anc[root][0] = -1;
		depth[root] = 0;
		timer = 0;
		dfs(root);
		for (int j = 1; (1 << j) < n; j++){
			for(int i = 0; i < n; i++){
				if(anc[i][j-1] != -1){
					anc[i][j] = anc[anc[i][j-1]][j-1];
				} else {
					anc[i][j] = -1;
				}
			}
		}
	}
	
	bool isAncestor(int u, int v){ //is u ancestor of v ?
		return tIn[u] <= tIn[v] && tOut[u] >= tOut[v];
	}	
	
	int lca(int u, int v) { //O(log n)
		/*if (depth[u] > depth[v]) {
			swap(u , v);
		}*/
		if (isAncestor(u , v)) {
			return u;
		}
		int bits = 31 - __builtin_clz(depth[u]);
		for (int i = bits; i >= 0; i--) {
			if (anc[u][i] != -1 && !isAncestor(anc[u][i] , v)) {
				u = anc[u][i];
			}
		} 
		return anc[u][0];
	}
	
	bool onPath(int A, int B, int C) { //is C on AB path ?
		int x = lca(A , B); 
		if(C == x) {
			return true;
		}
		if(isAncestor(x , C) && isAncestor(C, A)) {
			return true;
		}
		if(isAncestor(x , C)  && isAncestor(C, B)) {
			return true;
		}
		return false;
	}
} G;

int main(){
	return 0;
}

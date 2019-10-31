#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long loga = log2(MX)+1;

struct Graph {
	vector<int> adj[MX];
	int anc[MX][loga]; //anc[i][j] : ancestor of i at distance 2^j
	int height[MX];
	int tIn[MX];
	int tOut[MX];
	int timer = 0;
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
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

	void precalculate(int n, int root = 0){ //O(nlogn)
		anc[root][0] = -1;
		height[root] = 0;
		dfs(root);
		for(int j = 1; (1 << j) < n; j++){
			for(int i = 0; i < n; i++){
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

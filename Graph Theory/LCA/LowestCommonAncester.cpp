#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;
const Long loga = log2(MAX)+1;

struct Graph {
	Long anc[MAX][loga];
	Long T[MAX], L[MAX]; // T[root]= -1 , iniciar L[ ] en -1
	vector<Long> adj[MAX];
	
	void clear(Long N = MAX) { //mandatory
		REP(i , N) {
			adj[i].clear();
			L[i] = -1;
			T[i] = -1;
		}
	}
	
	
	void dfs(Long u, Long nivel){ //O(n+m)
		L[u] = nivel;
		for ( Long v : adj[u] ) {
			if(L[v] == -1){
				T[v] = u;
				dfs(v,nivel+1);
			}
		}
	}

	void precalculate(Long N){ //O(nlogn)
		REP ( i , N) {
			for(Long j = 0; (1LL << j) < N; j++){
				anc[i][j] = -1;
			}	
		}
		
		for(Long i = 0; i < N; i++){
			anc[i][0] = T[i];
		}
		
		for(Long j = 1; (1LL << j) < N; j++){
			for(Long i = 0; i < N; i++){
				if(anc[i][j-1] != -1){
					anc[i][j] = anc[anc[i][j-1]][j-1];
				}
			}
		}
	}
	
	Long lca(Long u, Long v){ //O(logn)
		if(L[u] < L[v]){
			swap(u,v);
		}
		
		Long lg = 31 - (__builtin_clz(L[u]));
		
		for(Long i = lg; i >= 0; i--){
			if(L[u] - (1 << i) >= L[v]){
				u = anc[u][i];
			}
		}
		
		if(u == v){
			return u;
		}
		
		for(Long i = lg; i >= 0; i--){
			if(anc[u][i] != -1 && anc[u][i] != anc[v][i]){
				u = anc[u][i], v = anc[v][i];
			}
		}
		return T[u];
	}
		
} G;

int main(){
	return 0;
}

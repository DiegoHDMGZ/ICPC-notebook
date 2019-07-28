#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;
const Long LIM = 0;
const Long loga = log2(MAX)+1;

struct Graph{
	vector<Long> adj [MAX];
	vector<Long> cost[MAX];
	
	Long p[MAX];
	Long pPeso[MAX];
	Long anc[MAX][loga];
	Long L[MAX]; // iniciar L[ ] en -1
	Long st[MAX][loga];
	
	void clean(Long N) {
		REP(i , N) {
			adj[i].clear();
			cost[i].clear();
			p[i] = -1;
			L[i] = -1;
		}
	}
	
	void addEdge(Long u , Long v, Long w) {
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
		cost[u].pb(w);
		cost[v].pb(w);
	}
	
	void dfs(Long u, Long nivel){ //O(n + m)
		L[u] = nivel;
		Long i = 0;
		for(Long v : adj[u] ) {
			if(L[v] == -1){
				dfs(v , nivel + 1);
				p[v] = u;
				pPeso[v] = cost[u][i];
			}
			i++;
		}
	}
	
	Long f(Long a, Long b){
		return max(a,b); //cambiar para min
	}
	
	void precalculate(Long root, Long N){ //O(nlogn)
		fill(L, L+ MAX , -1);
		dfs(root,0);
		
		REP(i, N){
			for(Long j = 0; (1LL << j) < N; j++){
				anc[i][j] = -1;
			}	
		}
		
		for(Long i = 0; i < N; i++){
			anc[i][0] = p[i];
			st[i][0] = pPeso[i];
		}
		
		for(Long j = 1; (1LL << j) < N; j++){
			for(Long i = 0; i < N; i++){
				if(anc[i][j-1] != -1){
					anc[i][j] = anc[anc[i][j-1]][j-1];
					st[i][j] = f(st[i][j-1],st[anc[i][j-1]][j-1]);
				}
			}
		}
	}
	
	Long maxOnPath(Long u, Long v){ //O(logn)
		if(L[u] < L[v]){
			swap(u,v);
		}
		
		Long lg = 31 - (__builtin_clz(L[u]));
		
		Long maxU,maxV;
		maxU = maxV = LIM; //cambiar para min
		for(Long i = lg; i >= 0; i--){
			if(L[u] - (1LL << i) >= L[v]){
	
				maxU = f(maxU,st[u][i]);
	
				u = anc[u][i];
			
			}
		}
		
		if(u == v){
			return maxU;
		}
		
		for(int i = lg; i >= 0; i--){
			if(anc[u][i] != -1 && anc[u][i] != anc[v][i]){
				maxU = f(maxU,st[u][i]);
				maxV = f(maxV,st[v][i]);
				u = anc[u][i], v = anc[v][i];
			}
		}
		return f( f(maxU,maxV) , f(pPeso[u],pPeso[v]) );
	}
} G;

int main() {
	return 0;
}



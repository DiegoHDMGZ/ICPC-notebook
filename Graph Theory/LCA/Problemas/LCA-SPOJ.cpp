#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MAX = 1e5;
const Long loga = log2(MAX)+1;

struct Graph {
	Long anc[MAX][loga];
	Long T[MAX], L[MAX];
	vector<Long> adj[MAX];
	
	void clear(Long N = MAX) { 
		REP(i , N) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v){
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	
	void dfs(Long u = 0, Long nivel = 0){ //O(n+m)
		L[u] = nivel;
		for ( Long v : adj[u] ) {
			if(L[v] == -1){
				T[v] = u;
				anc[v][0] = u;
				dfs(v,nivel+1);
			}
		}
	}

	void precalculate(Long N){ //O(nlogn)
		
		REP ( i , N) {
			for(Long j = 0; (1LL << j) < N; j++){
				anc[i][j] = -1;
			}	
			T[i] = L[i] = -1;
		}
		dfs();
		
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
			if(L[u] - (1LL << i) >= L[v]){
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
		G.precalculate(n);
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

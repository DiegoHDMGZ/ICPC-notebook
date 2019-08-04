#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://www.spoj.com/problems/LCA/
const Long MAX = 1e5;
const Long loga = log2(MAX)+1;

struct SparseTable{
	pair<Long,Long> st[2 *MAX][loga + 1]; //<min height , node>
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return min(a , b);
	}

	pair<Long,Long> f(pair<Long,Long> a){
		return a;
	}
	
	void build(vector<pair<Long,Long>> &A){ // O(n log n)
		Long n = A.size();
		for(Long i = 0; i < n; i++){
			st[i][0] = f(A[i]);
		}
		
		for(Long j = 1; (1 << j) <= n; j++){
			for(Long i = 0; i + (1 << j) <= n; i++){
				st[i][j] = f(st[i][j-1], st[i + (1 << (j-1))][j-1]);
			}
		}
	}
	
	Long query(Long L, Long R){ //O(1)
		Long T = R - L + 1;
		Long lg = 31 - (__builtin_clz(T));
		return f(st[L][lg], st[R- (1LL << lg) + 1][lg]).second;
	}
	
}st;

struct Graph {
	vector<Long> adj[MAX];
	vector<pair<Long,Long>> euler;
	Long first[MAX];
	Long height[MAX];
	Long tIn[MAX];
	Long tOut[MAX];
	Long timer = 0;
	Long inDegree[MAX];
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
			inDegree[i] = 0;
		}
		euler.clear();
		timer = 0;
	}
	
	void addEdge(Long u , Long v){
		adj[u].push_back(v);
		adj[v].push_back(u);
		inDegree[v]++;
	}
	
	Long getRoot(Long n){
		for(Long i = 0; i < n; i++){
			if(inDegree[i] == 0) return i;
		}
		return -1;
	}
	
	void dfs(Long u = 0, Long p = -1){ //O(n+m)
		tIn[u] = timer++;
		first[u] = euler.size();
		euler.push_back({height[u], u });
		for ( Long v : adj[u] ) {
			if(p != v){
				height[v] = height[u] + 1;
				dfs(v , u);
				euler.push_back({height[u], u});
			}
		}
		tOut[u] = timer++;
	}

	void precalculate(Long N, Long root = 0){ //O(nlogn)
		height[root] = 0;
		dfs(root);
		st.build(euler);
	}
	
	Long lca(Long u, Long v){ //O(logn)
		return st.query(min(first[u] , first[v]) , max(first[u]  , first[v]));
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
		G.precalculate(n , G.getRoot(n));
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
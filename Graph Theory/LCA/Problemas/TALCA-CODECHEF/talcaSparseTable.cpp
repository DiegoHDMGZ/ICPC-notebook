#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://www.codechef.com/problems/TALCA
const Long MAX = 2e5;
const Long loga = 18;
struct SparseTable{
	pair<Long,Long> st[2 * MAX][loga + 1]; //<min height , node>
	
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
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
		}
		euler.clear();
		timer = 0;
	}
	
	void addEdge(Long u , Long v){
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
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
		return st.query(min(first[u] , first[v]) , max(first[u] , first[v]));
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
	//probando el clear
	for(Long i = 0; i < N - 1; i++){
		G.addEdge(i + 1 , i + 2);
	}
	G.precalculate(N);
	G.clear(N); //
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

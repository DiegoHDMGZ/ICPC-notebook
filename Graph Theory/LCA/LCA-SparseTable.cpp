#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long loga = 32 - __builtin_clz(MX);

struct SparseTable{
	pair<Long,Long> st[2 * MX][loga + 1]; //<min height , node>
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return min(a , b);
	}
	
	void build(vector<pair<Long,Long>> &A){ // O(n log n)
		Long n = A.size();
		for(Long i = 0; i < n; i++){
			st[i][0] = A[i];
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
	vector<Long> adj[MX];
	vector<pair<Long,Long>> euler;
	Long first[MX];
	Long height[MX];
	Long tIn[MX];
	Long tOut[MX];
	Long timer = 0;
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
		}
		euler.clear();
		timer = 0;
	}
	
	void addEdge(Long u , Long v){
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

	void precalculate( Long root = 0){ //O(nlogn)
		height[root] = 0;
		dfs(root);
		st.build(euler);
	}
	
	Long lca(Long u, Long v){ //O(1)
		return st.query(min(first[u] , first[v]) , max(first[u] , first[v]));
	}
	
	bool isAncestor(Long u, Long v){ //is u ancestor of v ?
		return tIn[u] <= tIn[v] && tOut[u] >= tOut[v];
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

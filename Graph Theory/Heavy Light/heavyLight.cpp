#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://cp-algorithms.com/graph/hld.html

//With weight on edges, put the weight in the node with greater depth and add one line to query function

const Long MX = 1e5;
Long segmentTreeQuery(Long pos1 , Long pos2) { 
	return 0;
}

struct Graph {
	vector <Long> adj[MX];
	Long parent[MX];
	Long depth[MX];
	Long heavy[MX];
	Long head[MX];
	Long pos[MX];
	Long curPos = 0;
	
	void clear(Long N = MX) { //O(N)
		REP( i , N) {
			adj[i].clear();
			parent[i] = -1;
			heavy[i] = -1;
			depth[i] = head[i] = pos[i] = 0;
		}
		curPos = 0;
	}
	
	void addEdge(Long u, Long v) { //O(1)
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	Long dfs(Long u = 0){ //O(N + M)
		Long sz = 1;
		Long maxSize = 0;
		heavy[u] = -1;
		for(Long v : adj[u]){
			if(v != parent[u]) {
				parent[v] = u;
				depth[v] = depth[u] + 1;
				Long szV = dfs(v);
				sz += szV;
				if(szV > maxSize) {
					maxSize = szV;
					heavy[u] = v;
				}
			}
		}
		
		return sz;
	}
	
	void decompose(Long u , Long h ) { //O(N + M)
		head[u] = h;
		pos[u] = curPos++;
		if(heavy[u] != -1) {
			decompose(heavy[u] , h);
		}
		
		for(Long v : adj[u]) {
			if(v != parent[u] && v != heavy[u] ) {
				decompose(v , v);
			}
		}
	}
	
	void build(Long root = 0){
		curPos = 0;
		depth[root] = 0;
		parent[root] = -1;
		dfs(root);
		decompose(root , root);
	}
	
	Long query(Long u , Long v) {	//O( O( data query) log N)
		Long ans = 0;
		
		while(head[u] != head[v]) {
			if(depth[head[u]] > depth[head[v]]) {
				swap(u , v);
			}
			
			Long curHeavyMax = segmentTreeQuery(pos[head[v]], pos[v]);
			ans = max(ans , curHeavyMax);
			
			v = parent[head[v]];
		}
		
		if(depth[u] > depth[v]) {
			swap(u , v);
		}
		
		//u = heavy[u]; //when weight are on edges
		
		//last heavy path
		Long lastMax = segmentTreeQuery(pos[u], pos[v]);
		ans = max(ans, lastMax);
		return ans;
	}
} G;

int main() {
	return 0;
}


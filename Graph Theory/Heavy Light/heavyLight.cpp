#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;
Long segmentTreeQuery(Long pos1 , Long pos2) { 
	return 0;
}

struct Graph {
	vector <Long> adj[MAX];
	Long parent[MAX];
	Long depth[MAX];
	Long heavy[MAX];
	Long head[MAX];
	Long pos[MAX];
	
	void clear(Long N = MAX) { //O(N)
		REP( i , N) {
			adj[i].clear();
			parent[i] = -1;
			heavy[i] = -1;
			depth[i] = head[i] = pos[i] = 0;
		}
	}
	
	void addEdge(Long u, Long v) { //O(1)
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	Long dfs(Long u = 0){ //O(N + M)
		Long sz = 1;
		Long maxSize = 0;
		
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
	
	Long curPos = 0;
	
	Long decompose(Long u = 0, Long h = 0) { //O(N + M)
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
		//last heavy path
		
		Long lastMax = segmentTreeQuery(pos[u], pos[v]);
		ans = max(ans, lastMax);
		return ans;
	}
} G;

int main() {
	G.dfs();
	G.decompose();
	return 0;
}


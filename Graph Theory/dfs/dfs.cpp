#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;
const Long MX = 1e5;

struct Graph {
	vector <Long> adj[MX];
	bool vis[MX];
	Long tIn[MX];
	Long tOut[MX];
	Long timer = 0;
	
	void clear(Long n) {
		for (Long i = 0; i < n; i++) {
			adj[i].clear();
			vis[i] = false;
			tIn[i] = tOut[i] = 0;
		}
		timer = 0;
	}
	
	void addEdge(Long u, Long v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(Long u) { //O(V + E)
		vis[u] = true;
		tIn[u] = ++timer;
		for (Long v : adj[u]) {
			if(!vis[v]){
				dfs(v); //tree edge
			} else if(tOut[v] == 0){
				//back edge
			} else if(tIn[u] < tIn[v]){
				//forward edge
			} else {
				//cross edge
			}
		}
		tOut[u] = ++timer;
	}
} G;

int main() {
	return 0;
}

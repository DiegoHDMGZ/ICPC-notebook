#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef int Cap;
const int MX = 3000;

struct GraphFlow {
	//max flow template
	//Use 2 * MX + 2 for the array sizes
	void clear(int n);
	void addEdge(int u, int v, Cap w, bool dir);
	Cap maxFlow(int s, int t, int n);
} GFlow;

struct Graph{
	vector<int> adj[MX];
	bool vis[MX];
	void clear(int n) {
		for (int i = 0; i < n ; i++) adj[i].clear();
		GFlow.clear(2 * n + 2);
	}
	
	void addEdge(int u, int v){
		adj[u].push_back(v);
	}
	
	int left(int u) {return 2 * u;}
	int right(int u) {return 2 * u + 1;}
	
	vector<int> nodes;
	void dfs(int u) {
		vis[u] = true;
		nodes.push_back(u);
		for (int v : adj[u]) {
			if (!vis[v]) dfs(v);
		}
	}
	
	int maxAntiChain(int n) {
		//O(V ^ 5/2) - could be less depending on E in Flow Graph
		//We build all the transitive edges
		int s = 2 * n;
		int t = 2 * n + 1;
		for (int u = 0; u < n; u++) {
			GFlow.addEdge(s, left(u), 1, true);
			GFlow.addEdge(right(u), t, 1, true);
			nodes.clear();
			dfs(u);
			for (int v : nodes) {
				vis[v] = false;
				if (u == v) continue;
				GFlow.addEdge(left(u), right(v), 1, true);
			} 
		}
		return n - GFlow.maxFlow(s, t, t + 1);
	}
}G; 

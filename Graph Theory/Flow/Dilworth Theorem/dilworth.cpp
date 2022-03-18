#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 3000;
const Long INF = 1e18;

struct GraphFlow {
	//max flow template
	void clear(int n);
	void addEdge(int u, int v, Long w, bool dir);
	Long maxFlow(int s, int t, int n);
} GFlow;

struct Graph{
	vector<int> adj[MX];
	int indegree[MX];
	set<int> parents[MX];
	
	void clear(int n) {
		for (int i = 0; i < n ; i++) {
			adj[i].clear();
			indegree[i] = 0;
			parents[i].clear();
		}
		GFlow.clear(2 * n + 2);
	}
	
	void addEdge(int u, int v){
		adj[u].push_back(v);
		indegree[v]++;
	}
	
	int maxAntiChain(int n) {
		//O(V ^ 5/2) - could be less depending on E in Flow Graph
		//We build all the transitive edges using toposort
		int s = 0;
		int t = 2 * n + 1;
		deque<int> q;
		for (int u = 0; u < n; u++) {
			if (indegree[u] == 0) q.push_back(u);
		}
		int cnt = 0;
		while (!q.empty()){
			int u = q.front();
			cnt++;
			GFlow.addEdge(s, u + 1, 1, true);
			GFlow.addEdge(u + 1 + n, t, 1, true);
			q.pop_front();
			for (int p : parents[u]) {
				GFlow.addEdge(p + 1, u + 1 + n, 1, true);
			}
			for (int v : adj[u]) {
				indegree[v]--;
				if (indegree[v] == 0) q.push_back(v);
				for (int p : parents[u]) parents[v].insert(p);
				parents[v].insert(u);
			}
		}
		assert(n == cnt); //should be a DAG
		return cnt - GFlow.maxFlow(s, t, t + 1);
	}
}G; 

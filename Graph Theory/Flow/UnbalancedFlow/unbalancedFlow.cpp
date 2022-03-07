#include <bits/stdc++.h>
using namespace std;

/*
Find maximum feasible (s-t) flow in a graph G(V, E)
such that l(e) <= f(e) <= c(e) for each e in E
and sum(flow out u) - sum(flow in u) = balance[u] for each u in V 

Balances are 0 by default, set its value before adding edges

It can also be easily modified to find the minimum feasible flow
*/

typedef long long Cap;

const int MX = 1e5;
const Cap INF = 1e18;

struct Edge {
	int to;
	Cap flow, cap;
	int rev; //index of the backward edge in the adj list of to
	Cap extraFlow;
	Edge(int to, Cap cap, Cap extraFlow, int rev): 
		to(to), flow(0), cap(cap), extraFlow(extraFlow), rev(rev) {}
};

struct Graph {
	vector<Edge> adj[MX];  
	int level[MX];
	int nextEdge[MX];
	int balance[MX];
	
	void clear(int n) {
		n += 3;
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			balance[i] = 0;
		}	
	}
	
	void addEdge(int u, int v, Cap L, Cap R, bool dir) {
		if (R < 0) {
			addEdge(v, u, -L, -R, dir);
			return;
		} else if (L < 0) {
			addEdge(u, v, 0, R, dir);
			addEdge(v, u, 0, -L, dir);
			return;
		} 
		adj[u].push_back(Edge(v, R - L, L, adj[v].size()));
		adj[v].push_back(Edge(u, 0, -L, adj[u].size() - 1));
		if (u == v) adj[u].end()[-2].rev++;
		balance[u] -= L;
		balance[v] += L;
		if (!dir) addEdge(u, v, L, R, true);
	}
	
	//******** Dinic's Algorithm ******** 	
	Cap maxNormalFlow(int s, int t, int n);
	
	//******** End Dinic's Algorithm ******** 
	
	bool findFeasibleFlow(int n, bool addExtraFlow) {
		//Assumption: All nodes are between [0... n - 1]
		//Same complexity as Dinic's algorithm
		int s = n;
		int t = n + 1;
		Cap target = 0;
		Cap sumBalance = 0;
		for (int u = 0; u < n; u++) {
			sumBalance += balance[u];
			if (balance[u] > 0) {
				addEdge(s, u, 0, balance[u], true);
				target += balance[u];
			} else if (balance[u] < 0) {
				addEdge(u, t, 0, -balance[u], true);
			}
		}
		bool ok = maxNormalFlow(s, t, n + 2) == target;
		ok &= (sumBalance == 0);
		for (int u = 0; u < n; u++) {
			if (balance[u] != 0) adj[u].pop_back();
			if (addExtraFlow) {
				for (Edge &e: adj[u]) e.flow += e.extraFlow;
			}
		}
		return ok;
	}
	
	Cap maxUnbalancedFlow(int s, int t, int n) {
		//Same complexity as Dinic's algorithm
		//If not solution exists, it returns -1
		Cap sumBalance = 0;
		for (int u = 0; u < n; u++) {
			if (u == s || u == t) continue;
			sumBalance += balance[u];
		}
		int z = n;
		balance[s] = balance[t] = 0;
		balance[z] = -sumBalance;
		addEdge(t, z, 0, INF - 1, true);
		addEdge(z, s, 0, INF - 1, true);
		if (!findFeasibleFlow(n + 1, false)) return -1;
		adj[t].pop_back();
		adj[s].pop_back();
		maxNormalFlow(s, t, n);
		//maxNormalFlow(t, s, n); to find min flow instead
		Cap flow = 0;
		for (int u = 0; u < n; u++) {
			for (Edge &e: adj[u]) {
				e.flow += e.extraFlow;
				if (u == s) flow += e.flow;
			}
		}
		return flow;
	}
} G;

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Solve AND(x_i or/xor y_i)
*/
struct TwoSat {
	vector<vector<int>> adj;
	vector<vector<int>> rev;
	vector<bool> vis;
	vector<int> order, scc;
	int numComponent;
	
	TwoSat(int n) {
		adj.resize(2 * n);
		rev.resize(2 * n);
	}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		rev[v].push_back(u);
	}
	
	void addOr(int x1, bool nega1, int x2, bool nega2) {
		//xi -> 2xi
		//-xi -> 2xi + 1
		addEdge(2 * x1 + !nega1, 2 * x2 + nega2);
		addEdge(2 * x2 + !nega2, 2 * x1 + nega1);
	}
	
	void addXor(int x1, bool nega1, int x2, bool nega2) {
		addOr(x1, nega1, x2, nega2);
		addOr(x1, !nega1, x2, !nega2);
	} 
	
	void dfs(int u) { //O(V + E)
		vis[u] = true;
		for (int v : adj[u]) {
			if (!vis[v]) dfs(v);
		}
		order.push_back(u);
	}
	
	void findComponent(int u) { //O(V + E)
		scc[u] = numComponent;
		for (int v : rev[u]) {
			if (scc[v] == -1) findComponent(v);
		}
	}
	
	vector<bool> solve(int n) { //O(V + E)
		n *= 2;
		order.clear();
		numComponent = 0;
		vis.resize(n, false);
		scc.resize(n, -1);
		for (int u = 0; u < n; u++) {
			if (!vis[u]) dfs(u);
		}
		for (int i = 0; i < n; i++) {
			int u = order[n - 1 - i];
			if (scc[u] == -1) {
				findComponent(u);
				numComponent++;
			}
		}
		vector<bool> assignment(n / 2);
		for (int i = 0; i < n; i += 2) {
			if (scc[i] == scc[i + 1]) return {};
			assignment[i / 2] = scc[i] > scc[i + 1];
		}
		return assignment;
	}
};

int main() {
	return 0;
}

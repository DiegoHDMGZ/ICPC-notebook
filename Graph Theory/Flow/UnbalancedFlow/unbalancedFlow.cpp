#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Find feasible / maximum flow in a graph G(V, E)
such that l(e) <= f(e) <= c(e) for each e in E
and sum(flow out u) - sum(flow in u) = balance[u] for each u in V 

Balances are 0 by default, set its value before adding edges
*/

const int MX = 1e5;
const Long INF = 1e18;

struct Edge{
	int from, to;
	Long flow, cap;
	Long extraFlow;
	int rev; //index of the backward edge in the adj list of to
	Edge(int from, int to, Long cap, Long extraFlow, int rev): 
		from(from), to(to), cap(cap), flow(0), extraFlow(extraFlow), rev(rev) {}
};

struct Graph{
	vector<Edge> adj[MX];  
	int level[MX];
	int nextEdge[MX];
	int balance[MX];
	
	void clear(int n) {
		n += 3;
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			balance[i] = 0;
		}	
	}
	
	void addEdge(int u, int v, Long L, Long R, bool dir) {
		if (R < 0) {
			addEdge(v, u, -L, -R, dir);
			return;
		} else if (L < 0) {
			addEdge(u, v, 0, R, dir);
			addEdge(v, u, 0, -L, dir);
			return;
		} 
		Edge forward(u, v, R - L, L, adj[v].size());
		Edge backward(v, u, 0, -L, adj[u].size());
		balance[u] -= L;
		balance[v] += L;
		adj[u].push_back(forward);
		adj[v].push_back(backward);
		if (!dir) addEdge(u, v, L, R, true);
	}
	
	Long dfs(int u, int t, Long f) { 
		if(u == t) return f;
		for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
			Edge &e = adj[u][i];
			int v = e.to;
			Edge &rev = adj[v][e.rev];
			Long cf = e.cap - e.flow;
			if (cf == 0 || level[v] != level[u] + 1) continue;
			Long ret = dfs(v, t, min(f, cf));
			if (ret > 0) {
				e.flow += ret;
				rev.flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	bool bfs(int s, int t) { //O(E)
		deque<int> q; 
		q.push_back(s);
		level[s] = 0;
		while (!q.empty()) {
			int u = q.front();
			nextEdge[u] = 0;
			q.pop_front();
			if (u == t) return true;
			for (Edge e : adj[u]) {
				int v = e.to;
				Long cf = e.cap - e.flow;
				if (level[v] == -1 && cf > 0) {
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return false;
	}
	
	Long maxNormalFlow(int s, int t, int n) {
		//Dinic's algorithm
		Long ans = 0;
		while (true) { 
			fill(level, level + n, -1);
			if (!bfs(s, t)) break;
			Long inc;
			do{
				inc = dfs(s, t, INF);
				ans += inc;
			} while (inc > 0);
		}
		return ans;
	}
	
	bool findFeasibleFlow(int n, bool addExtraFlow) {
		//Assumption: All nodes are between [0... n - 1]
		//Same complexity as Dinic's algorithm
		int s = n;
		int t = n + 1;
		Long target = 0;
		Long sumBalance = 0;
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
	
	Long maxUnbalancedFlow(int s, int t, int n) {
		//Same complexity as Dinic's algorithm
		//If not solution exists, it returns -1
		Long sumBalance = 0;
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
		Long flow = 0;
		for (int u = 0; u < n; u++) {
			for (Edge &e: adj[u]) {
				e.flow += e.extraFlow;
				if (e.from == s) flow += e.flow;
			}
		}
		return flow;
	}
} G;

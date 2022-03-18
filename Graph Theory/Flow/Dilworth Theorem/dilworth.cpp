#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef int Cap;
const int MX = 3000;

//This template build the entire transitive edges

struct Edge {
	int to;
	Cap flow, cap;
	int rev; //index of the backward edge in the adj list of to
	Edge(int to, Cap cap, int rev): 
		to(to), flow(0), cap(cap), rev(rev) {}
};

struct GraphFlow {
	//max flow template
	//Use 2 * MX + 2 for the array sizes
	vector<Edge> adj[2 * MX + 2];
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
	int getOriginal(int u) {return u / 2;}
	int getSource(int n) {return 2 * n;}
	int getTarget(int n) {return 2 * n + 1;}
	
	vector<int> nodes;
	void dfs(int u) {
		vis[u] = true;
		nodes.push_back(u);
		for (int v : adj[u]) {
			if (!vis[v]) dfs(v);
		}
	}
	
	int maxAntiChainSize(int n) {
		//O(V ^ 5/2) - could be less depending on E in Flow Graph
		int s = getSource(n);
		int t = getTarget(n);
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
	
	vector<vector<int>> getMinChainPartition(int n) {
		//Only usable when maxAntiChainSize has been called before
		vector<int> match(n, -1);
		vector<int> indegree(n);
		for (int u = 0; u < n; u++) {
			for (auto e : GFlow.adj[left(u)]) {
				if (e.flow == 1) {
					int v = getOriginal(e.to);
					indegree[v]++;
					match[u] = v;
				}
			}
		}
		vector<vector<int>> partition;
		for (int u = 0; u < n; u++) {
			if (indegree[u] == 0) {
				vector<int> chain;
				int cur = u;
				while (cur != -1) {
					chain.push_back(cur);
					cur = match[cur];
				}
				partition.push_back(chain);
			}
		}
		return partition;
	}
	
	bool inS[2 * MX + 2];
	void expandCut(int u) {
		inS[u] = true;
		for (auto e : GFlow.adj[u]) {
			if (e.cap - e.flow > 0 && !inS[e.to]) expandCut(e.to);
		}
	}
	
	vector<int> getMaxAntichain(int n) {
		//Only usable when maxAntiChainSize has been called before
		int s = getSource(n);
		int t = getTarget(n);
		expandCut(s);
		vector<bool> cover(n, false);
		for (auto e : GFlow.adj[s]) {
			if (!inS[e.to]) {
				cover[getOriginal(e.to)] = true;
			}
		}
		for (auto e : GFlow.adj[t]) {
			if (inS[e.to]) {
				cover[getOriginal(e.to)] = true;
			}
		}
		vector<int> antichain;
		for (int u = 0; u < n; u++) {
			if (!cover[u]) antichain.push_back(u);
		}
		return antichain;
	}
} G; 

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)

using namespace std;

typedef long long Long;

const int MX = 5000;
const Long INF = 1e18;

struct Edge{
	int from, to;
	Long flow, cap;
	int rev; //index of the backward edge in the adj list of to
	Edge(int from, int to, Long cap, int rev): 
		from(from), to(to), cap(cap), flow(0), rev(rev) {}
};

struct Graph{
	vector<Edge> adj[MX];  
	int level[MX];
	int nextEdge[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		Edge forward(u, v, w, adj[v].size());
		Edge backward(v, u, 0, adj[u].size());
		if (!dir) backward.cap = w;
		adj[u].push_back(forward);
		adj[v].push_back(backward);
	}
	
	Long dfs(int u, int t ,Long f) { 
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
			q.pop_front();
			for (Edge e : adj[u]) {
				int v = e.to;
				Long cf = e.cap - e.flow;
				if (level[v] == -1 && cf > 0) {
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	Long maxFlow(int s, int t, int n) {
		//General: O(E * V^2)
		//Unit Cap: O(E * min(E^(1/2) , V^(2/3)))
		//Unit Network: O(E * V^(1/2))
		//In unit network, all the edges have unit capacity
		//and for any vertex except s and t either the 
		//incoming or outgoing edge is unique.
		Long ans = 0;
		while (true) { //O(V) iterations
			fill(level, level + n, -1);
			if (!bfs(s, t)) break;
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n, 0);
			Long inc;
			do{
				inc = dfs(s, t, INF);
				ans += inc;
			} while (inc > 0);
		}
		return ans;
	}
} G;

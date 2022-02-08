#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 5000;
const Long INF = 1e18;

struct Edge{
	int from, to;
	Long flow, cap;
	Edge(int from, int to, Long cap):
		from(from), to(to), cap(cap), flow(0) {}
};

struct Graph{
	vector<Edge> edges;
	vector<int> adjInd[MX]; 
	//'adjInd' stores the position of the edge in the vector 'edges'
	int parent[MX];
	
	void clear(int n) {
		edges.clear();
		for (int i = 0 ; i < n; i++) {
			adjInd[i].clear();
			parent[i] = -1;
		}
	}
	
	void addEdge(int u, int v, Long w, bool dir) {
		Edge forward(u, v, w);
		Edge backward(v, u, 0);
		adjInd[u].push_back(edges.size());
		edges.push_back(forward);
		adjInd[v].push_back(edges.size());
		edges.push_back(backward);
		if (!dir) addEdge(v, u, w, true);
	}
	
	void pushFlow(int s, int t, Long inc) {
		int v = t;
		while (v != s) {
			int ind = parent[v];
			Edge &e = edges[ind];
			Edge &rev = edges[ind ^ 1];
			e.flow += inc;
			rev.flow -= inc;
			v = e.from;
		}
	}
	
	Long bfs(int s, int t) { //O(E)
		deque<pair<int, Long>> q; //<node, flow>
		q.push_back({s, INF});
		parent[s] = -2;
		while (!q.empty()) {
			int u = q.front().first;
			Long curFlow = q.front().second;
			q.pop_front();
			if (u == t) {
				pushFlow(s, t, curFlow);
				return curFlow;
			}
			for (int ind : adjInd[u]){
				auto e = edges[ind];
				int v = e.to;
				Long cf = e.cap - e.flow;
				if (parent[v] == -1 && cf > 0) {
					parent[v] = ind;
					Long newFlow = min(curFlow, cf);
					q.push_back({v, newFlow});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(int s, int t, int n) { //O(E * min(E * V , |F|))
		Long ans = 0;
		while (true){ //O(min(E * V, |F|)) iterations
			fill(parent, parent + n, -1);
			Long inc = bfs(s, t);
			if (inc == 0) break;
			ans += inc;
		}
		return ans;
	}
} G;

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 5000;
const Long INF = 1e18;

struct Edge{
	Long from, to, cap, flow, cost;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long from , Long to, Long cap, Long cost) : from(from) , to(to), cap(cap), flow(0), cost(cost), rev(NULL) {}
};

struct Graph{
	vector<Edge*> adj[MX];
	int level[MX];
	int nextEdge[MX];
	Edge* parent[MX];
	
	void clear(int n) {
		for (int i = 0 ; i < n; i++) {
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			parent[i] = nullptr;
		}
	}
	
	void addEdge(int u, int v, Long w, Long cost, bool dir) {
		Edge *forward = new Edge(u , v , w, cost);
		Edge *backward = new Edge(v , u , 0, -cost);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].push_back(forward);
		adj[v].push_back(backward);
		
		if (!dir) {
			forward = new Edge(v , u , w, cost);
			backward = new Edge(u , v , 0, -cost);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].push_back(forward);
			adj[u].push_back(backward);
		}
	}
	
	pair<Long,Long> dfs(int u, int t ,Long f) { 
		//<flow, sumCost>
		if (u == t) return {f , 0};
		for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
			Edge *e = adj[u][i];
			int v = e->to;
			Long cf = e->cap - e->flow;
			if(cf == 0 || level[v] != level[u] + 1) continue;
			pair<Long, Long> ret = dfs(v, t, min(f, cf));
			if (ret.first > 0) {
				e->flow += ret.first;
				e->rev->flow -= ret.first;
				Long cost = e->cost * ret.first;
				return {ret.first , cost + ret.second};
			}
		}
		return {0, 0};
	}
	
	bool bfs(int s, int t){ //O(E)
		deque<int> q; 
		q.push_back(s);
		level[s] = 0;
		while (!q.empty()) {
			int u = q.front();
			q.pop_front();
			for (Edge *e: adj[u]) {
				int v = e->to;
				Long cf = e->cap - e->flow;
				if (level[v] == -1 && cf > 0) {
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	pair<Long, Long> maxFlow(int s, int t, int n){//General: O(E * V^2), Unit Cap: O(E * min(E^(1/2) , V^(2/3))), Unit Network: O(E * V^(1/2))
		//unit network is a network in which all the edges have unit capacity,
		//and for any vertex except s and t either incoming or outgoing edge is unique.
		Long flow = 0;
		Long cost = 0;
		while (true) { //O(V) iterations
			fill(level, level + n, -1);
			if (!bfs(s, t)) break;
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n , 0);
			pair<Long,Long> inc;
			do {
				inc = dfs(s , t , INF);
				flow += inc.first;
				cost += inc.second;
			} while (inc.first > 0);
		}
		return {flow, cost};
	}
	
	Long costCycle(int u, int n) {
		REP(i, n) {
			u = parent[u]->from; //go back n times just in case
			//There is no loss as this is a cycle
		}
		Long cf = INF;
		Long cur = u;
		while (true) {
			cf = min(cf , parent[cur]->cap - parent[cur]->flow);
			cur = parent[cur]->from;
			if (cur == u) {
				break;
			}
		}
		cur = u;
		Long cost = 0;
		while (true) {
			cost += cf * parent[cur]->cost;
			parent[cur]->flow += cf;
			parent[cur]->rev->flow -= cf;
			cur = parent[cur]->from;
			if (cur == u) {
				break;
			}
		}
		return cost;
	}
	
	Long spfa(int n) { //O(E V)
		vector<Long> d(n, 0);
		queue<int> q;
		vector<bool> inQueue(n , true);
		for (int u = 0; u < n; u++) q.push(u);
		int phase = 0;
		while (!q.empty() && phase < n) {
			int sz = q.size();
			REP(i, sz) {
				int u = q.front();
				q.pop();
				inQueue[u] = false;
				for (Edge* e : adj[u]) {
					int v = e->to;
					Long cf = e->cap - e->flow;
					Long w = e->cost;
					if (cf > 0 && d[u] + w < d[v]) {
						d[v] = d[u] + w;
						parent[v] = e;
						if (!inQueue[v]) {
							q.push(v);
							inQueue[v] = true;
						}
					}
				}
			}
			phase++;
		}
		if (!q.empty()) return costCycle(q.front(), n);
		// no negative cycle
		return 0;
	}
	
	pair<Long,Long> minCostFlow(int s, int t, int n){ 
		//O(dinic + EV * |totalCost|) = O(dinic + EV * (mUC))
		// |totalCost| <= E * U * C, where U is max cap and C max cost
		//<maxFlow, minCost>
		pair<Long, Long> ans = maxFlow(s, t , n);
		Long inc;
		do {
			inc = spfa(n);
			ans.second += inc;
		} while(inc < 0);
		return ans;
	}
} G;

int main() {
	return 0;
}

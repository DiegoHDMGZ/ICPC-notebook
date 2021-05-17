#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 5000;
const Long INF = 1e18;

struct Edge{
	Long from , to, cap, flow, cost;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long from , Long to, Long cap, Long cost) : from(from) , to(to), cap(cap), flow(0), cost(cost), rev(NULL) {}
};

struct Graph{
	vector<Edge*> adj[MX];
	Long level[MX];
	Long nextEdge[MX];
	Edge* parent[MX];
	
	void clear(Long N = MX) {
		for (Long i = 0 ; i < N; i++) {
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			parent[i] = NULL;
		}
	}
	
	void addEdge(Long u, Long v, Long w, Long cost, bool dir) {
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
	
	pair<Long,Long> dfs(Long u, Long t ,Long f) { 
		//<flow, sumCost>
		if(u == t) return {f , 0};
		for (Long &i = nextEdge[u]; i < adj[u].size(); i++) {
			Edge *e = adj[u][i];
			Long v = e->to;
			Long cf = e->cap - e->flow;
			if(cf == 0 || level[v] != level[u] + 1) continue;
			
			pair<Long,Long> ret = dfs(v, t, min(f, cf) );
			
			if (ret.first > 0) {
				e->flow += ret.first;
				e->rev->flow -= ret.first;
				Long cost = e->cost * ret.first;
				return {ret.first , cost + ret.second};
			}
		}
		return {0, 0};
	}
	
	bool bfs(Long s, Long t){ //O(E)
		deque<Long> q; 
		q.push_back(s);
		level[s] = 0;
		while (!q.empty()) {
			Long u = q.front();
			q.pop_front();
			for (Edge *e: adj[u]) {
				Long v = e->to;
				Long cf = e->cap - e->flow;
				if (level[v] == -1 && cf > 0) {
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	pair<Long,Long> maxFlow(Long s, Long t, Long n){//General: O(E * V^2), Unit Cap: O(E * min(E^(1/2) , V^(2/3))), Unit Network: O(E * V^(1/2))
		//unit network is a network in which all the edges have unit capacity,
		//and for any vertex except s and t either incoming or outgoing edge is unique.
		Long flow = 0;
		Long cost = 0;
		while (true) { //O(V) iterations
			fill(level, level + n, -1);
			if (!bfs(s, t)) {
				break;
			}
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n , 0);
			pair<Long,Long> inc;
			do{
				inc = dfs(s , t , INF);
				flow += inc.first;
				cost += inc.second;
			} while (inc.first > 0);
		}
		return {flow, cost};
	}
	
	Long costCycle(Long u, Long n) {
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
	
	Long spfa(Long n) { //O(EV)
		vector<Long> d(n, 0);
		queue<Long> q;
		vector<bool> inQueue(n , true);
		vector<Long> cnt(n, 0);
		for (int u = 0; u < n; u++) {
			q.push(u);
		}
		while (!q.empty()) {
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			cnt[u]++;
			if (cnt[u] == n + 1) {
				//negative cycle
				return costCycle(u, n);
			}
			for (Edge* e : adj[u]) {
				Long v = e->to;
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
		
		// no negative cycle
		return 0;
	
	}
	
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O(dinic + nm * |totalCost|) = O(dinic + nm * (mUC))
		//<maxFlow, minCost>
		pair<Long,Long> ans = maxFlow(s, t , n);
		Long inc;
		do{
			inc = spfa(n);
			ans.second += inc;
		}while(inc < 0);
		return ans;
	}
} G;

int main() {
	return 0;
}

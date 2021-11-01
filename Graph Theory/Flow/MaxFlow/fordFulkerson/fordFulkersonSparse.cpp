#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 3000;
const Long INF = 1e18;

struct Edge{
	Long to, cap, flow;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long to, Long cap) : to(to), cap(cap), flow(0), rev(NULL) {}
};

struct Graph{
	vector<Edge*> adj[MX];
	bool vis[MX];
	
	void clear(Long n) {
		for (Long i = 0 ; i < n; i++) {
			adj[i].clear();
			vis[i] = false;
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir) {
		Edge* forward = new Edge(v , w);
		Edge* backward = new Edge(u , 0);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].push_back(forward);
		adj[v].push_back(backward);

		if (!dir) {
			forward = new Edge(u , w);
			backward = new Edge(v , 0);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].push_back(forward);
			adj[u].push_back(backward);
		}
	}
	
	Long dfs(Long u, Long t ,Long f) { //O(E)
		if (u == t) return f;
		if (vis[u]) return 0;
		vis[u] = true;
		
		for (Edge* e : adj[u]) {
			Long v = e->to;
			Long cf = e->cap - e->flow;
			if (cf == 0) continue;
			
			Long ret = dfs(v, t, min(f, cf));
			
			if (ret > 0) {
				e->flow += ret;
				e->rev->flow -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t, Long n) { //O(E |F|) = O(E * nU)
		Long ans = 0;
		while (true) { // O(|F|) iterations
			fill(vis, vis + n, false);
			Long inc = dfs(s, t, INF);
			if (inc == 0) break;
			ans += inc;
		}
		return ans;
	}
} G;

int main(){
	return 0;
}

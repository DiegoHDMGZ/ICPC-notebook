#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 5000;
const Long INF = 1e18;

struct Edge{
	Long from, to, cap, flow;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long from ,Long to, Long cap) : from(from), to(to), cap(cap), flow(0), rev(NULL) {}
};

struct Graph{
	vector<Edge*> adj[MX];
	bool vis[MX];
	Edge * parent[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			vis[i] = false;
			parent[i] = NULL;
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir){
		Edge *forward = new Edge(u , v , w);
		Edge *backward = new Edge(v , u , 0);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].pb(forward);
		adj[v].pb(backward);

		if(!dir){
			forward = new Edge(v , u , w);
			backward = new Edge(u , v , 0);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].pb(forward);
			adj[u].pb(backward);
		}
	}
	
	void transition(Long s , Long t, Long inc){
		Long cur = t;
		
		while(cur != s){
			Edge* prev = parent[cur];
			prev->flow += inc;
			prev->rev->flow -= inc;
			cur = prev->from;
		}
	}
	
	Long bfs(Long s, Long t ){ //O(E)
		deque<pair<Long,Long> > q; //< node, capacity>
		q.push_back({s , INF});
		vis[s] = true;
		parent[s] = NULL;
		while(!q.empty()){
			Long u = q.front().first;
			Long c = q.front().second;
			q.pop_front();
			if(u == t){
				return c;
			}
			for(Edge *e : adj[u]){
				Long v = e->to;
				Long cf = e->cap - e->flow;
				if(!vis[v] && cf > 0){
					parent[v] = e;
					vis[v] = true;
					Long x = min(c , cf);
					q.push_back({v , x});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t , Long n){ //O(E * min(E * V , |F|))
		Long ans = 0;
		while(true){ //O( min (E * V , |F| ) ) iterations
			fill(vis, vis + n, false);
			Long inc = bfs(s, t);
			if(inc == 0) break;
			ans += inc;
			transition(s , t , inc);
		}
		return ans;
	}
	
} G;



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

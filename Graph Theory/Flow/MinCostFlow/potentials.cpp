#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
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
 
struct Path{
	Long node, weight;
	Path(){}
	
	Path(Long node,Long weight) : node(node) , weight(weight) {}
 
	bool operator >(const Path &P) const{
		return weight > P.weight;
	}
};
 
struct Graph{
	vector<Edge*> adj[MX];
	Edge *parent[MX];
	Long pot[MX];
	bool inQueue[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			parent[i] = NULL;
			pot[i] = 0;
		}
	}
	
	void addEdge(Long u, Long v, Long w, Long cost, bool dir){
		Edge *forward = new Edge(u , v , w, cost);
		Edge *backward = new Edge(v , u , 0, -cost);
		forward->rev = backward;
		backward->rev = forward;
		adj[u].pb(forward);
		adj[v].pb(backward);
		
		if(!dir){
			forward = new Edge(v , u , w, cost);
			backward = new Edge(u , v , 0, -cost);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].pb(forward);
			adj[u].pb(backward);
		}
	}
	
	void spfa(Long s , Long n){ //O(nm)
		for(Long i = 0; i < n; i++){
			pot[i] = INF;
		}
		queue<Long> q;
		pot[s] = 0;
		inQueue[s] = true;
		q.push(s);
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			for(Edge *e : adj[u]){
				Long v = e->to;
				if (e->cap - e->flow > 0 && pot[u] + e->cost < pot[v]){
					pot[v] = pot[u] + e->cost;
					if(!inQueue[v]){
						q.push(v);
					}
					inQueue[v] = true;
				}
			}
		}
	}
	
	pair<Long,Long> dijkstra(Long s, Long t, Long n){ //O(nlogm + mlogn)
		//<flow, cost>
		priority_queue<Path , vector<Path> , greater<Path>> q;
		
		vector<Long> d(n , INF);
		vector<Long> residualCap(n, 0);
		d[s] = 0;
		residualCap[s] = INF;
		q.push(Path(s , d[s]));
		
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			int u = p.node;
			if(p.weight != d[u]){
				continue;
			}
	
			for( Edge *e : adj[u]){
				Long v = e->to;
				Long cf = e->cap - e->flow;
				Long cost = e->cost + pot[u] - pot[v];
				
				if(cf > 0 && d[u] + cost < d[v]){
					d[v] = d[u] + cost;
					q.push(Path(v , d[v]));
					residualCap[v] = min(residualCap[u], cf);
					parent[v] = e;
				}
			}
		}
		if(d[t] == INF){
			return {0,0};
		}
		for(Long i = 0; i < n; i++){
			pot[i] += d[i];
		}
		Long cf = residualCap[t];
		Long cur = t;
		while(true ){
			parent[cur]->flow += cf;
			parent[cur]->rev->flow -= cf;
			cur = parent[cur]->from;
			if(cur == s){
				break;
			}
		}
		return {cf , pot[t] * cf};
	}
	
	
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O(m log n *  |f| ) = O(m log n *(nU))
		//<maxFlow, minCost>
		spfa(s , n); //not necessary if there is no negative edges
		pair<Long,Long> inc;
		pair<Long,Long> ans = {0,0};
		do{
			inc = dijkstra(s , t , n );
			ans.first += inc.first;
			ans.second += inc.second;
		}while(inc.first > 0);
		
		return ans;
	}
} G;

int main() {
	return 0;
}

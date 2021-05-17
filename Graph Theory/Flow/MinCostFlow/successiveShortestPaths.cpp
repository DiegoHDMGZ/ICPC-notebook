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
	Edge* parent[MX];
	vector<Edge*> E;
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			parent[i] = NULL;
		}
		E.clear();
	}
	
	void addEdge(Long u, Long v, Long w, Long cost, bool dir){
		Edge *forward = new Edge(u , v , w, cost);
		Edge *backward = new Edge(v , u , 0, -cost);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].push_back(forward);
		adj[v].push_back(backward);
		E.push_back(forward);
		E.push_back(backward);
		
		if(!dir){
			forward = new Edge(v , u , w, cost);
			backward = new Edge(u , v , 0, -cost);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].push_back(forward);
			adj[u].push_back(backward);
			E.push_back(forward);
			E.push_back(backward);
		}
	}
	
	pair<Long,Long> spfa(Long s , Long t, Long n){ //O(nm)
		vector<Long> d(n, INF);
		vector<Long> cnt(n , 0);
		vector<bool> inQueue(n , false);
		d[s] = 0;
		queue<Long> q;
		inQueue[s] = true;
		q.push(s);
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			cnt[u]++;
			assert(cnt[u] < n);
			for(Edge *e : adj[u]){
				Long v = e->to;
				if (e->cap - e->flow > 0 && d[u] + e->cost < d[v]){
					d[v] = d[u] + e->cost;
					if(!inQueue[v]){
						q.push(v);
					}
					parent[v] = e;
					inQueue[v] = true;
				}
			}
		}
		
		if(d[t] == INF) return {0,0};
		
		Long cf = INF;
		Long cur = t;
		while(true ){
			cf = min(cf , parent[cur]->cap - parent[cur]->flow);
			cur = parent[cur]->from;
			if(cur == s){
				break;
			}
		}
		
		cur = t;
		Long cost = 0;
		while(true ){
			cost += cf * parent[cur]->cost;
			parent[cur]->flow += cf;
			parent[cur]->rev->flow -= cf;
			cur = parent[cur]->from;
			if(cur == s){
				break;
			}
		}
		
		return {cf , cost};
	
	}
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O(n * m |f| ) = O(n * m * (nU))
		//Initially no negative cycles
		//<maxFlow, minCost>
		pair<Long,Long> inc;
		pair<Long,Long> ans = {0,0};
		do{
			inc = spfa(s , t , n );
			ans.first += inc.first;
			ans.second += inc.second;
		}while(inc.first > 0);
		
		return ans;
	}
} G;

int main() {
	return 0;
}

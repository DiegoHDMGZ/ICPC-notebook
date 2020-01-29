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

struct Graph{
	vector<Edge*> adj[MX];
	Long level[MX];
	Long nextEdge[MX];
	Edge * p[MX];
	vector<Edge*> E;
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			p[i] = NULL;
		}
		E.clear();
	}
	
	Graph(){
		clear();
	}
	void addEdge(Long u, Long v, Long w, Long cost, bool dir){
		Edge *forward = new Edge(u , v , w, cost);
		Edge *backward = new Edge(v , u , 0, -cost);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].pb(forward);
		adj[v].pb(backward);
		E.pb(forward);
		E.pb(backward);
		
		if(!dir){
			forward = new Edge(v , u , w, cost);
			backward = new Edge(u , v , 0, -cost);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].pb(forward);
			adj[u].pb(backward);
			E.pb(forward);
			E.pb(backward);
		}
	}
	
	pair<Long,Long> dfs(Long u, Long t ,Long f){ 
		//<flow, sumCost>
		if(u == t) return {f , 0};
		for(Long &i = nextEdge[u]; i < adj[u].size(); i++){
			Edge *e = adj[u][i];
			Long v = e->to;
			Long cf = e->cap - e->flow;
			if(cf == 0 || level[v] != level[u] + 1) continue;
			
			pair<Long,Long> ret = dfs(v, t, min(f, cf) );
			
			if(ret.first > 0){
				e->flow += ret.first;
				e->rev->flow -= ret.first;
				Long cost = e->cost * ret.first;
				return {ret.first , cost + ret.second};
			}
		}
		return {0,0};
	}
	
	bool bfs(Long s, Long t ){ //O(E)
		deque<Long> q; 
		q.push_back(s);
		level[s] = 0;
		while(!q.empty()){
			Long u = q.front();
			q.pop_front();
			for(Edge *e: adj[u]){
				Long v = e->to;
				Long cf = e->cap - e->flow;
				if(level[v] == -1 && cf > 0){
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
		while(true){ //O(V) iterations
			fill(level, level + n, -1);
			if(!bfs(s, t) ){
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
	
	Long costCycle(Long y, Long n){
		REP( i , n) {
			y = p[y]->from; //go back n times just in case
			//There is no loss as this is a cycle
		}
		Long minCap = INF;
		Long cur = y;
		while(true ){
			minCap = min(minCap , p[cur]->cap - p[cur]->flow);
			cur = p[cur]->from;
			if(cur == y){
				break;
			}
		}
		cur = y;
		Long cost = 0;
		while(true ){
			cost += minCap * p[cur]->cost;
			p[cur]->flow += minCap;
			p[cur]->rev->flow -= minCap;
			cur = p[cur]->from;
			if(cur == y){
				break;
			}
		}
		return cost;
	}
	
	Long bellmanFord(Long n, Long root = 0){ //O(nm)
		vector<Long> d(n, INF);
		d[root] = 0;
		Long m = E.size();
		Long negaCycle; //negative cycle flag
		
		REP(i , n) {
			negaCycle = -1; 
			REP ( j , m ) {
				if (d[E[j]->from] < INF && E[j]->cap - E[j]->flow > 0) {
					if (d[E[j]->to] > d[E[j]->from] + E[j]->cost) {
						d[E[j]->to] = max(-INF ,d[E[j]->from] + E[j]->cost); //avoiding overflow
						p[E[j]->to] = E[j];
						negaCycle = E[j]->to;
					}
				}
			}
			if(negaCycle == -1) break;
		}
		
		if(negaCycle == -1){
			return 0; //no negative cycle
		}
		else{
			return costCycle(negaCycle, n);
		}
	
	}
	
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O(dinic + nm * # cycles) = O(dinic + nm * (mUC)) 
		//<maxFlow, minCost>
		pair<Long,Long> ans = maxFlow(s, t , n);
		Long inc;
		do{
			inc = bellmanFord(n , s);
			ans.second += inc;
		}while(inc > 0);
		return ans;
	}
} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	return 0;
}

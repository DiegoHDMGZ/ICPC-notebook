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
 
	bool operator <(const Path &P) const{
		if(weight == P.weight){
			return node > P.node;
		}
		return weight > P.weight;
	}
};
 
struct Graph{
	vector<Edge*> adj[MX];
	Edge *parent[MX];
	Long pot[MX];
	vector<Edge*> E;
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			parent[i] = NULL;
			pot[i] = 0;
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
	
	void bellmanFord(Long s , Long t, Long n){ //O(nm)
		vector<Long> d(n, INF);
		d[s] = 0;
		Long m = E.size();
		Long negaCycle; //negative cycle flag
		
		REP(i , n) {
			negaCycle = -1; 
			REP ( j , m ) {
				if (d[E[j]->from] < INF && E[j]->cap - E[j]->flow > 0) {
					if (d[E[j]->to] > d[E[j]->from] + E[j]->cost) {
						d[E[j]->to] = max(-INF ,d[E[j]->from] + E[j]->cost); //avoiding overflow
						negaCycle = E[j]->to;
					}
				}
			}
			if(negaCycle == -1) break;
		}
		for(Long i = 0; i < n; i++){
			pot[i] = d[i];
		}
		assert(negaCycle == -1); //(!) algorithm doesnt apply
	}
	
	pair<Long,Long> dijkstra(Long s, Long t, Long n){ //O(nlogm + mlogn)
		//<flow, cost>
		priority_queue<Path> q;
		
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
		bellmanFord(s , t , n); //not necessary if there is no negative edges
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n , m;
	cin >> n >> m;
	REP(i , m){
		Long u , v, w , c;
		cin >> u >> v >> w >> c;
		u--;
		v--;
		
		G.addEdge(u , v , w , c , true);
	}
	Long s = 0, t = n - 1; 
	cout << G.minCostFlow(s , t , t + 1).second;
	return 0;
}

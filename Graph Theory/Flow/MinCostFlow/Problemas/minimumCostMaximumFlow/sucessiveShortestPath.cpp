#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/group/Ohoz9kAFjS/contest/266572/problem/G

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
	
	pair<Long,Long> bellmanFord(Long s , Long t, Long n){ //O(nm)
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
						p[E[j]->to] = E[j];
						negaCycle = E[j]->to;
					}
				}
			}
			if(negaCycle == -1) break;
		}
		
		assert(negaCycle == -1); //(!) algorithm doesnt apply
		
		if(d[t] == INF) return {0,0};
		
		Long cf = INF;
		Long cur = t;
		while(true ){
			cf = min(cf , p[cur]->cap - p[cur]->flow);
			cur = p[cur]->from;
			if(cur == s){
				break;
			}
		}
		
		cur = t;
		Long cost = 0;
		while(true ){
			cost += cf * p[cur]->cost;
			p[cur]->flow += cf;
			p[cur]->rev->flow -= cf;
			cur = p[cur]->from;
			if(cur == s){
				break;
			}
		}
		
		return {cf , cost};
	
	}
	
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O( n * m * |f| )
		//<maxFlow, minCost>
		pair<Long,Long> inc;
		pair<Long,Long> ans = {0,0};
		do{
			inc = bellmanFord(s , t , n );
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

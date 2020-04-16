#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/group/Ohoz9kAFjS/contest/266572/problem/J

const Long MX = 1e5;
const Long INF = 1e18;


struct Edge{
	Long from , to, cap, flow, cost;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long from , Long to, Long cap, Long cost) : from(from) , to(to), cap(cap), flow(0), cost(cost), rev(NULL) {}
};

struct Graph{
	vector<Edge*> adj[MX];
	Edge *parent[MX];
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

Long enter(Long u){
	return 2 * u + 1;
}

Long exit(Long u){
	return 2 * u + 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	Long a , b , c;
	cin >> a >> c >> b;
	a--;
	b--;
	c--;
	
	Long s = 0;
	G.addEdge(s , enter(a), 1 , 0, true);
	G.addEdge(s, enter(c) , 1 , 0 , true);
	REP(i , n){
		G.addEdge(enter(i), exit(i), 1, 0, true );
	}
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		u--;
		v--;
		
		G.addEdge(exit(u), enter(v), 1 , w, true);
		G.addEdge(exit(v), enter(u) , 1 , w , true);
	}
	
	pair<Long,Long> mcf = G.minCostFlow(s , enter(b) , 2 * n + 1);
	
	if(mcf.first != 2){
		cout << "-1\n";
	} else {
		deque<Long> L;
		deque<Long> R;
		Long u = a;
		while(u != b){
			L.pb(u + 1);
			for(auto eV : G.adj[exit(u)]){
				if(eV->flow == 1){
					Long v = eV->to;
					u = (v - 1) / 2;
					break;
				}
				
				
			}
		}
		L.pb(b + 1);
		u = c;
		while(u != b){
			R.push_front(u + 1);
			for(auto eV : G.adj[exit(u)]){
				if(eV->flow == 1){
					Long v = eV->to;
					u = (v - 1) / 2;
					break;
				}
				
				
			}
		}
		for(Long x : R){
			L.pb(x);
		}
		cout << (Long)L.size() - 1 << " " << mcf.second << endl;
		for(Long x : L){
			cout << x << " ";
		}
		cout << endl;
	}

	return 0;
}
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef int Long;

const Long MX = 2005;
const Long INF = 2e9;

struct Path{
	Long node, weight;
	Path(){}
	
	Path(Long node,Long weight) : node(node) , weight(weight) {}
 
	bool operator >(const Path &P) const{
		return weight > P.weight;
	}
};

struct Graph{
	vector<Long> adj[MX];
	Long cap[MX][MX];
	Long cost[MX][MX];
	Long flow[MX][MX];
	Long parent[MX];
	Long pot[MX];
	bool inQueue[MX];
	vector<Long> dag[MX];
	Long indegree[MX];
	
	void addEdge(Long u, Long v, Long w, Long c){
		adj[u].push_back(v);
		adj[v].push_back(u);
		dag[u].pb(v);
		indegree[v]++;
		cap[u][v] = w;
		cost[u][v] = c;
		cost[v][u] = -c;
	}
	
	void topo(Long s , Long n){ //O(nm)
		for(Long i = 0; i < n; i++){
			pot[i] = INF;
		}
		queue<Long> q;
		pot[s] = 0;
		q.push(s);
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			for(Long v : dag[u]){
				if ( pot[u] + cost[u][v] < pot[v]){
					pot[v] = pot[u] + cost[u][v];
				}
				indegree[v]--;
				if(indegree[v] == 0){
					q.push(v);
				}
			}
		}
	}
	 
	
	
	pair<Long,Long> dijkstra(Long s, Long t, Long n){ //O(m log n)
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
	
			for( Long v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				Long c = cost[u][v] + pot[u] - pot[v];
				
				if(cf > 0 && d[u] + c < d[v]){
					assert(c >= 0);
					d[v] = d[u] + c;
					q.push(Path(v , d[v]));
					residualCap[v] = min(residualCap[u], cf);
					parent[v] = u;
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
			flow[parent[cur]][cur] += cf;
			flow[cur][parent[cur]] -= cf;
			cur = parent[cur];
			if(cur == s){
				break;
			}
		}
		return {cf,pot[t] * cf} ;
	}
	
	
	pair<Long,Long> minCostFlow(Long s, Long t, Long n){ 
		//O(m log n *  |f| ) = O(m log n *(nU))
		//<maxFlow, minCost>
		topo(s  , n); //not necessary if there is no negative edges
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

struct Task{
	Long l , r , c, order;
	Task(){}
	Task(Long l, Long r, Long c, Long order) : l(l), r(r), c(c), order(order) {}
};

bool cmp(const Task &T1, const Task &T2){
	return T1.l < T2.l;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n , k;
	cin >> n >> k;
	
	vector<Task> task;
	Long s = 0;
	Long t = 2 * n + 1;
	G.addEdge(s, 1, k , 0);
	REP(i , n){
		Long l , dur, c;
		cin >> l >> dur >> c;
		Long r = l + dur - 1;
		task.pb(Task(l, r,  c , i));
	}
	sort(task.begin(), task.end(), cmp);
	
	vector<Long> choice(n, t);
	REP(i ,n){
		G.addEdge(i + 1 , i + n + 1 , k , 0);
		Long next = i + 2;
		if(i == n - 1) {
			next = t;
		}
		G.addEdge(i + 1 + n , next , k , 0);
		for(Long j = i + 1; j < n; j++){
			if(task[i].r < task[j].l){
				choice[i] = j + 1;
				break;
			}
		}
		G.addEdge(i + 1 , choice[i], 1 , -task[i].c);
	}
	G.minCostFlow(s , t , t + 1);

	vector<Long> ans(n , 0);
	REP(i , n){
		if(G.flow[i + 1][choice[i]] == 1){
			ans[task[i].order] = 1;
		} else {
			ans[task[i].order] = 0;
		}
	}
	REP(i , n){
		cout << ans[i] << " ";
	}

	return 0;
}

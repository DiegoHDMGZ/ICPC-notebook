#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
 
using namespace std;
 
typedef long long Long;

struct Edge{
	int u, v;
	Edge(int u , int v) : u(min(u , v)) , v(max(u,v)){
	}
	Edge(){
	}
	
	bool operator == (const Edge &E) const {
		return E.u == u && E.v == v;
	}
	
	bool operator != (const Edge &E) const {
		return !(E == *this);
	}
};

const int MX = 1000;
const Long INF = 1e18;



Long energy[MX];

struct Graph{
	vector<int> adj[MX];
	vector<Long> nodes[MX];
	bool vis[MX];
	int tIn[MX];
	int low[MX];
	int timer;
	stack<Edge> edges;
	Long energyBiconnected[MX];

	int numComponent;
	Graph(){
		timer = 0;
		numComponent = 0;
	}

   Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool added[MX][MX];
	Long level[MX];
	Long nextEdge[MX];
	
	bool haveComponent[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			for(Long j = 0; j < N; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
			tIn[i] = low[i] = 0;
			vis[i] = false;
			nodes[i].clear();
			haveComponent[i] = false;
			energyBiconnected[i] = 0;
		}
		timer = numComponent = 0;
	}
	
	void addEdge(Long u, Long v, Long w, bool dir){
		if(!added[min(u, v)][max(u , v)]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		added[min(u , v)][max(u , v)] = true;
		cap[u][v] += w;
		if(!dir){
			cap[v][u] += w;
		}
	}
	
	Long dfsFlow(Long u, Long t ,Long f){ 
		if(u == t) return f;
		
		for(Long &i = nextEdge[u]; i < adj[u].size(); i++){
			Long v = adj[u][i];
			Long cf = cap[u][v] - flow[u][v];
			if(cf == 0 || level[v] != level[u] + 1) continue;
			
			Long ret = dfsFlow(v, t, min(f, cf) );
			
			if(ret > 0){
				flow[u][v] += ret;
				flow[v][u] -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	bool bfs(Long s, Long t ){ //O(E)
		deque<Long> q; 
		q.push_back(s);
		level[s] = 0;
		while(!q.empty()){
			Long u = q.front();
			q.pop_front();
			for(Long v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				if(level[v] == -1 && cf > 0){
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	Long maxFlow(Long s, Long t, Long n){//General: O(E * V^2), Unit Cap: O(E * min(E^(1/2) , V^(2/3))), Unit Network: O(E * V^(1/2))
		Long ans = 0;
		while(true){ //O(V) iterations
			fill(level, level + n, -1);
			if(!bfs(s, t) ){
				break;
			}
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n , 0);
			Long inc;
			do{
				inc = dfsFlow(s , t , INF);
				ans += inc;
			} while (inc > 0);
		}
		return ans;
	}

	
	void addBiconnectedComponent(Edge e){
		if(edges.empty()) return;
		
		unordered_set<int> processed; //articulation processed
		
		while(!edges.empty()){
			Edge cur = edges.top();
			int u = cur.u;
			int v = cur.v;
	
		   processed.insert(u);
		   processed.insert(v);
			edges.pop();
			if(cur == e){
				break;
			}
		}
		if(processed.size() == 2) {
		   return;
		}
		for(Long u : processed){
		   haveComponent[u] = true;
		   nodes[numComponent].pb(u);
		}
		
		numComponent++;
	}
	
	void dfs(int u = 0, int p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		int children = 0;
		for(int v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
				if(tIn[v] < tIn[u]){
					edges.push(Edge(u , v));
				}
			} else {
				edges.push(Edge(u , v));
				dfs(v , u );
				low[u] = min(low[u] , low[v]);
				
				if(low[v] >= tIn[u] && p != -1 ) {
					Edge e = Edge(u,v);
					addBiconnectedComponent(e);
				}
				children++;
				if(p == -1 && children > 1){
					Edge e = Edge(u,v);
					addBiconnectedComponent(e);
				}
			}
		}
		if(p == -1 ) {
			Edge e = Edge(-1,-1);
			addBiconnectedComponent(e);
		} 
	}
	
	void calculate(Long n) {
	   for(Long i = 0; i < n ; i++) {
	      if(!vis[i]) {
	         dfs(i);
	      }
	   }
	   for(Long i = 0; i < n; i++){
	      if(!haveComponent[i]) {
	         nodes[numComponent].pb(i);
	         numComponent++;
	      }
	   }
	   REP(i , numComponent) {
	      for(Long u : nodes[i]){
	         energyBiconnected[i] += energy[u];
	      }
	   }
	}

} G , GFlow;


Long buzz[MX];

bool check( Long maxDif, Long b , Long numComponent ){
   Long s = 0;
   Long t = b + numComponent + 1;
   GFlow.clear(t + 1);

   
   REP(i , numComponent) {
      GFlow.addEdge(s , i + 1 , 1 , true);
   }
   REP(i , b) {
      GFlow.addEdge(numComponent + i + 1 , t , 1 , true);
   }
   REP(i , numComponent){
      REP(j , b) {
         if(abs(buzz[j] - G.energyBiconnected[i]) <= maxDif) {
            GFlow.addEdge(i + 1 , j + numComponent + 1 , 1 , true);
         }
      }
   }

   return GFlow.maxFlow(s , t , t + 1) == numComponent;
	
}

Long search(  Long ini , Long fin , Long b, Long numComponent){ //O(logn)
	// F F F... V V V
	if(check(ini, b , numComponent)) return ini; //todos V
	
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= ini + (fin - ini) / 2;
		
		if(check( med , b , numComponent)){
			fin = med;
		} 
		else {
			ini = med;
		}
	}

	//hay 2 valores ini es F y fin es V
	return fin;
}



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	
	REP(q , T){
	   Long n , m , b;
	   cin >> n >> m >> b;
	   G.clear(n);
	   REP(i , n) {
	      cin >> energy[i];
	   }
	   REP(i , b) {
	      cin >> buzz[i];
	   }
	   REP(i , m){
	      Long u , v;
	      cin >> u >> v;
	      u--;v--;
	      G.addEdge(u, v, 1 , false);
	   }
	   G.calculate(n);
	   cout << "Buzz Mission " << q + 1 << ": " << G.numComponent << " ";
	   if(b < G.numComponent) {
	      cout << "No\n";
	   } else {
	       cout << search(0 , 1e12 , b , G.numComponent) << "\n";
	   }
	  
	}
	

	return 0;
}

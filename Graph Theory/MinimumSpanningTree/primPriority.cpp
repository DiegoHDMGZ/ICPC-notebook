#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Edge{
    Long w ,nodo;
    Edge(){
        w = INF;
        nodo = -1;
    }
    
    Edge(Long t, Long _w){
        w = _w;
        nodo = t;
    }
    
    bool operator <(Edge const &other) const{
        return w > other.w;
    }
};

struct Graph { 
	vector<Long> adj [MX];
	vector<Long> cost[MX];
	
	Long minCost[MX];
	Long p[MX]; //padre en el MST
	bool selected[MX];
	
	void clear(Long N) { //mandatory
		REP( i, N) {
			selected[i] = false;
			minCost[i] = INF;
			p[i] = -1;
			adj[i].clear();
			cost[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].pb(v);
		adj[v].pb(u);
		cost[u].pb(w);
		cost[v].pb(w);
	}
	
	Long prim (Long N) { //O(mlogn)
		REP(i , N){
			minCost[i] = INF;
		}
	    Long totalWeight = 0;
		minCost[0] = 0;
	    priority_queue<Edge> q;
	    
	    Edge ini(0,0);
	    q.push(ini);
	    
	    Long totalNodos = 0;
		while(!q.empty()) {
		    //encontramos la arista siguiente con menor peso
		    Edge e = q.top();
		    q.pop();
		    Long u = e.nodo;
		    if(selected[u]) {
		    	continue;
			}
		    
		    totalWeight += e.w;
		    selected[u] = true;
		    totalNodos++;
			
			Long j = 0;
		    for(Long v : adj[u] ) {
		        if(cost[u][j] < minCost[v] && !selected[v]){
		            minCost[v] = cost[u][j];
		            p[v] = u;
					q.push( Edge(v,cost[u][j] ) );
		        }
		        
		        j++;
		    }
		}
		
		if(totalNodos != N) return -1;
	    return totalWeight;
	}
		
	
} G;

int main() {
	Long n , m;
	cin >> n >> m;
	G.clear(n);
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		G.addEdge(u , v, w);
	}
	G.prim(n);
	REP(i , n){
		cout << G.p[i] + 1<< " -> " << i + 1 << endl;
	}
    return 0;
}

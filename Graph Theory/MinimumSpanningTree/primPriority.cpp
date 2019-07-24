#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;
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
	vector<Long> adj [MAX];
	vector<Long> cost[MAX];
	
	Long minCost[MAX];
	Long p[MAX]; //padre en el MST
	bool selected[MAX];
	
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
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
		cost[u].pb(w);
		cost[v].pb(w);
	}
	
	Long prim (Long N) { //O(mlogn)
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
    return 0;
}

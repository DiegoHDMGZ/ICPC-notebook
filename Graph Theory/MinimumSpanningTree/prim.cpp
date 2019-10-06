#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Edge{
    Long w ,to;
    Edge(){
        w = INF;
        to = -1;
    }
    
    Edge(Long t, Long _w){
        w = _w;
        to = t;
    }
    
    bool operator <(Edge const &other) const{
    	if(w == other.w) return to < other.to;
        return w < other.w;
    }
};

struct Graph {
	vector<Long>adj [MX];
	vector<Long> cost[MX];
	
	Long p[MX]; //padre en el MST
	bool selected[MX];
	
	void clear(Long N = MX) { //mandatory
		REP(i , N) {
			adj[i].clear();
			cost[i].clear();
			p[i] = -1;
			selected[i] = false;
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].pb(v);
		adj[v].pb(u);
		cost[u].pb(w);
		cost[v].pb(w);
	}
	
	Long prim(Long N){ //O(mlogn)
	    Long totalWeight = 0;
	    vector<Edge> min_e(N); //vector de pesos minimos hacia un vertice seleccionado desde cada nodo no seleccionado
	    min_e[0].w = 0;
	    set<Edge> q;
	    Edge ini(0,0);
	    q.insert(ini);
	    
	    REP( i , N){
	        if(q.empty()){
	            return -1;
	            //no hay maximum spanning tree
	        }
	        //encontramos la arista siguiente con menor peso
	        Long u = q.begin()->to;
	        totalWeight += q.begin()->w;
	  
	        q.erase(q.begin()); //la borramos de la lista
	        
	        selected[u] = true;
	        
	        if(min_e[u].to != -1){
	            p[u] = min_e[u].to;
	        }
			
			Long j = 0;
	        for (Long v : adj[u] ) {
	            if(cost[u][j] < min_e[v].w && !selected[v]){
	                Edge borrar(v,min_e[v].w);
	                if(min_e[v].w != INF){
	                	q.erase(borrar);
					}
	                Edge actualizar(u,cost[u][j]);
	                min_e[v] = actualizar;
	
	                Edge insertar(v,cost[u][j]);
	                q.insert(insertar);
	            }
	            j++;
	        }
	    }
	    return totalWeight;
	}

} G;

int main() {
    return 0;
}

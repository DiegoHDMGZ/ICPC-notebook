#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.hackerrank.com/challenges/primsmstsub/problem


const Long MX = 1e5;
const Long INF = 1e18;

struct EndPoint{
    Long node , w;
    EndPoint(){
        w = INF;
        node = -1;
    }
    
    EndPoint(Long node, Long w): node(node), w(w) {}
    
    bool operator <(EndPoint const &other) const{
        return w > other.w;
    }
};


struct Graph { 
	vector<EndPoint> adj [MX];
	
	Long minCost[MX];
	Long p[MX]; 
	bool selected[MX];
	
	void clear(Long N = MX) { //mandatory
		REP( i, N) {
			selected[i] = false;
			minCost[i] = INF;
			p[i] = -1;
			adj[i].clear();
		}
	}
	
	Graph(){
		clear();
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].pb(EndPoint(v , w));
		adj[v].pb(EndPoint(u , w));
	}
	
	Long MST (Long n) { //O(mlogn)
	    Long totalWeight = 0;
		minCost[0] = 0;
	    priority_queue<EndPoint> q;
	    
	    EndPoint ini(0,0);
	    q.push(ini);
	    
	    Long totalNodes = 0;
		while(!q.empty()) {
		    //we find the next edge with least weight
		    EndPoint cur = q.top();
		    q.pop();
		    Long u = cur.node;
		    if(selected[u]) {
		    	continue;
			}
		    
		    totalWeight += cur.w;
		    selected[u] = true;
		    totalNodes++;
			
			for(EndPoint e : adj[u]){
				  Long v = e.node;
				  if(e.w < minCost[v] && !selected[v]){
		            minCost[v] = e.w;
		            p[v] = u;
					q.push( e );
		        }
		        
			}
	
		}
		
		if(totalNodes != n) return -1;
	    return totalWeight;
	}
		
} G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n , m;
	cin >> n >> m;
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		G.addEdge(u - 1 , v - 1 , w);
	}
	cout << G.MST(n) << endl;
	return 0;
}

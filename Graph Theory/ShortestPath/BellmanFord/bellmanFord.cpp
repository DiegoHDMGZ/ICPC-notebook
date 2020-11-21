#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;
const Long MX = 1e4;
const Long INF = 1e18;

struct Edge{
	Long u, v, w;
	Edge(){}
	Edge(Long u, Long v, Long w) : u(u) , v(v) , w(w) {}
};

struct Graph{
	vector<Edge> edges;
	Long d[MX];
	Long parent[MX];
	
	void clear() {
		edges.clear();
	}

	void addEdge(Long u, Long v, Long w) {
		edges.push_back(Edge(u, v , w));
	}
	
	bool bellmanFord(Long s , Long n){ //O(VE)
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			parent[i] = -1;
		}
		d[s] = 0;
		Long relaxedVertex = -1; 
		for (Long i = 0; i < n; i++) {
			relaxedVertex = -1; 
			for (Edge e : edges ) {
				if (d[e.u] != INF && d[e.u] + e.w < d[e.v]) { //tense
					d[e.v] = d[e.u] + e.w; //relax
					parent[e.v] = e.u;
					relaxedVertex = e.v;
				}
			}
			if(relaxedVertex == -1) {
				break;
			}
		}
		if(relaxedVertex == -1){
			return false; //no negative cycle
		} else{
			return true; //negative cycle found
			//getNegativeCycle(relaxedVertex, n);
		}
	
	}
	
	vector<Long> getNegativeCycle(Long u, Long n){
		//go back n times to find a cycle
		for (int i = 0; i < n; i++) {
			u = parent[u]; 
			assert(parent[u] != -1);
		}
		
		vector<Long> cycle = {u};
		u = parent[u];
		while (u != cycle[0]) {
			cycle.push_back(u);
			u = parent[u];
		}
		return cycle;
	}
	
	vector<Long> getPath(Long u){
		if (d[u] == INF) {
			return {};
		}
		vector<Long> path;
		while(u != -1){
			path.push_back(u);
			u = parent[u];
		}
		reverse(path.begin(), path.end());
		return path;
	}
} G;

int main() {
	return 0;
}

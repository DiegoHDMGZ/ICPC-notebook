#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Graph{
	Long d[MX];
	vector<pair<Long, Long>> adj[MX];
	
	void clear(Long n) {
		for (Long i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u , Long v, Long w) {
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	
	void bfs01(Long s, Long n){ //O(V + E)
		for(Long i = 0; i < n; i++){
			d[i] = INF;
		}
		d[s] = 0;
		deque<Long> q;
		q.push_back(s);
		
		while(!q.empty()){
			Long u = q.front();
			q.pop_front();
			for (auto e : adj[u] ) {
				Long v = e.first;
				Long w = e.second;
				if(d[u] + w < d[v]) {
					d[v] = d[u] + w;
					if(w == 0){
						q.push_front(v);
					}
					else{
						q.push_back(v);
					}
				}
			}
		} 
	}
	
} G;

int main() {
    return 0;
}

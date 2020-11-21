#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

Long d[MX];
struct Compare{
    bool operator() (Long u, Long v) const {
		if (d[u] == d[v]) return u < v; 
        return d[u] < d[v];
    }
};

struct Graph{
	vector<pair<Long,Long>> adj[MX];
	Long parent[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back({v , w});
		adj[v].push_back({u , w});
	}
	
	void dijkstra(Long s, Long n){ //O(E log V)
		for(Long i = 0; i < n; i++){
			parent[i] = -1;
			d[i] = INF;
		}
		set<Long, Compare> q;
		d[s] = 0;
		q.insert(s);
		while(!q.empty()){
			Long u = *q.begin();
			q.erase(q.begin());
			for(auto e : adj[u]){
				Long v = e.first;
				Long w = e.second;
				if(d[u] + w < d[v]){
					q.erase(v);
					d[v] = d[u] + w;
					parent[v] = u;
					q.insert(v);
				}
			}
		}
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

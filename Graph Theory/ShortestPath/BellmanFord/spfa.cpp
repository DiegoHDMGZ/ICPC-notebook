#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e4;
const Long INF = 1e18;

struct EndPoint{
	Long node, weight;
	EndPoint(){}
	EndPoint(Long node, Long weight) : node(node) , weight(weight) {}
};

struct Graph{
	vector<EndPoint> adj[MX];
	Long d[MX];
	Long parent[MX];
	
	void clear(Long N = MX) {
		REP(i , N) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back(EndPoint(v, w));
		adj[v].push_back(EndPoint(u , w));
	}
	
	deque<Long> retrieveCycle(Long v, Long n){
		REP ( i , n) {
			v = parent[v]; //go back n times just in case
		}
		
		deque<Long> path;
		for(Long actual = v; ; actual = parent[actual]){
			path.push_front(actual);
			if(actual == v && path.size() > 1){
				break;
			}
		}
		return path;
	}
	
	deque<Long> retrievePath(Long v){
		if(parent[v] == -1){
			return {};
		}
		deque<Long> path;
		while(v != -1){
			path.push_front(v);
			v = parent[v];
		}
		return path;
	}
	
	bool spfa(Long n, Long m, Long root = 0){ //O(nm)
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			parent[i] = -1;
		}
		queue<Long> q;
		vector<bool> inQueue(n , false);
		vector<Long> cnt(n, 0);
		d[root] = 0;
		inQueue[root] = true;
		q.push(root);
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			cnt[u]++;
			if(cnt[u] >= n){
				return true;
			}
			for(EndPoint e : adj[u]){
				Long v = e.node;
				if(d[u] + e.weight < d[v]){
					d[v] = d[u] + e.weight;
					parent[v] = u;
					if(!inQueue[v]){
						q.push(v);
					}
					inQueue[v] = true;
				}
			}
		}
		return false;
	}
} G;

int main() {
	return 0;
}

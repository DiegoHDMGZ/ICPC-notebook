#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1e6;

struct Graph {
	vector<Long> adj[MX];
	Long indegree[MX]; 
	
	void clear(Long n) {
		for (Long i = 0; i < n; i++){
			indegree[i] = 0;
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v) {
		adj[u].push_back(v);
		indegree[v]++;
	}
	
	vector<Long> toposort(Long n) { //O(V + E)
		deque<Long> q;
		vector<Long> order;
		for (Long i = 0; i < n; i++) {
			if (indegree[i] == 0) {
				q.push_back(i);
			}
		}
		while (!q.empty()) {
			Long u = q.front();
			order.push_back(u);
			q.pop_front();
			for (Long v : adj[u]) {
				indegree[v]--;
				if(indegree[v] == 0){
					q.push_back(v);
				} 
			}
		}
		return order;
	}
}G ;

int main() {
	return 0;
}

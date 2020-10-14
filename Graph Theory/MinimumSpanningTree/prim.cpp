#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Endpoint{
	Long node , w;
	Endpoint(Long node, Long w): node(node), w(w) {}
	bool operator >(Endpoint const &other) const{
		return w > other.w;
	}
};

struct Graph { 
	vector<Endpoint> adj[MX];
	Long minWeight[MX];
	Long parent[MX]; 

	void clear(Long n) { 
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back(Endpoint(v , w));
		adj[v].push_back(Endpoint(u , w));
	}

	Long getMST(Long n, Long root = 0) { //O(mlogn)
		Long totalWeight = 0;
		Long totalNodes = 0;
		vector<bool> onTree(n, false);
		fill(minWeight, minWeight + n, INF);
		minWeight[root] = 0;
		parent[root] = -1;
		priority_queue<Endpoint, vector<Endpoint>, greater<Endpoint>> q;
		q.push(Endpoint(0, 0));
		while (!q.empty()) {
			Endpoint cur = q.top();
			q.pop();
			Long u = cur.node;
			if (onTree[u]) {
				continue;
			}
			totalWeight += cur.w;
			onTree[u] = true;
			totalNodes++;
			for (Endpoint e : adj[u]) {
				Long v = e.node;
				if (e.w < minWeight[v] && !onTree[v]) {
					minWeight[v] = e.w;
					parent[v] = u;
					q.push(e);
				}
			}
		}
		if(totalNodes != n) return -1;
		return totalWeight;
	}
} G;

int main() {
	return 0;
}

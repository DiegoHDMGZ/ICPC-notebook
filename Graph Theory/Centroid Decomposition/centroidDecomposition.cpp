#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const int MX = 1e5;
struct Graph {
	vector<int> adj[MX];
	int size[MX];
	bool vis[MX];
	int parent[MX];
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void findSize(int u, int p = -1) {
		size[u] = 1;
		for (int v : adj[u]) {
			if (v != p && !vis[v]) {
				findSize(v, u);
				size[u] += size[v];
			}
		}
	}
	
	int findCentroid(int u, int n, int p = -1) {
		for (int v : adj[u]) {
			if (v != p && !vis[v]) {
				if (2 * size[v] > n ) {
					return findCentroid(v, n, u);
				}
			}
		}
		return u;
	}
	
	void build(int root = 0) {
		findSize(root);
		int centroid = findCentroid(root, size[root]);
		vis[centroid] = true;
		for (int v : adj[root]) {
			if (!vis[v]) {
				parent[v] = centroid;
				build(v);
			}
		}
	}
}G; 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	return 0;
}

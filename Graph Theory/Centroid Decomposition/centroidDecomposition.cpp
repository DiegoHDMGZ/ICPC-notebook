#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Property :
A path from u to v in the original tree can be decomposed into
the path from u to centroid.lca(u , v) and from centroid.lca(u , v) to v
*/

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
	
	void build(int u = 0, int p = -1) {
		findSize(u);
		int centroid = findCentroid(u, size[u]);
		vis[centroid] = true;
		parent[centroid] = p;
		for (int v : adj[centroid]) {
			if (!vis[v]) {
				build(v, centroid);
			}
		}
	}
}G; 

int main() {
	return 0;
}

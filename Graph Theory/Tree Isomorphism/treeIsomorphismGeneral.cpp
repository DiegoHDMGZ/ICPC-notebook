#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 1e5;
struct Tree{
	vector<int> adj[MX];
	int depth[MX];
	int parent[MX];
	vector<int> layers[MX];
	int maxDepth;
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int u, int p = -1) {
		maxDepth = max(maxDepth, depth[u]);
		parent[u] = p;
		layers[depth[u]].push_back(u);
		for (int v : adj[u]) {
			if (v == p) continue;
			depth[v] = depth[u] + 1;
			dfs(v, u);
		}
	}
	
	vector<int> encode(int root, int n) { //O(n log n)
		vector<int> label(n);
		maxDepth = 0;
		depth[root] = 0;
		dfs(root);
		vector<int> code;
		for (int d = maxDepth; d >= 0; d--) {
			vector<pair<vector<int>, int>> sortedNodes;
			for (int u : layers[d]) {
				auto labelComp = [&](int &a, int &b) {
					return label[a] < label[b];
				};
				sort(adj[u].begin(), adj[u].end(), labelComp);
				vector<int> children;
				for (int v : adj[u]) {
					if (depth[v] < depth[u]) continue;
					children.push_back(label[v]);
				}
				sortedNodes.push_back({children, u});
			}
			layers[d].clear();
			sort(sortedNodes.begin(), sortedNodes.end());
			label[sortedNodes[0].second] = 0;
			for (int i = 1; i < sortedNodes.size(); i++) {
				label[sortedNodes[i].second] = label[sortedNodes[i - 1].second];
				if (sortedNodes[i].first != sortedNodes[i - 1].first) {
					label[sortedNodes[i].second]++;
				}
			}
			for (auto p : sortedNodes) {
				int u = p.second;
				vector<int> children;
				code.push_back(-1); //group separator
				for (int v : adj[u]) {
					if (depth[v] < depth[u]) continue;
					code.push_back(label[v]);
				}
			}
		}
		return code;
	}
	
	int size[MX];
	void findSize(int u, int p = -1) {
		size[u] = 1;
		for (int v : adj[u]) {
			if (v != p) {
				findSize(v, u);
				size[u] += size[v];
			}
		}
	}
	
	int findCentroid(int u, int n, int p = -1) {
		for (int v : adj[u]) {
			if (v != p) {
				if (2 * size[v] > n ) {
					return findCentroid(v, n, u);
				}
			}
		}
		return u;
	}
	
	vector<int> getCentroids(int n) {
		findSize(0);
		vector<int> ans = {findCentroid(0, n)};
		for (int v : adj[ans[0]]) {
			if (2 * size[v] == n) {
				ans.push_back(v);
			}
		}
		return ans;
	}
	
	vector<int> encode(int n) { //O(n log n)
		vector<int> centroids = getCentroids(n);
		vector<int> ans = encode(centroids[0], n);
		if (centroids.size() == 1) {
			return ans;
		}
		vector<int> code2 = encode(centroids[1], n);
		if (ans < code2) {
			swap(ans, code2);
		}
		ans.push_back(-2); //tree separator
		for (int c : code2) ans.push_back(c);
		return ans;
	}
} tree;

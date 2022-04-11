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
		dfs(root);
		depth[root] = 0;
		vector<int> code;
		auto labelComp = [&](int &a, int &b) {
			return label[a] < label[b];
		};
		for (int d = maxDepth; d >= 0; d--) {
			vector<pair<vector<int>, int>> sortedNodes;
			for (int u : layers[d]) {
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
				code.push_back(-1); //group separator
				for (int v : adj[u]) {
					if (depth[v] < depth[u]) continue;
					code.push_back(label[v]);
				}
			}
		}
		return code;
	}
} tree;

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const int MX = 1e5;
struct Tree{
	vector<int> adj[MX];
	int parent[MX];
	int depth[MX];
	vector<int> layers[MX];
	int label[MX];
	
	void clear(int n) {
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			parent[i] = -1;
			depth[i] = 0;
			layers[i].clear();
		}
	}
	
	void addEdge(int u , int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int u, int p = -1){
		parent[u] = p;
		layers[depth[u]].push_back(u);
		for(int v : adj[u]){
			if(v == p) continue;
			depth[v] = depth[u] + 1;
			dfs(v, u);
		}
	}
	
	vector<int> encode(int root, int n) {
		dfs(root);
		int maxDepth = 0;
		for (int u = 0; u < n; u++) {
			maxDepth = max(maxDepth, depth[u]);
		}
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
					if (v == parent[u]) continue;
					children.push_back(label[v]);
				}
				sortedNodes.push_back({children, u});
			}
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
				for (int v : adj[u]) {
					if (v == parent[u]) continue;
					code.push_back(label[u]);
					code.push_back(label[v]);
				}
			}
			code.push_back(-1);
		}
		
		return code;
	}
}tree;

int main() {
	return 0;
}

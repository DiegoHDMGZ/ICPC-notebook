#include <bits/stdc++.h>
#define all(v) begin(v), end(v)
using namespace std;

using Long = long long;

const int MX = 1e5;
struct Tree {
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

    vector<int> encode(int root, int n) { // O(n log n)
        // The code has size exactly 2n - 1
        vector<int> label(n);
        maxDepth = 0;
        depth[root] = 0;
        dfs(root);
        vector<int> code;
        vector<vector<int>> children(n);
        auto cmpNode = [&](int &u, int &v) { return children[u] < children[v]; };
        for (int d = maxDepth; d >= 0; d--) {
            sort(layers[d].begin(), layers[d].end(), cmpNode);
            for (int i = 0; i < layers[d].size(); i++) {
                int u = layers[d][i];
                if (i == 0) label[u] = 1;
                else {
                    int prev = layers[d][i - 1];
                    label[u] = label[prev];
                    if (children[u] != children[prev]) {
                        label[u]++;
                    }
                }
                if (d != 0) children[parent[u]].push_back(label[u]);
                code.push_back(0); // group separator
                copy(all(children[u]), back_inserter(code));
            }
            layers[d].clear();
        }
        return code;
    }

    int size[MX];
    void findCentroids(int u, int n, vector<int> &ans, int p = -1) {
        size[u] = 1;
        bool isCentroid = true;
        for (int v : adj[u]) {
            if (v == p) continue;
            findCentroids(v, n, ans, u);
            size[u] += size[v];
            if (size[v] > n / 2) isCentroid = false;
        }
        if (n - size[u] > n / 2) isCentroid = false;
        if (isCentroid) ans.push_back(u);
    }

    vector<int> encode(int n) { // O(n log n)
        // The code has size exactly 2n - 1 or 4n - 2
        vector<int> centroids;
        findCentroids(0, n, centroids);
        vector<int> code1 = encode(centroids[0], n);
        if (centroids.size() == 1) return code1;
        vector<int> code2 = encode(centroids[1], n);
        if (code1 < code2) swap(code1, code2);
        copy(all(code2), back_inserter(code1));
        return code1;
    }
} tree;

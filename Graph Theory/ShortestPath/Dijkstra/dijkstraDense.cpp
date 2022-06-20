#include <bits/stdc++.h>
using namespace std;

using Long = long long;
const Long INF = 1e18;

struct Graph {
    vector<vector<pair<int, Long>>> adj;
    vector<int> parent;
    vector<Long> d;

    Graph(int n) {
        adj.resize(n);
    }

    void addEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int s) { // O(V^2)
        int n = adj.size();
        vector<bool> vis(n, false);
        parent = vector<int>(n, -1);
        d = vector<Long>(n, INF);
        d[s] = 0;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!vis[j] && (u == -1 || d[j] < d[u])) {
                    u = j;
                }
            }
            if (u == -1 || d[u] == INF) break;
            vis[u] = true;
            for (auto [v, w] : adj[u]) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    vector<int> getPath(int u) {
        if (d[u] == INF) return {};
        vector<int> path;
        while (u != -1) {
            path.push_back(u);
            u = parent[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

typedef pair<Long, int> Path;
const Long INF = 1e18;

struct Graph {
    vector<vector<pair<int, Long>>> adj;
    vector<int> parent;
    vector<Long> d;

    Graph(int n) { adj.resize(n); }

    void addEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dijkstra(int s) { // O(E log V)
        int n = adj.size();
        parent = vector<int>(n, -1);
        d = vector<Long>(n, INF);
        priority_queue<Path, vector<Path>, greater<Path>> q;
        d[s] = 0;
        q.push({d[s], s});
        while (!q.empty()) {
            auto [weight, u] = q.top();
            q.pop();
            if (weight != d[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    parent[v] = u;
                    q.push({d[v], v});
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

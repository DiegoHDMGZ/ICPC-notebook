#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

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
        auto cmp = [&](int u, int v) {
            if (d[u] == d[v]) return u < v;
            return d[u] < d[v];
        };
        set<Long, decltype(cmp)> q(cmp);
        d[s] = 0;
        q.insert(s);
        while (!q.empty()) {
            int u = *q.begin();
            q.erase(q.begin());
            for (auto [v, w] : adj[u]) {
                if (d[u] + w < d[v]) {
                    q.erase(v);
                    d[v] = d[u] + w;
                    parent[v] = u;
                    q.insert(v);
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

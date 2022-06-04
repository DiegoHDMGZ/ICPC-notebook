#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

typedef pair<Long, int> Path;
const Long INF = 1e18;

struct Graph {
    vector<vector<pair<int, Long>>> adj;
    vector<int> parent;
    vector<Long> d;
    vector<int> reachedBy;

    Graph(int n) { adj.resize(n); }

    void addEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    Long dijkstra(vector<int> &root) { // O(E log V)
        // return the minimum distance between nodes in root set
        int n = adj.size();
        parent = vector<int>(n, -1);
        d = vector<Long>(n, INF);
        reachedBy = vector<int>(n, -1);
        priority_queue<Path, vector<Path>, greater<Path>> q;
        for (int s : root) {
            d[s] = 0;
            q.push(Path(d[s], s));
            reachedBy[s] = s;
        }
        while (!q.empty()) {
            auto [weight, u] = q.top();
            q.pop();
            if (weight != d[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    parent[v] = u;
                    reachedBy[v] = reachedBy[u];
                    q.push({d[v], v});
                }
            }
        }
        Long minDist = INF;
        for (int u = 0; u < n; u++) {
            if (reachedBy[u] == -1) continue;
            for (auto [v, w] : adj[u]) {
                if (reachedBy[v] == -1) continue;
                if (reachedBy[u] != reachedBy[v]) {
                    minDist = min(minDist, d[u] + d[v] + w);
                }
            }
        }
        return minDist;
    }
};

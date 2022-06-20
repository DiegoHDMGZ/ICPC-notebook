#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Graph {
    vector<pair<Long, Long>> adj[MX];
    Long minWeight[MX];
    Long parent[MX];

    void clear(Long n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    void addEdge(Long u, Long v, Long w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    Long getMST(Long n, Long root = 0) { // O(V^2)
        Long totalWeight = 0;
        vector<bool> onTree(n, false);
        fill(minWeight, minWeight + n, INF);
        minWeight[root] = 0;
        parent[root] = -1;

        for (Long nodes = 1; nodes <= n; nodes++) {
            Long u = -1;
            for (Long i = 0; i < n; i++) {
                if (!onTree[i]) {
                    if (u == -1 || minWeight[i] < minWeight[u]) {
                        u = i;
                    }
                }
            }
            if (minWeight[u] == INF) {
                // graph is not connected
                return -1;
            }
            totalWeight += minWeight[u];
            onTree[u] = true;
            for (auto e : adj[u]) {
                Long v = e.first;
                Long w = e.second;
                if (!onTree[v] && w < minWeight[v]) {
                    minWeight[v] = w;
                    parent[v] = w;
                }
            }
        }
        return totalWeight;
    }
} G;

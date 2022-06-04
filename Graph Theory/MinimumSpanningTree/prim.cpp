#include <bits/stdc++.h>
using namespace std;
typedef long long Long;
typedef pair<Long, Long> Pair;

const Long MX = 1e5;
const Long INF = 1e18;

struct Graph {
    vector<Pair> adj[MX];
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

    Long getMST(Long n, Long root = 0) { // O(E log V)
        Long totalWeight = 0;
        Long totalNodes = 0;
        vector<bool> onTree(n, false);
        fill(minWeight, minWeight + n, INF);
        minWeight[root] = 0;
        parent[root] = -1;
        priority_queue<Pair, vector<Pair>, greater<Pair>> q;
        q.push({0, root});
        while (!q.empty()) {
            Long u = q.top().second;
            q.pop();
            if (onTree[u]) {
                continue;
            }
            totalWeight += minWeight[u];
            onTree[u] = true;
            totalNodes++;
            for (auto e : adj[u]) {
                Long v = e.first;
                Long w = e.second;
                if (w < minWeight[v] && !onTree[v]) {
                    minWeight[v] = w;
                    parent[v] = u;
                    q.push({w, v});
                }
            }
        }
        if (totalNodes != n) return -1;
        return totalWeight;
    }
} G;

#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

const Long MX = 1e4;
const Long INF = 1e18;

struct Graph {
    vector<pair<Long, Long>> adj[MX];
    Long d[MX];
    int parent[MX];
    int reachedBy[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    void addEdge(int u, int v, Long w) { adj[u].push_back({v, w}); }

    void dfs(int u, int root) {
        d[u] = -INF;
        reachedBy[u] = root;
        for (auto e : adj[u]) {
            int v = e.first;
            if (d[v] != -INF) {
                dfs(v, root);
            }
        }
    }

    bool bellmanFord(int s, int n) { // O(VE)
        // true : negative cycle found
        for (int i = 0; i < n; i++) {
            d[i] = INF;
            parent[i] = -1;
        }
        d[s] = 0;
        vector<bool> cycle(n, false);
        bool tense;
        for (int i = 0; i < n; i++) {
            tense = false;
            for (int u = 0; u < n; u++) {
                for (auto e : adj[u]) {
                    int v = e.first;
                    Long w = e.second;
                    if (d[u] != INF && d[u] + w < d[v]) { // tense
                        d[v] = d[u] + w; // relax
                        parent[v] = u;
                        tense = true;
                        if (i == n - 1) {
                            cycle[v] = true;
                        }
                    }
                }
            }
            if (!tense) break;
        }
        for (int u = 0; u < n; u++) {
            if (cycle[u] && d[u] != -INF) {
                dfs(u, u);
            }
        }
        return tense;
    }

    vector<int> getNegativeCycle(int u, int n) {
        assert(d[u] == -INF);
        u = reachedBy[u];
        // go back n times to find a cycle
        for (int i = 0; i < n; i++) {
            u = parent[u];
        }
        vector<int> cycle = {u};
        u = parent[u];
        while (u != cycle[0]) {
            cycle.push_back(u);
            u = parent[u];
        }
        cycle.push_back(cycle[0]);
        reverse(cycle.begin(), cycle.end()); // directed cycle
        return cycle;
    }

    vector<int> getPath(int u) {
        if (d[u] == INF) {
            return {};
        }
        vector<int> path;
        while (u != -1) {
            path.push_back(u);
            u = parent[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
} G;

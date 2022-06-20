#include <bits/stdc++.h>
using namespace std;
using Long = long long;

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

    void addEdge(int u, int v, Long w) {
        adj[u].push_back({v, w});
    }

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

    bool spfa(int s, int n) { // O(VE)
        for (int i = 0; i < n; i++) {
            d[i] = INF;
            parent[i] = -1;
        }
        queue<int> q;
        vector<bool> inQueue(n, false);
        d[s] = 0;
        inQueue[s] = true;
        q.push(s);
        int phase = 0;
        while (!q.empty() && phase < n) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int u = q.front();
                q.pop();
                inQueue[u] = false;
                for (auto e : adj[u]) {
                    int v = e.first;
                    Long w = e.second;
                    if (d[u] + w < d[v]) {
                        d[v] = d[u] + w;
                        parent[v] = u;
                        if (!inQueue[v]) {
                            q.push(v);
                            inQueue[v] = true;
                        }
                    }
                }
            }
            phase++;
        }
        if (q.empty()) return false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (d[u] != -INF) {
                dfs(u, u);
            }
        }
        return true;
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
        if (d[u] == INF) return {};
        vector<int> path;
        while (u != -1) {
            path.push_back(u);
            u = parent[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
} G;

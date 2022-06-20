#include <bits/stdc++.h>
using namespace std;

// This implementation is for small graphs G(V, E) (|V| <= 3000 aprox)
// where O(|V|^2) memory will fit the memory limit.

using Cap = long long;
const int MX = 3000;
const Cap INF = 1e18;

struct Graph {
    vector<int> adj[MX];
    Cap cap[MX][MX];
    Cap flow[MX][MX];
    bool vis[MX];
    bool added[MX][MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            for (int j = 0; j < n; j++) {
                cap[i][j] = 0;
                flow[i][j] = 0;
                added[i][j] = false;
            }
        }
    }

    void addEdge(int u, int v, Cap w, bool dir) {
        if (!added[u][v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            added[u][v] = added[v][u] = true;
        }
        cap[u][v] += w;
        if (!dir) cap[v][u] += w;
    }

    Cap dfs(int u, int t, Cap f) { // O(E)
        if (u == t) return f;
        if (vis[u]) return 0;
        vis[u] = true;
        for (int v : adj[u]) {
            Cap cf = cap[u][v] - flow[u][v];
            if (cf == 0) continue;
            Cap ret = dfs(v, t, min(f, cf));
            if (ret > 0) {
                flow[u][v] += ret;
                flow[v][u] -= ret;
                return ret;
            }
        }
        return 0;
    }

    Cap maxFlow(int s, int t, int n) { // O(E * |F|)
        // As the graph is simple, O(|F|) = O(V * u)
        Cap ans = 0;
        while (true) { // O(|F|) iterations
            fill(vis, vis + n, false);
            Cap inc = dfs(s, t, INF);
            if (inc == 0) break;
            ans += inc;
        }
        return ans;
    }
} G;

#include <bits/stdc++.h>
using namespace std;

// This implementation is for small graphs G(V, E) (|V| <= 3000 aprox)
// where O(|V|^2) memory will fit the memory limit.

typedef long long Cap;
const int MX = 3000;
const Cap INF = 1e18;

struct Graph {
    vector<int> adj[MX];
    Cap cap[MX][MX];
    Cap flow[MX][MX];
    bool added[MX][MX];
    int level[MX];
    int nextEdge[MX];

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
        for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
            int v = adj[u][i];
            Cap cf = cap[u][v] - flow[u][v];
            if (cf == 0 || level[v] != level[u] + 1) continue;
            Cap ret = dfs(v, t, min(f, cf));
            if (ret > 0) {
                flow[u][v] += ret;
                flow[v][u] -= ret;
                return ret;
            }
        }
        return 0;
    }

    bool bfs(int s, int t, int n) { // O(E)
        fill(level, level + n, -1);
        queue<int> q({s});
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            nextEdge[u] = 0;
            q.pop();
            for (int v : adj[u]) {
                Cap cf = cap[u][v] - flow[u][v];
                if (level[v] == -1 && cf > 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    Cap maxFlow(int s, int t, int n) {
        // General: O(E * V^2), O(E * V + V * |F|)
        // Unit Cap: O(E * min(E^(1/2) , V^(2/3)))
        // Unit Network: O(E * V^(1/2))
        // In unit network, all the edges have unit capacity
        // and for any vertex except s and t either the
        // incoming or outgoing edge is unique.
        Cap ans = 0;
        while (bfs(s, t, n)) { // O(V) iterations
            // after bfs, the graph is a DAG
            while (Cap inc = dfs(s, t, INF)) ans += inc;
        }
        return ans;
    }
} G;

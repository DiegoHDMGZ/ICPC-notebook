#include <bits/stdc++.h>
using namespace std;

using Cap = long long;

const int MX = 5000;
const Cap INF = 1e18;

struct Edge {
    int to;
    Cap flow, cap;
    int rev; // index of the backward edge in the adj list of to
    Edge(int to, Cap cap, int rev) : to(to), flow(0), cap(cap), rev(rev) {}
};

struct Graph {
    vector<Edge> adj[MX];
    int level[MX];
    int nextEdge[MX];
    Cap maxCap = 0;
    Cap lowFlow;

    void clear(int n) {
        for (int i = 0; i < n; i++) adj[i].clear();
        maxCap = 0;
    }

    void addEdge(int u, int v, Cap w, bool dir) {
        adj[u].push_back(Edge(v, w, adj[v].size()));
        adj[v].push_back(Edge(u, dir ? 0 : w, adj[u].size() - 1));
        maxCap = max(maxCap, w);
    }

    Cap dfs(int u, int t, Cap f) {
        if (u == t) return f;
        for (int &i = nextEdge[u]; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            int v = e.to;
            Edge &rev = adj[v][e.rev];
            Cap cf = e.cap - e.flow;
            if (cf < lowFlow || level[v] != level[u] + 1) continue;
            Cap ret = dfs(v, t, min(f, cf));
            if (ret > 0) {
                e.flow += ret;
                rev.flow -= ret;
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
            if (u == t) return true;
            for (Edge e : adj[u]) {
                int v = e.to;
                Cap cf = e.cap - e.flow;
                if (level[v] == -1 && cf >= lowFlow) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return false;
    }

    Cap maxFlow(int s, int t, int n) {
        // All capacities must be integers in order to apply scaling
        // General: O(E * V * log U)
        if (maxCap == 0) return 0;
        int lg = 63 - __builtin_clzll(maxCap);
        Cap ans = 0;
        for (lowFlow = (1LL << lg); lowFlow >= 1; lowFlow >>= 1) {
            while (bfs(s, t, n)) { // O(V) iterations
                while (Cap inc = dfs(s, t, INF)) ans += inc;
            }
        }
        return ans;
    }
} G;

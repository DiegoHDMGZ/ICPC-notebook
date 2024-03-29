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
    int parentEdge[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) adj[i].clear();
    }

    void addEdge(int u, int v, Cap w, bool dir) {
        adj[u].push_back(Edge(v, w, adj[v].size()));
        adj[v].push_back(Edge(u, dir ? 0 : w, adj[u].size() - 1));
    }

    void pushFlow(int s, int t, Cap inc) {
        int v = t;
        while (v != s) {
            Edge &backward = adj[v][parentEdge[v]];
            int u = backward.to;
            Edge &forward = adj[u][backward.rev];
            forward.flow += inc;
            backward.flow -= inc;
            v = u;
        }
    }

    Cap bfs(int s, int t, int n) { // O(E)
        fill(parentEdge, parentEdge + n, -1);
        vector<Cap> residualCap(n, 0);
        queue<int> q({s});
        parentEdge[s] = -2;
        residualCap[s] = INF;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) {
                pushFlow(s, t, residualCap[t]);
                return residualCap[t];
            }
            for (auto e : adj[u]) {
                int v = e.to;
                Cap cf = e.cap - e.flow;
                if (parentEdge[v] == -1 && cf > 0) {
                    parentEdge[v] = e.rev;
                    residualCap[v] = min(residualCap[u], cf);
                    q.push(v);
                }
            }
        }
        return 0;
    }

    Cap maxFlow(int s, int t, int n) { // O(E * min(E * V , |F|))
        Cap ans = 0;
        while (Cap inc = bfs(s, t, n)) ans += inc;
        return ans;
    }
} G;

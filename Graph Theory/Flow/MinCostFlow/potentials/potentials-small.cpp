#include <bits/stdc++.h>
using namespace std;

// Find the maximum flow that has minimum cost.
// Costs can be negative but there must be no negative cycle initially.

// This implementation is for small graphs G(V, E) (|V| <= 3000 aprox)
// where O(|V|^2) memory will fit the memory limit.
// So a 2D array can be used to speed up the algorithm a little bit.
// WARNING: No multi-edges allowed.
// No antiparallel edges allowed i.e. No (u, v) (v, u) at the same time

using Cap = long long;
using Cost = long long;

const int MX = 2005;
const Cap INF_CAP = 1e18;
const Cost INF_COST = 1e18;

struct Graph {
    vector<int> adj[MX];
    Cap cap[MX][MX];
    Cap flow[MX][MX];
    Cost cost[MX][MX];
    int parent[MX];
    bool inQueue[MX];
    Cost pot[MX];
    // |pot[u]| <= the maximum sum of absolute cost in a path
    // which is also bounded by [(V - 1) * C]
    // where C is the maximum value of |cost(e)| for all edges e
    void clear(int n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            pot[i] = 0;
            for (int j = 0; j < n; j++) {
                cap[i][j] = 0;
                flow[i][j] = 0;
                cost[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, Cap w, Cost c) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = w;
        cost[u][v] = c;
        cost[v][u] = -c;
    }

    void spfa(int s, int n) { // O(E V)
        for (int i = 0; i < n; i++) pot[i] = INF_COST;
        queue<int> q({s});
        pot[s] = 0;
        inQueue[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            for (int v : adj[u]) {
                if (cap[u][v] - flow[u][v] > 0 && pot[u] + cost[u][v] < pot[v]) {
                    pot[v] = pot[u] + cost[u][v];
                    if (!inQueue[v]) q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    void pushFlow(int s, int t, Cap inc) {
        int v = t;
        while (v != s) {
            int u = parent[v];
            flow[u][v] += inc;
            flow[v][u] -= inc;
            v = u;
        }
    }

    pair<Cap, Cost> dijkstra(int s, int t, int n) { // O(E log V)
        //<flow, cost>
        using Path = pair<Cost, int>; //<weight, node>
        priority_queue<Path, vector<Path>, greater<Path>> q;
        vector<Cost> d(n, INF_COST);
        vector<Cap> residualCap(n, 0);
        d[s] = 0;
        residualCap[s] = INF_CAP;
        q.push(Path(d[s], s));
        while (!q.empty()) {
            auto [dist, u] = q.top();
            q.pop();
            if (dist != d[u]) continue;
            for (int v : adj[u]) {
                Cap cf = cap[u][v] - flow[u][v];
                Cost c = cost[u][v] + pot[u] - pot[v];
                if (cf > 0 && d[u] + c < d[v]) {
                    assert(c >= 0);
                    d[v] = d[u] + c;
                    q.push(Path(d[v], v));
                    residualCap[v] = min(residualCap[u], cf);
                    parent[v] = u;
                }
            }
        }
        if (d[t] == INF_COST) return {0, 0};
        for (int i = 0; i < n; i++) {
            if (pot[i] != INF_COST) pot[i] += d[i];
        }
        Cap cf = residualCap[t];
        pushFlow(s, t, cf);
        return {cf, pot[t] * cf};
    }

    // For dense graph, the quadratic version can be used
    /*pair<Cap, Cost> dijkstra(int s, int t, int n) { // O(V^2)
        // <flow, cost>
        vector<Cost> d(n, INF_COST);
        vector<bool> vis(n, false);
        vector<Cap> residualCap(n, 0);
        d[s] = 0;
        residualCap[s] = INF_CAP;
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!vis[j] && (u == -1 || d[j] < d[u])) u = j;
            }
            if (u == -1 || d[u] == INF_COST) break;
            vis[u] = true;
            for (int v : adj[u]) {
                Cap cf = cap[u][v] - flow[u][v];
                Cost c = cost[u][v] + pot[u] - pot[v];
                if (cf > 0 && d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    residualCap[v] = min(residualCap[u], cf);
                    parent[v] = u;
                }
            }
        }
        if (d[t] == INF_COST) return {0, 0};
        for (int i = 0; i < n; i++) {
            if (pot[i] != INF_COST) pot[i] += d[i];
        }
        Cap cf = residualCap[t];
        pushFlow(s, t, cf);
        return {cf, pot[t] * cf};
    }*/

    pair<Cap, Cost> minCostFlow(int s, int t, int n) {
        // O(E log V *  maxFlow)
        // maxFlow <= V * U, where U is the maximum capacity
        // Initially no negative cycles
        //<maxFlow, minCost>
        spfa(s, n); // not necessary if there is no negative edges
        pair<Cap, Cost> inc;
        Cap f = 0;
        Cost c = 0;
        do {
            inc = dijkstra(s, t, n);
            f += inc.first;
            c += inc.second;
        } while (inc.first > 0);
        return {f, c};
    }
} G;

#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

// Find the maximum flow that has minimum cost.
// Costs can be negative but there must be no negative cycle initially.

typedef long long Cap;
typedef long long Cost;

const int MX = 5000;
const Cap INF_CAP = 1e18;
const Cost INF_COST = 1e18;

struct Edge {
    int to;
    Cap flow, cap;
    Cost cost;
    int rev; // index of the backward edge in the adj list of to
    Edge(int to, Cap cap, Cost cost, int rev)
        : to(to), flow(0), cap(cap), cost(cost), rev(rev) {}
};

struct Graph {
    vector<Edge> adj[MX];
    int parentEdge[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) adj[i].clear();
    }

    void addEdge(int u, int v, Cap w, Cost cost, bool dir) {
        adj[u].push_back(Edge(v, w, cost, adj[v].size()));
        adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
        if (!dir) addEdge(v, u, w, cost, true);
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

    pair<Cap, Cost> spfa(int s, int t, int n) { // O(E V)
        //<flow, cost>
        vector<Cost> d(n, INF_COST);
        vector<bool> inQueue(n, false);
        vector<Cap> residualCap(n, 0);
        queue<int> q;
        d[s] = 0;
        residualCap[s] = INF_CAP;
        inQueue[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;
            for (Edge e : adj[u]) {
                int v = e.to;
                Cap cf = e.cap - e.flow;
                if (cf > 0 && d[u] + e.cost < d[v]) {
                    d[v] = d[u] + e.cost;
                    if (!inQueue[v]) q.push(v);
                    parentEdge[v] = e.rev;
                    residualCap[v] = min(residualCap[u], cf);
                    inQueue[v] = true;
                }
            }
        }
        if (d[t] == INF_COST) return {0, 0};
        Cap cf = residualCap[t];
        pushFlow(s, t, cf);
        return {cf, d[t] * cf};
    }

    pair<Cap, Cost> minCostFlow(int s, int t, int n) {
        // O(E * V * maxFlow )
        // maxFlow <= V * U, where U is the maximum capacity
        // Assumption: Initially no negative cycles
        // <maxFlow, minCost>
        pair<Cap, Cost> inc;
        Cap flow = 0;
        Cost cost = 0;
        do {
            inc = spfa(s, t, n);
            flow += inc.first;
            cost += inc.second;
        } while (inc.first > 0);
        return {flow, cost};
    }
} G;

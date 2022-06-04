#include <bits/stdc++.h>
using namespace std;

/*
The algorithm first use Dinic to find any max flow. Then, it finds
the minimum circulation finding negative cycles in the residual graph.

This algorithm DOES work even when the initial graph has negative
cycles.
*/

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
    Edge() {}
    Edge(int to, Cap cap, Cost cost, int rev)
        : to(to), flow(0), cap(cap), cost(cost), rev(rev) {}
};

struct Graph {
    vector<Edge> adj[MX];
    int level[MX];
    int nextEdge[MX];
    int parentEdge[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) adj[i].clear();
    }

    void addEdge(int u, int v, Cap w, Cost cost, bool dir) {
        adj[u].push_back(Edge(v, w, cost, adj[v].size()));
        adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
        if (u == v) adj[u].end()[-2].rev++;
        if (!dir && u != v) addEdge(v, u, w, cost, true);
    }

    //******** Dinic's Algorithm ********
    Cap maxFlow(int s, int t, int n);
    //******** End Dinic's Algorithm ********

    Cost costCycle(int v, int n) {
        // go back n times to find a cycle
        for (int i = 0; i < n; i++) v = adj[v][parentEdge[v]].to;
        Cap cf = INF_CAP;
        int start = v;
        do {
            Edge backward = adj[v][parentEdge[v]];
            int u = backward.to;
            Edge forward = adj[u][backward.rev];
            cf = min(cf, forward.cap - forward.flow);
            v = u;
        } while (v != start);
        start = v;
        Cost cost = 0;
        do {
            Edge &backward = adj[v][parentEdge[v]];
            int u = backward.to;
            Edge &forward = adj[u][backward.rev];
            cost += cf * forward.cost;
            forward.flow += cf;
            backward.flow -= cf;
            v = u;
        } while (v != start);
        return cost;
    }

    Cost spfa(int n) { // O(E V)
        vector<Cost> d(n, 0);
        queue<int> q;
        vector<bool> inQueue(n, true);
        for (int u = 0; u < n; u++) q.push(u);
        int phase = 0;
        while (!q.empty() && phase < n) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int u = q.front();
                q.pop();
                inQueue[u] = false;
                for (Edge e : adj[u]) {
                    int v = e.to;
                    Cap cf = e.cap - e.flow;
                    if (cf > 0 && d[u] + e.cost < d[v]) {
                        d[v] = d[u] + e.cost;
                        parentEdge[v] = e.rev;
                        if (!inQueue[v]) {
                            q.push(v);
                            inQueue[v] = true;
                        }
                    }
                }
            }
            phase++;
        }
        if (!q.empty()) return costCycle(q.front(), n);
        // no negative cycle
        return 0;
    }

    pair<Cap, Cost> minCostFlow(int s, int t, int n) {
        // O(dinic + EV * |totalCost|)
        //|totalCost| <= E * U * C, where U is max cap and C max cost
        //<maxFlow, minCost>
        Cap flow = maxFlow(s, t, n);
        Cost cost = 0;
        for (int u = 0; u < n; u++) {
            for (auto e : adj[u]) {
                if (e.flow > 0) cost += e.cost * e.flow;
            }
        }
        Cost inc;
        do {
            inc = spfa(n);
            cost += inc;
        } while (inc < 0);
        return {flow, cost};
    }
} G;

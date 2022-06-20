#include <bits/stdc++.h>
using namespace std;

/*Find the maximum flow that has minimum cost.
This algorithm DOES work even when the initial graph has negative
cycles*/

using Cap = long long;
using Cost = long long;

const int MX = 5000;
const Cap INF_CAP = 1e18;

struct Edge {
    int to;
    Cap flow, cap;
    Cost cost;
    int rev; // index of the backward edge in the adj list of to
    Edge(int to, Cap cap, Cost cost, int rev)
        : to(to), flow(0), cap(cap), cost(cost), rev(rev) {}

    Cap resCap() const {
        return cap - flow;
    }
};

struct Graph {
    vector<Edge> adj[MX];
    int parentEdge[MX];
    Cost pot[MX];
    // After every minCirculation call
    // minCost <= pot[u] <= 0, where minCost is the minimum
    // sum of negative absolute values of cost
    // minCost is bounded by -sum(|cost(e)|)
    // It's also bounded by -(V - 1) * C and
    // where C is the maximum value of |cost(e)| for all edges e
    // However some intermediate results may have 3 * minCost - 1 <= pot[u]
    Cap maxCap = 0;
    Cost minCost = 0;
    Cap lowFlow;

    void clear(int n) {
        maxCap = 0;
        minCost = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            pot[i] = 0;
        }
    }

    void addEdge(int u, int v, Cap w, Cost cost, bool dir) {
        adj[u].push_back(Edge(v, w, cost, adj[v].size()));
        adj[v].push_back(Edge(u, 0, -cost, adj[u].size() - 1));
        if (u == v) adj[u].end()[-2].rev++;
        maxCap = max(maxCap, w);
        minCost = min(minCost, -abs(cost));
        if (!dir) addEdge(v, u, w, cost, true);
    }

    Cost resCost(const Edge &e) const {
        int v = e.to;
        if (e.rev == -1) return e.cost - pot[v];
        int u = adj[e.to][e.rev].to;
        return e.cost + pot[u] - pot[v];
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

    void dijkstra(vector<Cost> &d, vector<Cap> &bottleneck) {
        using Path = pair<Cost, int>; //<weight, node>
        priority_queue<Path, vector<Path>, greater<Path>> q;
        int n = d.size();
        for (int u = 0; u < n; u++) q.push(Path(d[u], u));
        while (!q.empty()) {
            auto [dist, u] = q.top();
            q.pop();
            if (dist != d[u]) continue;
            for (Edge e : adj[u]) {
                int v = e.to;
                if (e.resCap() < lowFlow) continue;
                if (resCost(e) < 0) continue;
                if (d[u] + resCost(e) < d[v]) {
                    d[v] = d[u] + resCost(e);
                    q.push(Path(d[v], v));
                    bottleneck[v] = min(bottleneck[u], e.resCap());
                    parentEdge[v] = e.rev;
                }
            }
        }
    }

    pair<Cap, Cost> minCirculation(int s, int t, int n, Edge &ts) {
        // O(E log V)
        // tsCap = 0 means we are looking for an st-path
        // tsCap > 0 means we are looking for negative cycle from s to t
        vector<Cost> d(n, 0);
        vector<Cap> bottleneck(n, 0);
        d[s] = resCost(ts);
        bottleneck[s] = INF_CAP;
        dijkstra(d, bottleneck);
        for (int u = 0; u < n; u++) pot[u] += d[u];
        pair<Cap, Cost> ans;
        if (d[t] >= 0) ans = {0, 0};
        else {
            Cap cf = bottleneck[t];
            if (ts.resCap() > 0) {
                cf = min(cf, ts.resCap());
                ans = {cf, d[t] * cf};
                ts.flow += cf;
                adj[ts.to][ts.rev].flow -= cf;
            } else ans = {cf, (pot[t] - ts.cost) * cf};
            pushFlow(s, t, cf);
        }
        // Potentials adjustment
        // Some potentials may have repeated edge cost
        for (int u = 0; u < n; u++) d[u] = -pot[u];
        dijkstra(d, bottleneck);
        for (int u = 0; u < n; u++) pot[u] += d[u];
        return ans;
    }

    pair<Cap, Cost> minCostFlow(int s, int t, int n) {
        // O(E^2 * log V * log U) where U is the maximum capacity
        //<maxFlow, minCost>
        if (maxCap == 0) return {0, 0};
        minCost *= (n - 1);
        int lg = 63 - __builtin_clzll(maxCap);
        pair<Cap, Cost> inc;
        Cap totalFlow = 0;
        Cost totalCost = 0;
        for (lowFlow = (1LL << lg); lowFlow >= 1; lowFlow >>= 1) {
            // push flow through negative cycles
            for (int u = 0; u < n; u++) {
                for (auto &e : adj[u]) {
                    int v = e.to;
                    if (e.resCap() >= lowFlow && resCost(e) < 0) {
                        inc = minCirculation(v, u, n, e);
                        totalCost += inc.second;
                    }
                }
            }
            // normal shortest augmenting path
            do {
                Edge circleEdge = Edge(s, 0, 2 * minCost - 1, -1);
                inc = minCirculation(s, t, n, circleEdge);
                totalFlow += inc.first;
                totalCost += inc.second;
            } while (inc.first > 0);
        }
        return {totalFlow, totalCost};
    }
} G;

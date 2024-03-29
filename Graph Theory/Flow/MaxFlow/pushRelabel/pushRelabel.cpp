#include <bits/stdc++.h>
using namespace std;
using Long = long long;

const Long MX = 3000;
const Long INF = 1e18;

struct Graph {
    vector<Long> adj[MX];
    Long cap[MX][MX];
    Long flow[MX][MX];
    bool added[MX][MX];
    Long e[MX]; // excess
    Long h[MX]; // height function
    deque<Long> overflowing;

    void clear(Long N = MX) {
        overflowing.clear();
        for (Long i = 0; i < N; i++) {
            adj[i].clear();
            e[i] = 0;
            h[i] = 0;
            for (Long j = 0; j < N; j++) {
                cap[i][j] = 0;
                flow[i][j] = 0;
                added[i][j] = false;
            }
        }
    }

    void addEdge(Long u, Long v, Long w, bool dir) {
        if (!added[min(u, v)][max(u, v)]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        added[min(u, v)][max(u, v)] = true;
        cap[u][v] += w;
        if (!dir) {
            cap[v][u] += w;
        }
    }

    void push(Long u, Long v) {
        Long cf = cap[u][v] - flow[u][v];
        Long dif = min(e[u], cf);
        flow[u][v] += dif;
        flow[v][u] -= dif;
        e[u] -= dif;
        e[v] += dif;
        if (e[v] == dif) {
            overflowing.push_back(v);
        }
    }

    void relabel(Long u, Long minHeight) {
        h[u] = 1 + minHeight;
    }

    void discharge(Long u) {
        while (e[u] > 0) {
            Long minHeight = INF;
            for (Long v : adj[u]) {
                if (cap[u][v] - flow[u][v] > 0) {
                    if (h[u] == h[v] + 1) {
                        push(u, v);
                    }
                    minHeight = min(minHeight, h[v]);
                    if (e[u] == 0) {
                        return;
                    }
                }
            }
            if (e[u] > 0) {
                relabel(u, minHeight);
            }
        }
    }

    Long maxFlow(Long s, Long t, Long n) { // O(V ^ 3)
        // General push-relabel without discharge runs in O((E * V * min(V , |F|))
        h[s] = n - 2;
        e[s] = 0;
        for (Long v : adj[s]) {
            flow[s][v] += cap[s][v];
            flow[v][s] -= cap[s][v];
            e[s] -= cap[s][v];
            e[v] += cap[s][v];
            overflowing.push_back(v);
        }
        while (!overflowing.empty()) {
            Long u = overflowing.front();
            overflowing.pop_front();
            if (u == s || u == t) {
                continue;
            }
            discharge(u);
        }
        return -e[s];
    }
} G;

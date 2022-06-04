#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long INF = 1e18;
const Long MX = 1e5;

struct Graph {
    Long d[MX];
    vector<Long> adj[MX];

    void clear(Long n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    void addEdge(Long u, Long v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void bfs(Long s, Long n) { // O(V + E)
        for (Long i = 0; i < n; i++) {
            d[i] = INF;
        }
        d[s] = 0;
        deque<Long> q;
        q.push_back(s);
        while (!q.empty()) {
            Long u = q.front();
            q.pop_front();
            for (Long v : adj[u]) {
                if (d[v] == INF) {
                    d[v] = d[u] + 1;
                    q.push_back(v);
                }
            }
        }
    }
} G;

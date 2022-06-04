#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 4e5;

struct Edge {
    Long u, v;
    Edge() {}
    Edge(Long u, Long v) : u(u), v(v) {}
};

struct Graph {
    vector<int> adj[MX];
    bool vis[MX];
    int tIn[MX]; // entry time
    int low[MX];
    // if S[u] = {Set of this node and all of its sucessors}
    // low[u] = min entry time of S[u] U {all parents of S[u]}
    int timer;
    vector<Edge> bridges;
    vector<int> articulations;
    bool isArticulation[MX];
    map<int, bool> isBridge[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = false;
            tIn[i] = 0;
            low[i] = 0;
            isArticulation[i] = false;
            isBridge[i].clear();
        }
        bridges.clear();
        articulations.clear();
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = -1) { // O(V + E)
        vis[u] = true;
        tIn[u] = low[u] = timer++;
        int children = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (vis[v]) {
                low[u] = min(low[u], tIn[v]);
            } else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tIn[u]) {
                    bridges.push_back(Edge(u, v));
                    isBridge[min(u, v)][max(u, v)] = true;
                }
                if (low[v] >= tIn[u] && p != -1 && !isArticulation[u]) {
                    articulations.push_back(u);
                    isArticulation[u] = true;
                }
                children++;
                if (p == -1 && children > 1) {
                    if (!isArticulation[u]) {
                        isArticulation[u] = true;
                        articulations.push_back(u);
                    }
                }
            }
        }
    }

    void calculate(int n) { // O(V + E)
        timer = 0;
        for (int u = 0; u < n; u++) {
            if (!vis[u]) {
                dfs(u);
            }
        }
    }
} G;

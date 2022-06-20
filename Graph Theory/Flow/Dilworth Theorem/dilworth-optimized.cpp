#include <bits/stdc++.h>
using namespace std;

using Long = long long;
using Cap = int;
const int MX = 3000;

// This template does not build the entire transitive edges

struct Edge {
    int to;
    Cap flow, cap;
    int rev; // index of the backward edge in the adj list of to
    Edge(int to, Cap cap, int rev) : to(to), flow(0), cap(cap), rev(rev) {}
};

struct GraphFlow {
    // max flow template
    // Use 2 * MX + 2 for the array sizes
    vector<Edge> adj[2 * MX + 2];
    void clear(int n);
    void addEdge(int u, int v, Cap w, bool dir);
    Cap maxFlow(int s, int t, int n);
} GFlow;

struct Graph {
    void clear(int n) {
        GFlow.clear(2 * n + 2);
    }
    int left(int u) {
        return 2 * u;
    }
    int right(int u) {
        return 2 * u + 1;
    }
    int getOriginal(int u) {
        return u / 2;
    }
    int getSource(int n) {
        return 2 * n;
    }
    int getTarget(int n) {
        return 2 * n + 1;
    }

    void addEdge(int u, int v) {
        GFlow.addEdge(left(u), right(v), MX, true);
    }

    int maxAntiChainSize(int n) {
        // O(E * V) for FF/Dinic
        // n is the number of nodes in the original graph
        int s = 2 * n;
        int t = 2 * n + 1;
        for (int u = 0; u < n; u++) {
            GFlow.addEdge(s, left(u), 1, true);
            GFlow.addEdge(right(u), t, 1, true);
            GFlow.addEdge(right(u), left(u), n, true);
        }
        return n - GFlow.maxFlow(s, t, 2 * n + 2);
    }

    vector<vector<int>> getMinChainPartition(int n) {
        // Only usable when maxAntiChainSize has been called before
        vector<int> match(n, -1);
        vector<int> indegree(n);
        int s = getSource(n);
        vector<Edge> returnFlow;
        for (auto eS : GFlow.adj[s]) {
            if (eS.flow == 1) {
                int u = eS.to;
                int cur = u;
                while (true) {
                    for (auto &e : GFlow.adj[cur]) {
                        if (e.flow > 0) {
                            int v = e.to;
                            e.flow--;
                            returnFlow.push_back(GFlow.adj[e.to][e.rev]);
                            if (indegree[getOriginal(v)] == 0) {
                                indegree[getOriginal(v)] = 1;
                                match[getOriginal(u)] = getOriginal(v);
                            } else {
                                cur = v - 1;
                            }
                            break;
                        }
                    }
                    if (match[getOriginal(u)] != -1) break;
                }
            }
        }
        for (auto e : returnFlow) GFlow.adj[e.to][e.rev].flow++;
        vector<vector<int>> partition;
        for (int u = 0; u < n; u++) {
            if (indegree[u] == 0) {
                vector<int> chain;
                int cur = u;
                while (cur != -1) {
                    chain.push_back(cur);
                    cur = match[cur];
                }
                partition.push_back(chain);
            }
        }
        return partition;
    }

    bool inS[2 * MX + 2];
    void expandCut(int u) {
        inS[u] = true;
        for (auto e : GFlow.adj[u]) {
            if (e.cap - e.flow > 0 && !inS[e.to]) expandCut(e.to);
        }
    }

    vector<int> getMaxAntichain(int n) {
        // Only usable when maxAntiChainSize has been called before
        int s = getSource(n);
        int t = getTarget(n);
        expandCut(s);
        vector<bool> cover(n, false);
        for (auto e : GFlow.adj[s]) {
            if (!inS[e.to]) {
                cover[getOriginal(e.to)] = true;
            }
        }
        for (auto e : GFlow.adj[t]) {
            if (inS[e.to]) {
                cover[getOriginal(e.to)] = true;
            }
        }
        vector<int> antichain;
        for (int u = 0; u < n; u++) {
            if (!cover[u]) antichain.push_back(u);
        }
        return antichain;
    }
} G;

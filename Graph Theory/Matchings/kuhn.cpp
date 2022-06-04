#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

// Maximum matching for bipartite unweighted graphs

const int MX = 1000;
struct Graph {
    int match[MX];
    bool vis[MX];
    vector<int> adj[MX];
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool dfs(int u) {
        if (vis[u]) return false;
        vis[u] = true;
        for (int v : adj[u]) {
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

    int maximumMatching(int n) { // O(V * E)
        // If the bipartition is (V1, V2) we can iterate from the side
        // that have less nodes (say is V1) and achieve O(V1 * E)
        fill(match, match + n, -1);
        int ans = 0;
        for (int u = 0; u < n; u++) {
            if (match[u] == -1) {
                fill(vis, vis + n, false);
                ans += dfs(u);
            }
        }
        return ans;
    }
} G;

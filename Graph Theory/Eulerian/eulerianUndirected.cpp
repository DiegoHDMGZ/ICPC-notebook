#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

// Theory: http://www.math.caltech.edu/~2014-15/1term/ma006a/class8.pdf
// Eulerian Path: A path (with possible repeated vertices) that visits
// every edge exactly once
// Eulerian cycle: An eulerian path that start and ends in the same vertex

const int MX = 1e5;

struct Graph {
    vector<int> adj[MX];
    vector<pair<int, int>> edges;

    void clear(int n) {
        edges.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }

    vector<int> hierholzer(int n, int start) {
        vector<vector<pair<int, int>>> endpoint(n);
        for (int i = 0; i < edges.size(); i++) {
            auto e = edges[i];
            int u = e.first;
            int v = e.second;
            endpoint[u].push_back({v, i});
            endpoint[v].push_back({u, i});
        }
        vector<bool> used(edges.size(), false);
        vector<int> curPath = {start};
        vector<int> path;
        while (!curPath.empty()) {
            int u = curPath.back();
            while (!endpoint[u].empty() && used[endpoint[u].back().second]) {
                endpoint[u].pop_back();
            }
            if (endpoint[u].empty()) {
                path.push_back(u);
                curPath.pop_back();
            } else {
                int v = endpoint[u].back().first;
                curPath.push_back(v);
                used[endpoint[u].back().second] = true;
                endpoint[u].pop_back();
            }
        }
        if (path.size() != edges.size() + 1) return {};
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> getEulerianCycle(int n, int start = -1) {
        // it has to be connected (but it can be isolated vertices)
        // all vertices have to have even degree
        // if no eulerian cycle exists, an empty array is returned
        for (int u = 0; u < n; u++) {
            if ((adj[u].size() & 1) != 0) return {};
            if (adj[u].size() > 0 && start == -1) start = u;
        }
        if (start == -1) start = 0;
        return hierholzer(n, start);
    }

    vector<int> getEulerianPath(int n, int start = -1) {
        // it has to be connected (but it can be isolated vertices)
        // there has to be exactly 2 nodes with odd degree
        // if no eulerian path exists, an empty array is returned
        vector<int> odd;
        for (int u = 0; u < n; u++) {
            if ((adj[u].size() & 1) == 1) {
                odd.push_back(u);
            }
        }
        if (odd.size() != 2) return {};
        if (start == -1) start = odd[0];
        if (start != odd[0] && start != odd[1]) return {};
        return hierholzer(n, start);
    }
} G;

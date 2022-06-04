#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

// Theory: http://www.math.caltech.edu/~2014-15/1term/ma006a/class8.pdf
// Eulerian Path: A path (with possible repeated vertices) that visits
// every edge exactly once
// Eulerian cycle: An eulerian path that start and ends in the same vertex

const int MX = 1e5;

struct Graph {
    int indegree[MX];
    int outdegree[MX];
    vector<pair<int, int>> edges;

    void clear(int n) {
        edges.clear();
        for (int i = 0; i < n; i++) {
            indegree[i] = outdegree[i] = 0;
        }
    }
    void addEdge(int u, int v) {
        indegree[v]++;
        outdegree[u]++;
        edges.push_back({u, v});
    }

    vector<int> hierholzer(int n, int start) {
        vector<vector<int>> endpoint(n);
        for (int i = 0; i < edges.size(); i++) {
            auto e = edges[i];
            int u = e.first;
            int v = e.second;
            endpoint[u].push_back(v);
        }
        vector<int> curPath = {start};
        vector<int> path;
        while (!curPath.empty()) {
            int u = curPath.back();
            if (endpoint[u].empty()) {
                path.push_back(u);
                curPath.pop_back();
            } else {
                int v = endpoint[u].back();
                curPath.push_back(v);
                endpoint[u].pop_back();
            }
        }
        if (path.size() != edges.size() + 1) return {};
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> getEulerianCycle(int n, int start = -1) {
        // it has to be weakly connected (but it can be isolated vertices)
        // in all vertices, indegree = outdegree
        // if no eulerian cycle exists, an empty array is returned
        for (int u = 0; u < n; u++) {
            if (indegree[u] != outdegree[u]) return {};
            if (outdegree[u] > 0 && start == -1) start = u;
        }
        if (start == -1) start = 0;
        return hierholzer(n, start);
    }

    vector<int> getEulerianPath(int n, int start = -1) {
        // it has to be weakly connected (but it can be isolated vertices)
        // in all vertices, indegree = outdegree except for two vertices.
        // The first with outdegree - indegree = 1
        // The last with indegree - outdegree = 1
        // if no eulerian path exists, an empty array is returned
        int first = -1;
        int last = -1;
        for (int u = 0; u < n; u++) {
            if (abs(outdegree[u] - indegree[u]) >= 2) return {};
            if (outdegree[u] - indegree[u] == 1) {
                if (first != -1) return {};
                first = u;
            }
            if (indegree[u] - outdegree[u] == 1) {
                if (last != -1) return {};
                last = u;
            }
        }
        if (last == -1 || first == -1) return {};
        if (start != -1 && start != first) return {};
        return hierholzer(n, first);
    }
} G;

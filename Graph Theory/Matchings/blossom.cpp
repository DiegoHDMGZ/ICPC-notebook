#include <bits/stdc++.h>
using namespace std;

// General maximum matching for unweighted graphs
const int MX = 1e5;
struct Graph {
    vector<int> adj[MX];
    int p[MX];
    int match[MX];
    // match[u] is the node match with u
    // or -1 if it does not belong to the matching

    int base[MX]; // base of the flower
    bool used[MX];
    bool blossom[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int lca(int u, int v, int n) { // O(n)
        vector<bool> marked(n);
        while (true) {
            u = base[u]; // blossom compression
            marked[u] = true;
            if (match[u] == -1) {
                // we reach the root : unexposed vertex
                break;
            }
            u = p[match[u]];
        }
        while (true) {
            v = base[v];
            if (marked[v]) return v;
            v = p[match[v]];
        }
        return -1;
    }

    void markPath(int u, int b, int children) {
        while (base[u] != b) {
            blossom[base[u]] = blossom[base[match[u]]] = true;
            p[u] = children;
            children = match[u];
            u = p[match[u]];
        }
    }

    void compress(int u, int v, int n, queue<int> &q) {
        int curBase = lca(u, v, n); // base of the flower
        assert(curBase != -1);
        fill(blossom, blossom + n, false);

        markPath(u, curBase, v);
        markPath(v, curBase, u);
        for (int i = 0; i < n; i++) {
            if (blossom[base[i]]) {
                base[i] = curBase;
                if (!used[i]) {
                    used[i] = true;
                    q.push(i);
                }
            }
        }
    }

    int findPath(int root, int n) {
        for (int i = 0; i < n; i++) {
            base[i] = i;
            used[i] = false;
            p[i] = -1;
        }
        used[root] = true;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int to : adj[u]) {
                if (base[u] == base[to] || match[u] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                    // we find a blossom
                    compress(u, to, n, q);
                } else if (p[to] == -1) {
                    // augmenting path or continue bfs
                    p[to] = u;
                    if (match[to] == -1) {
                        // we find an augmenting path
                        return to;
                    }
                    // we continue the bfs
                    to = match[to];
                    used[to] = true;
                    q.push(to);
                }
            }
        }
        return -1;
    }

    int maxMatching(int n) { // O(n^3)
        fill(match, match + n, -1);
        int ans = 0;
        for (int u = 0; u < n; u++) {
            if (match[u] == -1) {
                int v = findPath(u, n);
                if (v != -1) {
                    ans++;
                    while (v != -1) {
                        int nextVertex = match[p[v]];
                        match[v] = p[v];
                        match[p[v]] = v;
                        v = nextVertex;
                    }
                }
            }
        }
        return ans;
    }
} G;

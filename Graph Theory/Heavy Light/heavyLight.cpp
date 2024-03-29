#include <bits/stdc++.h>
using namespace std;
using Long = long long;

// https://cp-algorithms.com/graph/hld.html

// Querys and updates on tree paths
// With weight on edges, put the weight in the node with greater depth and add one line to
// query function

const int MX = 2e5;

Long combine(Long a, Long b) {
    return max(a, b);
}

const Long NEUTRAL = 0;
struct SegmentTree {
    void build(vector<Long> &v);
    Long query(int l, int r);
    void update(int pos, Long val); // range updates are also possible
} st;

struct Graph {
    vector<int> adj[MX];
    int parent[MX];
    int depth[MX];
    int heavy[MX];
    int head[MX];
    int pos[MX];
    int curPos = 0;

    void clear(int n) { // O(n)
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            parent[i] = -1;
            heavy[i] = -1;
            depth[i] = head[i] = pos[i] = 0;
        }
        curPos = 0;
    }

    void addEdge(int u, int v) { // O(1)
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int u = 0) { // O(V + E)
        int sz = 1;
        int maxSize = 0;
        heavy[u] = -1;
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                int szV = dfs(v);
                sz += szV;
                if (szV > maxSize) {
                    maxSize = szV;
                    heavy[u] = v;
                }
            }
        }
        return sz;
    }

    void decompose(int u, int h) { // O(V + E)
        head[u] = h;
        pos[u] = curPos++;
        if (heavy[u] != -1) {
            decompose(heavy[u], h);
        }
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u]) {
                decompose(v, v);
            }
        }
    }

    void build(vector<Long> &v, int root = 0) {
        curPos = 0;
        depth[root] = 0;
        parent[root] = -1;
        dfs(root);
        decompose(root, root);
        vector<Long> vals(v.size());
        for (int i = 0; i < v.size(); i++) {
            vals[pos[i]] = v[i];
        }
        st.build(vals);
    }

    Long query(int u, int v) { // O(O(|query|) log V)
        Long ans = NEUTRAL;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                swap(u, v);
            }
            Long curHeavyVal = st.query(pos[head[v]], pos[v]);
            ans = combine(ans, curHeavyVal);
            v = parent[head[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        // u = heavy[u]; //when weight are on edges

        // last heavy path
        Long lastVal = st.query(pos[u], pos[v]);
        ans = combine(ans, lastVal);
        return ans;
    }

    void update(int u, Long val) {
        st.update(pos[u], val);
    }
} G;

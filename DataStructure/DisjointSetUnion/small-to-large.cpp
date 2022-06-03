#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const int MX = 1e5;
struct DSU {
    int p[MX];
    vector<int> elements[MX];

    void build(int n) { // O(n)
        for (int i = 0; i < n; i++) {
            make_set(i);
        }
    }

    void make_set(int u) { // O(1)
        p[u] = u;
        elements[u] = {u};
    }

    int find(int u) { // O(1)
        return p[u];
    }

    void join(int u, int v) { // O(log n) amortized
        u = find(u);
        v = find(v);
        if (u != v) {
            if (elements[u].size() > elements[v].size()) {
                swap(u, v);
            }
            while (!elements[u].empty()) {
                int x = elements[u].back();
                elements[v].push_back(x);
                p[x] = v;
                elements[u].pop_back();
            }
        }
    }
} dsu;

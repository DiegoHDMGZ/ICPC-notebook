#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const Long MX = 1e5;

struct DSU {
    Long parent[MX];
    Long size[MX];
    vector<Long> history;
    vector<Long> savedCheckpoints;
    Long components;

    void make_set(Long u) { // O(1)
        parent[u] = u;
        size[u] = 1;
    }

    void build(int n) { // O(n)
        for (int i = 0; i < n; i++) {
            make_set(i);
        }
        components = n;
    }

    Long find(Long u) { // O(log n)
        if (u == parent[u]) {
            return u;
        }
        return find(parent[u]);
    }

    void join(Long u, Long v) { // O(1)
        u = find(u);
        v = find(v);
        if (u != v) {
            if (size[u] > size[v]) {
                swap(u, v);
            }
            history.push_back(u);
            components--;
            parent[u] = v;
            size[v] += size[u];
        } else {
            history.push_back(u);
        }
    }

    void rollback() { // O(1)
        // undo one join
        if (history.empty()) {
            return;
        }
        Long u = history.back();
        Long v = parent[u];
        history.pop_back();
        if (u == v) return;
        components++;
        size[v] -= size[u];
        parent[u] = u;
    }

    void save() { // O(1)
        savedCheckpoints.push_back(history.size());
    }

    void load() { // O(1) amortized
        // load to the last saved checkpoint
        assert(!savedCheckpoints.empty());
        while (history.size() > savedCheckpoints.back()) {
            rollback();
        }
        savedCheckpoints.pop_back();
    }

    void reset() { // O(1) amortized
        while (!history.empty()) rollback();
    }

    Long getComponents() { // O(1)
        return components;
    }
} dsu;

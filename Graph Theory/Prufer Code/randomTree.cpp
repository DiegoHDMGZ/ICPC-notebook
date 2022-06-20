#include <bits/stdc++.h>
using namespace std;
using Long = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
    return uniform_int_distribution<Long>(a, b)(rng);
}

struct Edge {
    Long u, v;
    Edge() {}
    Edge(Long u, Long v) : u(u), v(v) {}
};

vector<Edge> getTree() {
    vector<Long> code;
    Long n = random(2, 20);

    for (Long i = 0; i < n - 2; i++) {
        code.push_back(random(0, n - 1));
    }
    vector<Long> degree(n, 1);
    for (Long u : code) {
        degree[u]++;
    }
    Long ptr = 0;
    while (degree[ptr] != 1) {
        ptr++;
    }
    Long leaf = ptr;

    vector<Edge> tree;
    for (Long u : code) {
        tree.push_back(Edge(leaf, u));
        degree[u]--;
        if (degree[u] == 1 && u < ptr) leaf = u;
        else {
            ptr++;
            while (degree[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }
    tree.push_back(Edge(leaf, n - 1));
    return tree;
}
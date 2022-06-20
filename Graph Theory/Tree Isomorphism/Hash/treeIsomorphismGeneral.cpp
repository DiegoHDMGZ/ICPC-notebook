#include <bits/stdc++.h>
#define all(v) begin(v), end(v)
using namespace std;

using Long = long long;

const int MOD = 1e9 + 7;
const int MX = 1e5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}

vector<int> randomVector(int n, int maxVal) {
    vector<int> ans(n);
    for (int i = 0; i < n; i++) ans[i] = random(0, maxVal);
    return ans;
}
vector<int> randVal = randomVector(MX + 1, MOD);

struct Tree {
    vector<int> adj[MX];
    int height[MX];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int encodeRooted(int u, int p = -1) {
        height[u] = 0;
        vector<int> hashes;
        for (int v : adj[u]) {
            if (v == p) continue;
            hashes.push_back(encodeRooted(v, u));
            height[u] = max(height[u], height[v] + 1);
        }
        int x = randVal[height[u]];
        int ans = 1;
        for (int h : hashes) {
            h += x;
            if (h >= MOD) h -= MOD;
            ans = ((Long)ans * h) % MOD;
        }
        return ans;
    }

    int size[MX];
    void findCentroids(int u, int n, vector<int> &ans, int p = -1) {
        size[u] = 1;
        bool isCentroid = true;
        for (int v : adj[u]) {
            if (v == p) continue;
            findCentroids(v, n, ans, u);
            size[u] += size[v];
            if (size[v] > n / 2) isCentroid = false;
        }
        if (n - size[u] > n / 2) isCentroid = false;
        if (isCentroid) ans.push_back(u);
    }

    int encode(int n) { // O(n)
        vector<int> centroids;
        findCentroids(0, n, centroids);
        int ans = 1;
        for (int root : centroids) {
            int h = encodeRooted(root) + randVal[n];
            if (h >= MOD) h -= MOD;
            ans = ((Long)ans * h) % MOD;
        }
        return ans;
    }
} tree;

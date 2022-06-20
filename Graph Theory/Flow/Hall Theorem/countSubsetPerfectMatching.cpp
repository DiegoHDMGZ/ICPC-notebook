#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// Given a bipartite graph G = A U B
// Found how many subsets of A are covered by a matching
const int MX = 20;

int getBit(int mask, int pos) {
    return (mask >> pos) & 1;
}

int turnOff(int mask, int pos) {
    return mask & (~(1 << pos));
}

struct Graph {
    vector<int> adj[MX];

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int countOneSide(int current, int other, bool left) { // O(n * 2^n)
        vector<bool> dp(1 << current, true);
        int ans = 0;
        for (int mask = 0; mask < (1 << current); mask++) {
            vector<bool> nodes(other, false);
            for (int i = 0; i < current; i++) {
                if (getBit(mask, i) == 1) {
                    int u = i;
                    if (!left) u += other;
                    for (int v : adj[u]) {
                        if (left) v -= current;
                        nodes[v] = true;
                    }
                    dp[mask] = dp[mask] & dp[turnOff(mask, i)];
                }
            }
            int szNeigh = 0;
            for (int i = 0; i < other; i++) szNeigh += nodes[i];
            if (szNeigh < __builtin_popcount(mask)) dp[mask] = false;
            if (dp[mask]) ans++;
        }
        return ans;
    }

    int countPerfectMatching(int n, int m) {
        return countOneSide(n, m, true) + countOneSide(m, n, false);
    }
} G;

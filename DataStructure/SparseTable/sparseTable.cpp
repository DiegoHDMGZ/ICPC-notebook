#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 1e6;
const int LG = __lg(MX) + 1;

struct SparseTable {
    Long st[LG][MX];

    Long f(Long a, Long b) { return min(a, b); }

    void build(vector<Long> &A) { // O(|f| n log n)
        int n = A.size();
        for (int i = 0; i < n; i++) st[0][i] = A[i];
        for (int k = 1; k < LG; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = f(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    Long query(int l, int r) { // O(|f|)
        // special cases : idempotent(min, max, gcd)
        int lg = __lg(r - l + 1);
        return f(st[lg][l], st[lg][r - (1 << lg) + 1]);
    }
} st;

#include <bits/stdc++.h>
using namespace std;
using Long = long long;

struct BIT {
    vector<Long> tree;

    BIT() {}
    BIT(int n) {
        tree = vector<Long>(n + 1, 0);
    }

    Long query(int r) { // O(log n)
        // a[0] + a[1] + ... + a[r]
        r++;
        if (r <= 0) return 0;
        Long ans = 0;
        while (r > 0) {
            ans += tree[r];
            r -= (r & -r);
        }
        return ans;
    }

    Long query(int l, int r) { // O(log n)
        return query(r) - query(l - 1);
    }

    void update(int l, Long val) { // O(log n)
        // a[i] += val, i >= l
        l++;
        while (l < tree.size()) {
            tree[l] += val;
            l += (l & -l);
        }
    }

    void update(int l, int r, Long add) {
        update(l, add);
        update(r + 1, -add);
    }
};

struct RangeBIT {
    BIT ft1, ft2;

    RangeBIT(int n) {
        ft1 = BIT(n);
        ft2 = BIT(n);
    }

    Long query(int x) {
        Long m = ft1.query(x);
        Long b = ft2.query(x);
        return m * x + b;
    }

    Long query(int l, int r) {
        return query(r) - query(l - 1);
    }

    void update(int l, int r, Long v) {
        ft1.update(l, v);
        ft1.update(r + 1, -v);

        ft2.update(l, -v * (l - 1));
        ft2.update(r + 1, v * r);
    }
};

#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct SegmentTree {
    Long lazy[2 * MX];
    Long n;

    void clear(Long n) {
        for (Long i = 0; i < 2 * n; i++) {
            lazy[i] = 0;
        }
        this->n = n;
    }

    void push(Long id, Long tl, Long tr) { // O(1)
        Long tm = (tl + tr) / 2;
        Long left = id + 1;
        Long right = id + 2 * (tm - tl + 1);
        // Aggregate the lazy value
        lazy[left] += lazy[id];
        lazy[right] += lazy[id];

        // Restart the lazy value
        lazy[id] = 0;
    }

    void build(vector<Long> &a, Long id, Long tl, Long tr) { // O(n)
        if (tl == tr) {
            lazy[id] = a[tl];
        } else {
            Long tm = (tl + tr) / 2;
            Long left = id + 1;
            Long right = id + 2 * (tm - tl + 1);
            build(a, left, tl, tm);
            build(a, right, tm + 1, tr);
            lazy[id] = 0;
        }
    }

    void build(vector<Long> &a) {
        n = a.size();
        build(a, 1, 0, n - 1);
    }

    Long query(Long pos, Long id, Long tl, Long tr) { // O(logn)
        if (tl == tr) return lazy[id];
        Long tm = (tl + tr) / 2;
        Long left = id + 1;
        Long right = id + 2 * (tm - tl + 1);
        push(id, tl, tr);
        if (pos <= tm) return query(pos, left, tl, tm);
        else return query(pos, right, tm + 1, tr);
    }

    Long query(Long pos) {
        assert(n > 0);
        return query(pos, 1, 0, n - 1);
    }

    void update(Long l, Long r, Long val, Long id, Long tl, Long tr) { // O(logn)
        if (tr < l || tl > r) return;
        if (l <= tl && tr <= r) {
            // Aggregate update
            lazy[id] += val;
        } else {
            Long tm = (tl + tr) / 2;
            Long left = id + 1;
            Long right = id + 2 * (tm - tl + 1);
            push(id, tl, tr);
            update(l, r, val, left, tl, tm);
            update(l, r, val, right, tm + 1, tr);
        }
    }

    void update(Long l, Long r, Long val) {
        assert(n > 0);
        update(l, r, val, 1, 0, n - 1);
    }
} st;

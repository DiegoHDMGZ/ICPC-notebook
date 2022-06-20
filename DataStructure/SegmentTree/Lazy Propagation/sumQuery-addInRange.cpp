#include <bits/stdc++.h>
using namespace std;
using Long = long long;

const Long MX = 1e5;

Long combine(Long x, Long y) {
    return x + y;
}

struct SegmentTree {
    Long t[2 * MX];
    Long lazy[2 * MX];
    Long n;

    void clear(Long n) {
        for (Long i = 0; i < 2 * n; i++) {
            t[i] = 0;
            lazy[i] = 0;
        }
        this->n = n;
    }

    void build(vector<Long> &a, Long id, Long tl, Long tr) { // O(n)
        lazy[id] = 0;
        if (tl == tr) {
            t[id] = a[tl];
        } else {
            Long tm = (tl + tr) / 2;
            Long left = id + 1;
            Long right = id + 2 * (tm - tl + 1);
            build(a, left, tl, tm);
            build(a, right, tm + 1, tr);
            t[id] = combine(t[left], t[right]);
        }
    }

    void build(vector<Long> &a) {
        n = a.size();
        build(a, 1, 0, n - 1);
    }

    void push(Long id, Long tl, Long tr) { // O(1)
        Long tm = (tl + tr) / 2;
        Long left = id + 1;
        Long right = id + 2 * (tm - tl + 1);
        Long szLeft = tm - tl + 1;
        Long szRight = tr - tm;
        // Apply the lazy value of the node to the children
        t[left] += lazy[id] * szLeft;
        t[right] += lazy[id] * szRight;

        // Aggregate the lazy value
        lazy[left] += lazy[id];
        lazy[right] += lazy[id];

        // Restart the lazy value
        lazy[id] = 0;
    }

    Long query(Long l, Long r, Long id, Long tl, Long tr) { // O(logn)
        if (l <= tl && tr <= r) return t[id];
        Long tm = (tl + tr) / 2;
        Long left = id + 1;
        Long right = id + 2 * (tm - tl + 1);
        push(id, tl, tr);
        if (r < tm + 1) return query(l, r, left, tl, tm);
        else if (tm < l) return query(l, r, right, tm + 1, tr);
        else return combine(query(l, r, left, tl, tm), query(l, r, right, tm + 1, tr));
    }

    Long query(Long l, Long r) {
        assert(n > 0);
        return query(l, r, 1, 0, n - 1);
    }

    void update(Long l, Long r, Long val, Long id, Long tl, Long tr) { // O(logn)
        if (tr < l || tl > r) return;
        if (l <= tl && tr <= r) {
            Long sz = tr - tl + 1;
            // Apply the lazy value
            t[id] += val * sz;
            // Aggregate the lazy value
            lazy[id] += val;
        } else {
            Long tm = (tl + tr) / 2;
            Long left = id + 1;
            Long right = id + 2 * (tm - tl + 1);
            push(id, tl, tr);
            update(l, r, val, left, tl, tm);
            update(l, r, val, right, tm + 1, tr);
            t[id] = combine(t[left], t[right]);
        }
    }

    void update(Long l, Long r, Long val) {
        assert(n > 0);
        update(l, r, val, 1, 0, n - 1);
    }
} st;
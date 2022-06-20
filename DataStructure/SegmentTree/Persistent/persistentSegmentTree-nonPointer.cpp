#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const int MX = 1e5;
const int MX2 = 21 * MX;
struct SegmentTree {
    int roots[MX + 1]; // O(n + Q log n)
    Long sum[MX2];
    int left[MX2];
    int right[MX2];
    int n;
    int lastVersion;
    int nodes;

    Long combine(Long x, Long y) {
        return x + y;
    }

    int build(vector<Long> &a, int tl, int tr) { // O(n)
        int node = nodes++;
        if (tl == tr) {
            sum[node] = a[tl];
            return node;
        } else {
            int tm = (tl + tr) / 2;
            left[node] = build(a, tl, tm);
            right[node] = build(a, tm + 1, tr);
            sum[node] = combine(sum[left[node]], sum[right[node]]);
            return node;
        }
    }

    void build(vector<Long> &a) {
        nodes = 1;
        n = a.size();
        roots[0] = build(a, 0, n - 1);
        lastVersion = 0;
    }

    Long query(int l, int r, int node, Long tl, Long tr) { // O(log n)
        if (l <= tl && tr <= r) return sum[node];
        int tm = (tl + tr) / 2;
        if (r < tm + 1) return query(l, r, left[node], tl, tm);
        else if (tm < l) return query(l, r, right[node], tm + 1, tr);
        else
            return combine(query(l, r, left[node], tl, tm),
                           query(l, r, right[node], tm + 1, tr));
    }

    Long query(int l, int r, int version = -1) {
        // query in the version (or the last version if it's -1)
        assert(n > 0);
        if (version == -1) {
            version = lastVersion;
        }
        return query(l, r, roots[version], 0, n - 1);
    }

    int update(int pos, Long val, int prevNode, int tl, int tr) { // O(log n)
        int node = nodes++;
        if (tl == tr) {
            sum[node] = val;
            return node;
        } else {
            int tm = (tl + tr) / 2;
            left[node] = left[prevNode];
            right[node] = right[prevNode];
            if (pos <= tm) {
                left[node] = update(pos, val, left[prevNode], tl, tm);
            } else {
                right[node] = update(pos, val, right[prevNode], tm + 1, tr);
            }
            sum[node] = combine(sum[left[node]], sum[right[node]]);
            return node;
        }
    }

    void update(int pos, Long val, int version = -1) {
        // update a past version and append the new version to the history
        //(or update the last version if it's -1)
        assert(n > 0);
        if (version == -1) {
            version = lastVersion;
        }
        lastVersion++;
        roots[lastVersion] = update(pos, val, roots[version], 0, n - 1);
    }
} st;
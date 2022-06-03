#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct Node {
    Long sum;
    Long lazy;
    Node *left;
    Node *right;
    Node(Long sum = 0, Node *left = nullptr, Node *right = nullptr)
        : sum(sum), left(left), right(right), lazy(0) {}

    pair<Node *, Node *> push(Long tl, Long tr) { // O(1)
        Long tm = (tl + tr) / 2;
        Long szLeft = tm - tl + 1;
        Long szRight = tr - tm;
        // Apply the lazy value of the node to the children
        Node *newLeft = new Node(*left);
        Node *newRight = new Node(*right);
        newLeft->sum += lazy * szLeft;
        newRight->sum += lazy * szRight;
        // Aggregate the lazy value
        newLeft->lazy += lazy;
        newRight->lazy += lazy;
        return {newLeft, newRight};
    }
};

struct SegmentTree {
    vector<Node *> roots; // O(n + Q log n)
    Long n;

    Long combine(Long x, Long y) { return x + y; }

    Node *combine(Node *left, Node *right) {
        return new Node(combine(left->sum, right->sum), left, right);
    }

    Node *build(vector<Long> &a, Long tl, Long tr) { // O(n)
        if (tl == tr) {
            return new Node(a[tl]);
        } else {
            Long tm = (tl + tr) / 2;
            return combine(build(a, tl, tm), build(a, tm + 1, tr));
        }
    }

    SegmentTree() {}

    SegmentTree(vector<Long> &a) {
        n = a.size();
        roots = {build(a, 0, n - 1)};
    }

    Long query(Long l, Long r, Node *node, Long tl, Long tr) { // O(log n)
        if (l <= tl && tr <= r) return node->sum;
        Long tm = (tl + tr) / 2;
        auto children = node->push(tl, tr);
        if (r < tm + 1)
            return query(l, r, children.first, tl, tm);
        else if (tm < l)
            return query(l, r, children.second, tm + 1, tr);
        else
            return combine(query(l, r, children.first, tl, tm),
                           query(l, r, children.second, tm + 1, tr));
    }

    Long query(Long l, Long r, Long version = -1) {
        // query in the version (or the last version if it's -1)
        assert(n > 0);
        if (version == -1) {
            version = (Long)roots.size() - 1;
        }
        return query(l, r, roots[version], 0, n - 1);
    }

    void update(Long l, Long r, Long val, Node *node, Long tl, Long tr) { // O(log n)
        if (tr < l || tl > r) return;
        if (l <= tl && tr <= r) {
            Long sz = tr - tl + 1;
            node->sum += val * sz;
            node->lazy += val;
        } else {
            Long tm = (tl + tr) / 2;
            auto children = node->push(tl, tr);
            update(l, r, val, children.first, tl, tm);
            update(l, r, val, children.second, tm + 1, tr);
            *node = *combine(children.first, children.second);
        }
    }

    void update(Long l, Long r, Long val, Long version = -1) {
        // update a past version and append the new version to the history
        //(or update the last version if it's -1)
        assert(n > 0);
        if (version == -1) {
            version = (Long)roots.size() - 1;
        }
        Node *newRoot = new Node(*roots[version]);
        update(l, r, val, newRoot, 0, n - 1);
        roots.push_back(newRoot);
    }
};
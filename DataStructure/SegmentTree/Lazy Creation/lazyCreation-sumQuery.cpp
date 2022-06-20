#include <bits/stdc++.h>
using namespace std;

using Long = long long;

struct Node {
    Long sum;
    Long lazy;
    Node *left;
    Node *right;

    Node() {
        sum = lazy = 0;
        left = right = nullptr;
    }

    void push(Long tl, Long tr) { // O(1)
        // Create children if they are NULL
        if (left == nullptr) {
            left = new Node();
            right = new Node();
        }
        Long tm = (tl + tr) / 2;
        Long szLeft = tm - tl + 1;
        Long szRight = tr - tm;
        // Apply the lazy value of the node to the children
        left->sum += lazy * szLeft;
        right->sum += lazy * szRight;

        // Aggregate the lazy value
        left->lazy += lazy;
        right->lazy += lazy;

        // Restart the lazy value
        lazy = 0;
    }
};

Long combine(Long x, Long y) {
    return x + y;
}

struct SegmentTree {
    Node *root;
    Long n;

    SegmentTree() {}

    SegmentTree(Long n) {
        root = new Node();
        this->n = n;
    }

    Long query(Long l, Long r, Node *node, Long tl, Long tr) { // O(logn)
        if (!node) return 0;
        if (l <= tl && tr <= r) return node->sum;
        Long tm = (tl + tr) / 2;
        node->push(tl, tr);
        if (r < tm + 1) return query(l, r, node->left, tl, tm);
        else if (tm < l) return query(l, r, node->right, tm + 1, tr);
        else {
            return combine(query(l, r, node->left, tl, tm),
                           query(l, r, node->right, tm + 1, tr));
        }
    }

    Long query(Long l, Long r) {
        assert(n > 0);
        return query(l, r, root, 0, n - 1);
    }

    void update(Long l, Long r, Long val, Node *node, Long tl, Long tr) { // O(logn)
        if (tr < l || tl > r) return;
        if (l <= tl && tr <= r) {
            Long sz = tr - tl + 1;
            node->sum += val * sz;
            node->lazy += val;
        } else {
            Long tm = (tl + tr) / 2;
            node->push(tl, tr);
            update(l, r, val, node->left, tl, tm);
            update(l, r, val, node->right, tm + 1, tr);
            node->sum = combine(node->left->sum, node->right->sum);
        }
    }

    void update(Long l, Long r, Long val) {
        assert(n > 0);
        update(l, r, val, root, 0, n - 1);
    }
};
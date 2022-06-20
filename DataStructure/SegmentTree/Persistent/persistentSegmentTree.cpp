#include <bits/stdc++.h>
using namespace std;

using Long = long long;

struct Node {
    Long sum;
    Node *left;
    Node *right;
    Node(Long sum = 0, Node *left = nullptr, Node *right = nullptr)
        : sum(sum), left(left), right(right) {}
};

struct SegmentTree {
    vector<Node *> roots; // O(n + Q log n)
    Long n;

    Long combine(Long x, Long y) {
        return x + y;
    }

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
        if (r < tm + 1) return query(l, r, node->left, tl, tm);
        else if (tm < l) return query(l, r, node->right, tm + 1, tr);
        else
            return combine(query(l, r, node->left, tl, tm),
                           query(l, r, node->right, tm + 1, tr));
    }

    Long query(Long l, Long r, Long version = -1) {
        // query in the version (or the last version if it's -1)
        assert(n > 0);
        if (version == -1) {
            version = (Long)roots.size() - 1;
        }
        return query(l, r, roots[version], 0, n - 1);
    }

    Node *update(Long pos, Long val, Node *node, Long tl, Long tr) { // O(log n)
        if (tl == tr) {
            return new Node(node->sum + val);
        } else {
            Long tm = (tl + tr) / 2;
            Node *left = node->left;
            Node *right = node->right;
            if (pos <= tm) {
                left = update(pos, val, node->left, tl, tm);
            } else {
                right = update(pos, val, node->right, tm + 1, tr);
            }
            return combine(left, right);
        }
    }

    void update(Long pos, Long val, Long version = -1) {
        // update a past version and append the new version to the history
        //(or update the last version if it's -1)
        assert(n > 0);
        if (version == -1) {
            version = (Long)roots.size() - 1;
        }
        roots.push_back(update(pos, val, roots[version], 0, n - 1));
    }
};
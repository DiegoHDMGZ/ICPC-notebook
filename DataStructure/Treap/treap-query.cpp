#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Given an associative function f
Operations:
- Insert(key, val): Insert a key with its value
- Erase(key): Erase all values with this key
- Query(l, r): Return the cumulative result of applying f to the values
  of all keys in range [l, r] in the same order
*/
typedef long long Key;
typedef int Prior;
const Prior POOL = 1e9; // preferable in the order of n^2

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Prior random(Prior a, Prior b) { return uniform_int_distribution<Prior>(a, b)(rng); }

Long f(Long a, Long b) { return a + b; }

struct Node {
    Prior prior;
    Key key;
    Long value, answer;
    Node *left, *right;
    Node(Key key, Prior prior, Long value)
        : key(key), prior(prior), value(value), left(nullptr), right(nullptr) {}

    void recalc() {
        if (!left) answer = value;
        else answer = f(left->answer, value);
        if (right) answer = f(answer, right->answer);
    }
};

void split(Node *t, Node *&l, Node *&r, Key key) { // O(log n)
    // Splits tree `t` into two subtrees `l`, `r` such that
    // all keys of `l` are <= `key` and all keys of `r` are > `key`
    if (!t) l = r = nullptr;
    else if (t->key <= key) split(t->right, t->right, r, key), l = t;
    else split(t->left, l, t->left, key), r = t;
    if (t) t->recalc();
}

void merge(Node *&t, Node *l, Node *r) { // O(log n)
    // Merge trees `l` and `r` into tree `t`, assuming that
    // all the keys on `l` are smaller than the keys on `r`
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge(l->right, l->right, r), t = l;
    else merge(r->left, l, r->left), t = r;
    if (t) t->recalc();
}

const int NEUTRAL = 0;
struct Treap {
    Node *tree;
    Treap() : tree(nullptr) {}

    void insert(Key key, Long value) { // O(log n)
        Node *T1, *T2;
        split(tree, T1, T2, key);
        merge(T1, T1, new Node(key, random(0, POOL), value));
        merge(tree, T1, T2);
    }

    void erase(Key key) { // O(log n)
        Node *T1, *T2, *T3;
        split(tree, T1, T2, key - 1);
        split(T2, T2, T3, key);
        merge(tree, T1, T3);
    }

    Long query(Long l, Long r) { // O(log n)
        Node *T1, *T2, *T3;
        split(tree, T1, T2, l - 1);
        split(T2, T2, T3, r);
        Long ans = T2 ? T2->answer : NEUTRAL;
        merge(tree, T1, T2);
        merge(tree, tree, T3);
        return ans;
    }
} treap;

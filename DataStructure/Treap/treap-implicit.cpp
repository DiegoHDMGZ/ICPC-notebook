#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Given an array A initially empty, and an associative function f
Operations:
- Insert(pos, val): Insert the value `val` in position `pos` (0-indexed)
- Erase(pos): Erase the element in position `pos` (0-indexed)
- Query(l, r): Return f(A_l, A_{l+1}, ..., A_r)
After every insertion or deletion, the positions are recalculated
(all position greater than `pos` are shifted to the right)
We are going to construct a treap with implicit keys to recalculate
the positions
*/

typedef int Prior;
const Prior POOL = 1e9; //preferable in the order of n^2

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Prior random(Prior a, Prior b) {
	return uniform_int_distribution<Prior>(a, b)(rng);
}

const Long NEUTRAL = 0;

Long f(Long a, Long b) {
	return a + b;
}

struct Node {
	Prior prior;
	int size; //size of subtree 
	Long value, answer; 
	Node* left;
	Node* right;
	Node(Prior prior, Long value): 
		prior(prior), value(value), answer(NEUTRAL), size(0),
		left(nullptr), right(nullptr) {}
};

Long getAnswer(Node* node) {
	return node ? node->answer : NEUTRAL;
}

Long getSize(Node* node) {
	return node ? node->size : 0;
}

void recalc(Node* node) {
	if (node) {
		node->answer = f(getAnswer(node->left), node->value);
		node->answer = f(node->answer, getAnswer(node->right));
		node->size = getSize(node->left) + getSize(node->right) + 1;
	}
}

void split(Node* t, Node* &l, Node* &r, int pos, int smaller = 0) { 
	//O(log n)
	//Splits tree `t` into two subtrees `l`, `r` such that 
	//all pos of `l` are <= `pos` and all pos of `r` are > `pos`
	//and `smaller` is the number of smaller elements 
	//in the ancestors' trees
	if (!t) l = r = nullptr; 
	else {
		int curPos = smaller + getSize(t->left);
		if (curPos <= pos) split(t->right, t->right, r, pos, curPos + 1), l = t;
		else split(t->left, l, t->left, pos, smaller), r = t;
		recalc(t);
	}
}

void merge(Node* &t, Node* l, Node* r) { //O(log n)
	//Merge trees `l` and `r` into tree `t`, assuming that
	//all the pos on `l` are smaller than the pos on `r`
	if (!l || !r) t = l ? l : r;
	else if (l->prior > r->prior) merge(l->right, l->right, r), t = l;
	else merge(r->left, l, r->left), t = r;
	recalc(t);
}

struct Treap{
	Node* tree;
	Treap(): tree(nullptr){}
	
	void insert(int pos, Long value) { //O(log n) 
		Node *T1, *T2;
		split(tree, T1, T2, pos - 1);
		merge(T1, T1, new Node(random(0, POOL), value));
		merge(tree, T1, T2);
	}
	
	void erase(int pos) { //O(log n)
		Node *T1, *T2, *T3;
		split(tree, T1, T2, pos - 1);
		split(T2, T2, T3, 0);
		merge(tree, T1, T3);
	}
	
	Long query(int l, int r) { //O(log n)
		Node *T1, *T2, *T3;
		split(tree, T1, T2, l - 1);
		split(T2, T2, T3, r - l);
		Long ans = getAnswer(T2);
		merge(tree, T1, T2);
		merge(tree, tree, T3);
		return ans;
	}
} treap;

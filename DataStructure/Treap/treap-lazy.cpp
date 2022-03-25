#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Given an array A initially empty, and an associative function f
Operations:
- Insert(pos, val): Insert the value `val` in position `pos` (0-indexed)
- Erase(pos): Erase the element in position `pos` (0-indexed)
- Query(l, r): Return f(A_l, A_{l+1}, ..., A_r)
- Update(l, r): Do some changes to each element of this range
- Reverse(l, r): Reverse the range

After every insertion or deletion, the positions are recalculated
The updates can't be too complex, as you need to easily recalculate
the answers after each update like in Segment Tree
Notice that with the split and merge methods is also easy to cut
an specific range and put it in other place.

For this template we're going to use range sum query, range addition
update and range reversals.
*/
typedef int Prior;
const Prior POOL = 1e9; //preferable in the order of n^2

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Prior random(Prior a, Prior b) {
	return uniform_int_distribution<Prior>(a, b)(rng);
}

Long f(Long a, Long b) {
	return a + b;
}

struct Node {
	Prior prior;
	int size; //size of subtree 
	Long value, answer; 
	Long lazy;
	bool rev;
	Node *left, *right;
	Node(Prior prior, Long value): 
		prior(prior), value(value), size(0), lazy(0), rev(false),
		left(nullptr), right(nullptr) {}
	
	void recalc() {
		if (!left) answer = value;
		else answer = f(left->answer, value);
		if (right) answer = f(answer, right->answer);
		size = 1 + (left ? left->size : 0) + (right ? right->size : 0);
	}
	
	void push() {
		//Apply the lazy value
		value += lazy;
		if (rev) swap(left, right);
		if (left) left->answer += lazy * left->size;
		if (right) right->answer += lazy * right->size;
		//Aggregate the lazy value
		if (left) left->lazy += lazy, left->rev ^= rev;
		if (right) right->lazy += lazy, right->rev ^= rev;
		//Restart the lazy value
		lazy = 0;
		rev = false;
	}
};

int getSize(Node* node) {
	return node ? node->size : 0;
}

void split(Node* t, Node* &l, Node* &r, int pos, int smaller = 0) { 
	//O(log n)
	//Splits tree `t` into two subtrees `l`, `r` such that 
	//all pos of `l` are <= `pos` and all pos of `r` are > `pos`
	//and `smaller` is the number of smaller elements 
	//in the ancestors' trees
	if (!t) l = r = nullptr; 
	else {
		t->push();
		int curPos = smaller + getSize(t->left);
		if (curPos <= pos) split(t->right, t->right, r, pos, curPos + 1), l = t;
		else split(t->left, l, t->left, pos, smaller), r = t;
		t->recalc();
	}
}

void merge(Node* &t, Node* l, Node* r) { //O(log n)
	//Merge trees `l` and `r` into tree `t`, assuming that
	//all the pos on `l` are smaller than the pos on `r`
	if (l) l->push();
	if (r) r->push();
	if (!l || !r) t = l ? l : r;
	else if (l->prior > r->prior) merge(l->right, l->right, r), t = l;
	else merge(r->left, l, r->left), t = r;
	if (t) t->recalc();
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
		if (r >= tree->size) return 0; //null range, return neutral
		Node *T1, *T2, *T3;
		split(tree, T1, T2, l - 1);
		split(T2, T2, T3, r - l);
		Long ans = T2->answer; 
		merge(tree, T1, T2);
		merge(tree, tree, T3);
		return ans;
	}
	
	void update(int l, int r, Long add) { //O(log n)
		if (r >= tree->size) return; //null range
		Node *T1, *T2, *T3;
		split(tree, T1, T2, l - 1);
		split(T2, T2, T3, r - l);
		T2->answer += T2->size * add;
		T2->lazy += add;
		merge(tree, T1, T2);
		merge(tree, tree, T3);
	}
	
	void reverse(int l, int r) { //O(log n)
		if (r >= tree->size) return; //null range
		Node *T1, *T2, *T3;
		split(tree, T1, T2, l - 1);
		split(T2, T2, T3, r - l);
		T2->rev ^= 1;
		merge(tree, T1, T2);
		merge(tree, tree, T3);
	}
} treap;

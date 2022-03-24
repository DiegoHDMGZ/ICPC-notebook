#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

/*
Every node T has two main values (key, priority) and two 
nullable children. Assume that all keys are different. 
Priorities also must be different with high probability using a
big enough pool of random numbers (preferable in the order of n^2)
If a node T has values (X, Y) then all the nodes
in the subtree of T have Y' <= Y, all nodes in the left subtree
have X' < X and finally all nodes in the right subtree have X' > X

The height of the tree will be O(log n) with high probability if 
the elements are distinct. If there are equal elements we can enforce
this rule by transforming each element into a pair <value, frequency>.
The implementation of our insert function already does this implicitly
because ties will be broken by the time of insertion
*/

typedef long long Key;
typedef int Prior;
const Prior POOL = 1e9; //preferable in the order of n^2

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Prior random(Prior a, Prior b) {
	return uniform_int_distribution<Prior>(a, b)(rng);
}

struct Node {
	Prior prior;
	Key key;
	Node* left;
	Node* right;
	Node(){}
	Node(Key key, Prior prior): 
		key(key), prior(prior), left(nullptr), right(nullptr) {}
};

void split(Node* t, Node* &l, Node* &r, Key key) { //O(log n)
	//Splits tree `t` into two subtrees `l`, `r` such that 
	//all keys of `l` are <= `key` and all keys of `r` are > `key`
	if (!t) l = r = nullptr;
	else if (t->key <= key) split(t->right, t->right, r, key), l = t;
	else split(t->left, l, t->left, key), r = t;
}

void merge(Node* &t, Node* l, Node* r) { //O(log n)
	//Merge trees `l` and `r` into tree `t`, assuming that
	//all the keys on `l` are smaller than the keys on `r`
	if (!l || !r) t = l ? l : r;
	else if (l->prior > r->prior) merge(l->right, l->right, r), t = l;
	else merge(r->left, l, r->left), t = r;
}

struct Treap {
	Node* tree;
	Treap(): tree(nullptr){}
	void insert(Node* &t, Node* node) { //O(log n) 
		if (!t) t = node;
		else if (node->prior > t->prior) {
			split(t, node->left, node->right, node->key);
			t = node;
		} else if (node->key < t->key) insert(t->left, node);
		else insert(t->right, node);
	}
	
	void insert(Key key) { //O(log n) 
		insert(tree, new Node(key, random(0, POOL)));
		//Another equivalent implementation with less code
		/*Node *T1, *T2;
		split(tree, T1, T2, X);
		merge(T1, T1, new Node(X, random(0, POOL)));
		merge(tree, T1, T2);*/
	}
	
	void erase(Node* &t, Key key) { //O(log n)
		if (!t) return;
		if (t->key == key) merge(t, t->left, t->right);
		else if (key < t->key) erase(t->left, key);
		else erase(t->right, key);
	}
	
	void erase(Key key) { //O(log n)
		//Erase only one element with given key
		erase(tree, key);
		//Erase all elements with given key
		/*Node *T1, *T2, *T3;
		split(tree, T1, T2, key - 1);
		split(T2, T2, T3, key);
		merge(tree, T1, T3);*/
	}
	
	bool search(Node* t, Key key) { //O(log n)
		if (!t) return false;
		if (t->key == key) return true;
		else if (key < t->key) return search(t->left, key);
		else return search(t->right, key);
	}
	
	bool search(Key key) { //O(log n)
		return search(tree, key);
	}
	
	Node* unite(Node* l, Node* r) { //O(m log (n / m))
		if (!l || !r) return l ? l : r;
		if (l->prior < r->prior) swap(l , r);
		Node* lt;
		Node* rt;
		split(r, lt, rt, l->key);
		l->left = unite(l->left, lt);
		l->right = unite(l->right, rt);
		return l;
	}

	void unite(Treap t2) { //O(m log (n / m))
		tree = unite(tree, t2.tree);
	}
} treap;

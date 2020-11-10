#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

struct Node{
	Long sum;
	Node *left;
	Node *right;
	Node(Long sum = 0 , Node *left = nullptr, Node *right = nullptr) :
		sum(sum), left(left), right(right){}
};

struct SegmentTree {
	vector<Node*> roots; //O(n + Q log n)
	Long maxN;
	
	Long combine(Long x, Long y){
		return x + y;
	}
	
	Node* combine(Node *left, Node *right) {
		return new Node(combine(left->sum, right->sum) , left, right);
	}
	
	Node* build(vector<Long> &a, Long tl, Long tr) { //O(n)
		if (tl == tr){
			return new Node(a[tl]);
		} else{
			Long tm = (tl + tr) / 2;
			return combine(build(a, tl, tm), build(a, tm + 1, tr)); 
		}
	}
	
	SegmentTree(){}
	
	SegmentTree(vector<Long> &a) {
		maxN = a.size();
		roots = {build(a, 0, maxN - 1)};
	}

	Long query(Long l, Long r, Node *node, Long tl, Long tr) { //O(log n)
		if(!node) return 0;
		if (l <= tl && tr <= r) {
			return node->sum;
		}
		Long tm = (tl + tr) / 2;
		if(r < tm + 1){
			return query(l , r, node->left  , tl , tm);
		} else if(tm < l){
			return query( l , r , node->right , tm + 1 , tr);  
		} else{
			return combine(query(l, r, node->left, tl, tm) , query(l, r, node->right, tm + 1, tr));
		}
	}
	
	Long query(Long version, Long l , Long r) { 
		//query in the version
		assert(maxN > 0);
		return query(l , r  ,roots[version] ,  0 , maxN - 1);
	}

	Node* update(Long pos, Long val, Node *node, Long tl, Long tr) { //O(log n)
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
			return combine(left , right);
		}
	}
	
	void update(Long version, Long pos, Long val) {
		//update a past version and append the new version to the history
		assert(maxN > 0);
		roots.push_back(update(pos , val , roots[version] , 0 , maxN - 1));
	}
};

int main() {
	return 0;
}

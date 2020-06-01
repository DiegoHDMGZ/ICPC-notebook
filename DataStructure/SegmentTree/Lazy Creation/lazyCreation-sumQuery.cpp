#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct Node{
	Long sum;
	Long lazy;
	Node *left;
	Node *right;
	
	Node(){
		sum = lazy = 0;
		left = right = NULL;
	}
};

Long combine(Long x, Long y){
	return x + y;
}

struct SegmentTree {
	Node *root;
	Long maxN;
	
	SegmentTree(){}
	
	SegmentTree(Long n){
		root = new Node();
		maxN = n;
	}
	
	void push(Node *node, Long tl, Long tr) { //O(1)
		//Create childre if they are NULL
		if(!node->left){
			node->left = new Node();
			node->right = new Node();
		}
		Long tm = (tl + tr) / 2;
		Long szLeft = tm - tl + 1;
		Long szRight = tr - tm;
		//Apply the lazy value of the node to the children
		node->left->sum += node->lazy * szLeft;
		node->right->sum += node->lazy * szRight;
		
		//aggregate the lazy value of the node to the lazy value of the children
		node->left->lazy  += node->lazy;
		node->right->lazy += node->lazy;
		
		//restart lazy node of the node
		node->lazy = 0;
	}

	Long query(Long l, Long r, Node *node ,  Long tl, Long tr ) { //O(logn)
		if(!node) return 0;
		
		if (l <= tl && tr <= r) {
			return node->sum;
		}
		Long tm = (tl + tr) / 2;
		push(node , tl , tr);
		if(r < tm + 1){
			return query(l , r, node->left  , tl , tm);
		}else if(tm < l){
			return query( l , r , node->right , tm + 1 , tr);  
		} else{
			return combine(query(l, r, node->left, tl, tm) , query(l, r, node->right, tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r  ,root ,  0 , maxN - 1);
	}

	void update(Long l, Long r, Long val, Node *node , Long tl , Long tr) { //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			Long sz = tr - tl + 1;
			node->sum += val * sz;
			node->lazy += val;
		}else{
			Long tm = (tl + tr) / 2;
			push(node, tl , tr);
			update(l, r, val , node->left, tl, tm);
			update(l, r, val , node->right, tm + 1, tr);
			node->sum = combine(node->left->sum, node->right->sum);
		}
	}
	
	void update(Long l , Long r, Long val) {
		assert(maxN > 0);
		update(l, r , val , root , 0 , maxN - 1);
	}
};

int main() {
	return 0;
}

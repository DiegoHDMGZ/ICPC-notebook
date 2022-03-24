#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Given an array initially empty, and an associative function f
Operations:
Insert(pos, val): Insert the value `val` in position `pos`
Erase(pos): Erase the element in position `pos`
Query(l, r): Return f(a_l, a_{l+1}, ..., a_r)
Update(l, r): Do some changes in this range
Reverse(l, r): Reverse the range
After every insertion or deletion, the positions are recalculated

The updates can't be too complex, as you need to easily recalculate
the answers after each update like in Segment Tree
*/
const int MAXINT = 1e9;
const Long INF = 1e18;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

struct Item{
	Long value,prior , cnt;
	bool rev;
	Item *l, *r;
	Item(){
	}
	
	Item(Long value, Long prior) : value(value) , prior(prior), l (NULL), r(NULL) , cnt(0), rev(false){}
};

typedef Item * pitem;

Long getCnt(pitem it) {
	return it ? it -> cnt : 0;
}

void updateNode(pitem it) {
	if(it) {
		it -> cnt = getCnt(it -> l) + getCnt(it -> r) + 1;
	}
}

void push(pitem it){
	if(it && it->rev){
		swap(it->l , it->r);
		if(it->l){
			it->l->rev ^= true;
		}
		if(it->r){
			it->r->rev ^= true;
		}
		it->rev = false;
	}
}


void merge (pitem &t, pitem l , pitem r){ //O(log N)
	push(l);
	push(r);
	if(!l || !r){
		if(l){
			t=l;
		}
		else{
			t = r;
		}
	}
	else if(l -> prior > r->prior){
		merge(l -> r, l -> r, r);
		t = l;
	}
	else{
		merge(r -> l, l , r->l);
		t = r;
	}
	updateNode(t);
}

void split(pitem t,  pitem &l, pitem &r, Long key, Long add = 0){ //O(log N)
	if(!t){
		l = r = NULL;
		return;
	}
	push(t);
	Long curKey = add + getCnt(t -> l); //implicit key
	
	if(key <= curKey){
		split(t -> l, l , t -> l , key , add);
		r = t;
	}
	else{
		split(t -> r, t -> r , r ,key , add + 1 + getCnt(t -> l));
		l = t;
	}
	
	updateNode(t);
}

struct Treap{
	pitem tree;
	
	void insert(Long pos, Long X){ //O(log N) 
		Long r = random(0 , MAXINT);
		pitem it = new Item(X,r);
		pitem T1, T2;
		split(tree , T1, T2, pos);
		merge(T1, T1 , it);
		merge(tree, T1, T2);
	}
	
	void erase(pitem &t, Long key, Long add = 0){ //O(log N)
		if(!t){
			return;
		}
		
		push(t);
		Long curKey = add + getCnt(t -> l);
		if(curKey == key){
			merge(t, t -> l , t -> r);
		}
		else{
			if(key < curKey ){
				erase(t -> l, key, add);
			}
			else{
				erase(t -> r, key , add + 1 + getCnt(t -> l) );
			}
		}
		updateNode(t);
	}
	
	void erase(Long key){ //O(log N)
		erase(tree,key);
	}
	
	Long search(pitem t, Long key, Long add = 0){ //O(log N)
		if(!t){
			return -INF;
		}
		
		push(t);
		Long curKey = add + getCnt(t -> l);
		if(curKey == key){
			return t->value;
		}
		else{
			if(key < curKey){
				return search(t->l, key , add);
			}
			else{
				return search(t->r ,key, add + 1 + getCnt(t -> l) );
			}
		}
	}
	
	Long search(Long key){ //O(log N)
		return search(tree,key);
	}
	
	void replace(pitem t, Long key, Long val , Long add = 0){ //O(log N)
		if(!t){
			return;
		}
		
		push(t);
		Long curKey = add + getCnt(t -> l);
		if(curKey == key){
			t -> value = val;
		}
		else{
			if(key < curKey){
				replace(t->l, key , val , add);
			}
			else{
				replace(t->r ,key, val , add + 1 + getCnt(t -> l) );
			}
		}
	}
	
	void replace(Long key, Long val){ //O(log N)
		return replace(tree,key, val);
	}
	
	void reverse(Long l, Long r){
		if(l > r) return;
		pitem t1, t2 , t3;
		split(tree , t1 , t2, l);
		split(t2, t2 , t3, r - l  + 1);
		
		t2->rev ^= true;
		merge(tree, t1 , t2);
		merge(tree, tree, t3);
	}
	
	
}tp;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	return 0;
}


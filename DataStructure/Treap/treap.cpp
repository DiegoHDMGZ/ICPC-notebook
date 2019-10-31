#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const int MAXINT = 1e9;

struct Item{
	Long key,prior;
	Item *l, *r;
	Item(){}
	Item(Long key, Long prior) : key(key) , prior(prior), l (NULL), r(NULL){}
};

typedef Item * pitem;

void split(pitem t,  pitem &l, pitem &r, Long key){ //O(log N)
	if(!t){
		l = r = NULL;
	}
	else if(key < t->key){
		split(t->l, l , t->l ,key), r = t;
	}
	else{
		split(t->r, t->r , r ,key), l=t;
	}
}

void merge (pitem &t, pitem l , pitem r){ //O(log N)
	if(!l || !r){
		if(l) t=l;
		else t = r;
	}
	else if(l -> prior > r->prior){
		merge(l -> r, l -> r, r);
		t = l;
	}
	else{
		merge(r -> l, l , r->l);
		t = r;
	}
}

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

struct Treap{
	pitem tree;

	void insert(pitem &t, pitem it){ //O(log N) 
		if(!t){
			t = it;
		}
		else if(it->prior > t->prior){
			split(t, it->l , it->r ,it->key);
			t = it;
		}	
		else{
			if(it->key < t->key){
				insert( t->l , it);
			}
			else{
				insert(t->r , it);
			}
		}
	}
	
	void insert(Long X){ //O(log N) . !warning : complexity only works with different elements (it can be transform to a pair< value, frequency>)
		Long r = random(0 , MAXINT);
		pitem it = new Item(X , r);
		insert(tree,it);
	}
	
	void erase(pitem &t, Long key){ //O(log N)
		if(!t){
			return;
		}
		if(t-> key == key){
			merge(t,t->l,t->r);
		}
		else{
			if(key < t->key){
				erase(t->l,key);
			}
			else{
				erase(t->r,key);
			}
		}
	}
	
	void erase(Long key){ //O(log N)
		erase(tree,key);
	}
	
	bool search(pitem t, Long key){ //O(log N)
		if(!t){
			return false;
		}
		
		if(t->key == key){
			return true;
		}
		else{
			if(key < t->key){
				return search(t->l,key);
			}
			else{
				return search(t->r,key);
			}
		}
	}
	
	bool search(Long key){ //O(log N)
		return search(tree,key);
	}
	
	pitem unite( pitem l, pitem r) { //O( M log (N / M) )
		if(!l || !r) {
			return l ? l : r;
		}
		if(l -> prior < r -> prior) {
			swap(l , r);
		}
		pitem lt,rt;
		split(r , lt, rt , l -> key);
		l -> l = unite(l -> l, lt);
		l -> r = unite(l -> r, rt);
		return l;
	}

	void unite(Treap t2) { //O( M log (N / M) )
		tree = unite(tree , t2.tree);
	}
}tp;



int main() {
	return 0;
}

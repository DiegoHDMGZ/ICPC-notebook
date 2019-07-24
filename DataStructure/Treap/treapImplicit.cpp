#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define RANDOM mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define unif(a,b) uniform_int_distribution<int>(a,b)(rng)
using namespace std;

typedef long long Long;

const int MAXINT = 1e9;
RANDOM;
struct Item{
	Long value,prior , cnt;
	Item *l, *r;
	Item(){
	}
	
	Item(Long value, Long prior) : value(value) , prior(prior), l (NULL), r(NULL) , cnt(0){}
};

typedef Item * pitem;

Long cnt(pitem it) {
	return it ? it -> cnt : 0;
}

void upd_cnt(pitem it) {
	if(it) {
		it -> cnt = cnt(it -> l) + cnt(it -> r) + 1;
	}
}

void merge (pitem &t, pitem l , pitem r){ //O(log N)
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
	upd_cnt(t);
}

void split(pitem t,  pitem &l, pitem &r, Long key, Long add = 0){ //O(log N)
	if(!t){
		l = r = NULL;
		return;
	}
	
	Long curKey = add + cnt(t -> l); //indixex : implicit key
	
	if(key <= curKey){
		split(t -> l, l , t -> l , key , add);
		r = t;
	}
	else{
		split(t -> r, t -> r , r ,key , add + 1 + cnt(t -> l));
		l = t;
	}
	
	upd_cnt(t);
}

const Long INF = 1e18;

struct Treap{
	pitem tree;
	
	void insert(Long pos, Long X){ //O(log N) . !warning : only different elements
		Long random = unif(0,MAXINT);
		pitem it = new Item(X,random);
		pitem T1, T2;
		split(tree , T1, T2, pos);
		merge(T1, T1 , it);
		merge(tree, T1, T2);
	}
	
	void erase(pitem &t, Long key, Long add = 0){ //O(log N)
		if(!t){
			return;
		}
		
		Long curKey = add + cnt(t -> l);
		if(curKey == key){
			merge(t, t -> l , t -> r);
		}
		else{
			if(key < curKey ){
				erase(t -> l, key, add);
			}
			else{
				erase(t -> r, key , add + 1 + cnt(t -> l) );
			}
		}
		upd_cnt(t);
	}
	
	void erase(Long key){ //O(log N)
		erase(tree,key);
	}
	
	Long search(pitem t, Long key, Long add = 0){ //O(log N)
		if(!t){
			return -INF;
		}
		
		Long curKey = add + cnt(t -> l);
		if(curKey == key){
			return t->value;
		}
		else{
			if(key < curKey){
				return search(t->l, key , add);
			}
			else{
				return search(t->r ,key, add + 1 + cnt(t -> l) );
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
		
		Long curKey = add + cnt(t -> l);
		if(curKey == key){
			t -> value = val;
		}
		else{
			if(key < curKey){
				replace(t->l, key , val , add);
			}
			else{
				replace(t->r ,key, val , add + 1 + cnt(t -> l) );
			}
		}
	}
	
	void replace(Long key, Long val){ //O(log N)
		return replace(tree,key, val);
	}
	
}tp;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	return 0;
}


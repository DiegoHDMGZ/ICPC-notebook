#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const int MAXINT = 1e9;
const Long INF = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b){
	return uniform_int_distribution<int> (a , b) (rng);
}

struct Item{
	Long value,prior , cnt , add;
	Item *l, *r;
	Item(){}
	Item(Long value, Long prior) : value(value) , prior(prior),add(0), l (NULL), r(NULL) , cnt(0){}
};

typedef Item * pitem;

Long getCnt(pitem it) {
	return it ? it -> cnt : 0;
}

Long getVal(pitem it){
	return it ? it->value + it->add : 0;
}

void updateNode(pitem it) {
	if(it) {
		it -> cnt = getCnt(it -> l) + getCnt(it -> r) + 1;
		it->add =  getVal(it->l) + getVal(it->r);
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
	updateNode(t);
}

void split(pitem t,  pitem &l, pitem &r, Long key, Long add = 0){ //O(log N)
	if(!t){
		l = r = NULL;
		return;
	}
	
	Long curKey = add + getCnt(t -> l); // implicit key
	
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
	
	Long query(Long A, Long B){
		pitem T1,T2,T3;
		split(tree,T1,T2,A);
		split(T2,T2,T3,B - A +1);
		
		Long resp = getVal(T2);
	
		merge(tree,T1,T2);
		merge(tree,tree,T3);
		
		return resp;
	}
}tp;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

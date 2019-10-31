#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define RANDOM mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define unif(a,b) uniform_int_distribution<int>(a,b)(rng)

using namespace std;

typedef long long Long;

const int MAXINT = 1e9;

struct Item{
	Long key,prior,value,add;
	Item *l, *r;
	Item(){}
	Item(Long key, Long prior, Long value) : key(key) , prior(prior), value(value), add(0),l (NULL), r(NULL){}
	
	void debugItem(string s){
		cout << s << " = ( " << key  << " , " << value << " , "  << add << " ) " << endl;
	}
};

typedef Item * pitem;

Long val(pitem it){
	return it ? it->value + it->add : 0;
}

void updateVal(pitem it){
	if(it){
		it->add =  val(it->l) + val(it->r);
	}
}

void split(pitem t,  pitem &l, pitem &r, Long key){  //O(log N)
	if(!t){
		l = r = NULL;
	}
	else if(key <= t->key){
		split(t->l, l , t->l ,key), r = t;
	}
	else{
		split(t->r, t->r , r ,key), l=t;
	}
	updateVal(t);
}

void merge (pitem &t, pitem l , pitem r){  //O(log N)
	if(!l || !r){
		if(l) t=l;
		else t = r;
	}
	else if(l -> prior > r->prior){
		merge(l->r,l->r,r);
		t = l;
	}
	else{
		merge(r->l, l ,r->l);
		t = r;
	}
	updateVal(t);
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
		updateVal(t);
	}
	
	void insert(Long X, Long valor){ //O(log N) . !warning : complexity only works with different elements (it can be transform to a pair< value, frequency>)
		Long r = random(0 , MAXINT);
		pitem it = new Item(X, r, valor);
		insert(tree,it);
	}
	
	void erase(pitem &t, Long key){  //O(log N)
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
		updateVal(t);
	}
	
	void erase(Long key){  //O(log N)
		erase(tree,key);
	}
	
	Long query(Long A, Long B){  //O(log N)
		pitem T1,T2,T3;
		split(tree,T1,T2,A);
		split(T2,T2,T3,B+1);
		
		Long resp = val(T2);
	
		merge(tree,T1,T2);
		merge(tree,tree,T3);
		
		return resp;
	}
	
	void debugTree(pitem t){
		if(!t){
			return;
		}
		(*t).debugItem("t");
		if(t->l){
			(*(t->l) ).debugItem("l");
		}
		if(t->r){
			(*(t->r) ).debugItem("r");
		}
		cout << "**********************" << endl;
		debugTree(t->l);
		debugTree(t->r);
		
	}
	
	void debugTree(){
		debugTree(tree);
	}
}tp;



int main() {
/*
5
2 5
8 7
1 -5
6 15
100 12
*/
	
	Long n;
	cin >> n;
	REP(i,n){
		Long x, valor;
		cin >> x >> valor;
		tp.insert(x,valor);
	}
	
	while(true){
		Long l,r;
		cin >> l >> r;
		debug(tp.query(l,r) );
	}
	
	return 0;
}




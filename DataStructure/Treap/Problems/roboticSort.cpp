#include <bits/stdc++.h>
#define REP(i , n) for(Long i = 0; i < n; i++)
#define pb push_back
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

typedef long long Long;

const int MAXINT = 1e9;
const Long INF = 1e18;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b){
	return uniform_int_distribution<int> (a , b) (rng);
}
 
struct Item{
	Long value,prior , cnt , mini;
	bool rev;
	Item *l, *r;
	Item(){}
	Item(Long value, Long prior) : value(value) , prior(prior),mini(value), l (NULL), r(NULL) , cnt(0) , rev(false){}
	
	void debugItem(string s, Long pos){
		cout << s << " = (val = " << value << " , pos = " << pos  << ", mini = " << mini << endl;
	}
};

typedef Item * pitem;

Long cnt(pitem it) {
	return it ? it -> cnt : 0;
}

void updCnt(pitem it) {
	if(it) {
		it -> cnt = cnt(it -> l) + cnt(it -> r) + 1;
	}
}

Long val(pitem it){
	return it ? it->mini: INF;
}

void updateVal(pitem it){
	if(it){
		it->mini = min({val(it->l) , val(it->r) , it->value});
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
	updCnt(t);
	updateVal(t);
}

void split(pitem t,  pitem &l, pitem &r, Long key, Long add = 0){ //O(log N)
	if(!t){
		l = r = NULL;
		return;
	}
	push(t);
	Long curKey = add + cnt(t -> l); // implicit key
	
	if(key <= curKey){
		split(t -> l, l , t -> l , key , add);
		r = t;
	}
	else{
		split(t -> r, t -> r , r ,key , add + 1 + cnt(t -> l));
		l = t;
	}
	
	updCnt(t);
	updateVal(t);
}


struct Treap{
	pitem tree;
	
	void clear(){
		tree = NULL;
	}
	void insert(Long pos, Long x){
		Long r = random(0 , MAXINT);
		pitem it = new Item(x , r);
		pitem T1 , T2;
		split(tree, T1 , T2, pos);
		merge(T1 , T1, it);
		merge(tree, T1 , T2);
	}
	
	Long query(pitem t, Long add = 0){
		if(!t){
			return INF;
		}
		updCnt(t);
		updateVal(t);
		push(t);
		Long curKey = add + cnt(t -> l);
		
		if(t->mini == t->value){
			return curKey;
		}else{
			if(!t->r){
				return query(t->l, add);
			}
			if(!t->l){
				return query(t->r , add + 1 + cnt(t -> l)); 
			}
			if(t->l->mini < t->r->mini){
				return query(t->l, add);
			}
			else{
				return query(t->r , add + 1 + cnt(t -> l) );
			}
		}
	}

	
	Long query(Long A, Long B){
		pitem T1,T2,T3;
		split(tree,T1,T2,A);
		split(T2,T2,T3,B - A +1);
		
		Long resp = query(T2) + A;
	
		merge(tree,T1,T2);
		merge(tree,tree,T3);
		
		return resp;
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
	
	void debugTree(pitem t, Long add = 0){
		if(!t){
			return;
		}
		//push(t);
		Long curKey = add + cnt(t -> l); // implicit key
		(*t).debugItem("t", curKey);
		if(t->l){
			(*(t->l  ) ).debugItem("l", -1);
		}
		if(t->r){
			(*(t->r) ).debugItem("r" , -1);
		}
		cout << "**********************" << endl;
		debugTree(t->l , add);
		debugTree(t->r, add + 1 + cnt(t -> l));
		
	}
	
	void debugTree(){
		debugTree(tree);
	}
}treap;


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	while(cin >> n){
		if(n == 0) break;
		treap.clear();
		vector<pair<Long,Long>> v;
		REP(i , n){
			Long x;
			cin >> x;
			v.pb({x , i});
		}
		sort(v.begin(), v.end());
		
		Long ind = 0;
		REP(i , n){
			v[i].first = ind;
			swap(v[i].first, v[i].second);
			ind++;
			
		}
		sort(v.begin(), v.end()); 
		REP(i , n){
			treap.insert(i , v[i].second);	
		}

		REP(i , n){
			Long pos = treap.query(i , n - 1);
			cout << pos + 1;
			if(i < n - 1) cout << " ";
			else cout << "\n";
			treap.reverse(i , pos);
		}
	}
	
	
	return 0;	
}

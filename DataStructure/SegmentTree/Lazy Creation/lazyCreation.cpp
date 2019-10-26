#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

Long nTree = 1e9+5;
struct Data{
	Long sum,pref,suf,ans;
	Data(){
		sum = pref = suf = ans = 0;
	}
	Data(Long val){
		sum = pref = suf = ans = val;
	}
	
	void debugData(){
		cout << " ( " << sum << " , " << pref << " , " << suf << " , " << ans << " ) " << endl;
	}
};

Data combine(Data l, Data r){
	Data d;
	d.sum = l.sum + r.sum;
	d.pref = max(l.pref,l.sum+r.pref);
	d.suf = max(r.suf, r.sum + l.suf);
	d.ans = max(max(l.ans,r.ans), l.suf + r.pref);
	return d;
}

struct Node{
	Data datos;
	Node *l, *r;
	Data lazyLeft, lazyRight;
	
	Node(){
		l = NULL;
		r = NULL;
	}
	
	Node(Data D){
		datos = D;
		l = NULL;
		r = NULL;	
	}
	
	void updateLeft(Long val){
		datos = combine(Data(val) , datos);
		lazyLeft = combine( Data(val) , lazyLeft);
	}
	
	void updateRight(Long val){
		datos = combine(datos , Data(val));
		lazyRight = combine(lazyRight, Data(val));
	}
	
	void push(){
		if(!l){
			l = new Node();
		}
		if(!r){
			r = new Node();
		}
		
		l -> datos = combine( lazyLeft , l -> datos );
		r -> datos = combine( lazyLeft , r -> datos );
		l -> datos = combine( l -> datos , lazyRight );
		r -> datos = combine( r -> datos , lazyRight );
		
		l -> lazyLeft = combine( lazyLeft , l -> lazyLeft);
		r -> lazyLeft = combine( lazyLeft , r -> lazyLeft);
		l -> lazyRight = combine( l -> lazyRight , lazyRight);
		r -> lazyRight = combine( r -> lazyRight , lazyRight);
		
		lazyLeft = Data(0);
		lazyRight = Data(0);
	}
};

struct SegmentTree{
	Node *tree;
	
	SegmentTree(){
		tree = new Node();
	}
	
	void update(Node *root, Long l , Long r,  Long new_val, bool left, Long tl = 0, Long tr = nTree){
		if(l > r) return;
		
		if(l == tl && r == tr){
			if(left){
				root->updateLeft(new_val);
			}
			else{
				root->updateRight(new_val);
			}
		}
		else{
			root->push();
			Long tm = (tl+tr)/2;
			update(root->l, l , min(r, tm) , new_val, left, tl, tm);
			update(root->r, max(l , tm + 1) , r , new_val , left, tm + 1, tr );
		}
	}
	
	void updateLeft(Long l , Long r, Long new_val){
		update(tree, l , r , new_val,true);
	}
	
	void updateRight(Long l , Long r, Long new_val){
		update(tree, l , r , new_val , false);
	}
	
	Long query(Node *root , Long pos , Long  tl = 0, Long tr = nTree){
		if(tl == tr){
			return root->datos.ans;
		}
		
		Long tm = (tl+tr)/2;
	
		if(pos <= tm){
			if(!root->l){
				return root->datos.ans;
			}
			root->push();
			return query(root->l , pos, tl, tm);
		}
		else{
			if(!root->r){
				return root->datos.ans;
			}
			root->push();
			return query(root->r , pos , tm+1 , tr);
		}
	}
	
	Long query(Long pos){
		return query(tree,pos);
	}

}st;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long Q,K;
	cin >> Q >> K;
	
	Long ans = 0;
	
	REP(i,Q){
		Long t;
		cin >> t;
		Long c;
		cin >> c;
		c = ans ^ c;
		
		if(t != 3){
			Long d;
			cin >> d;
			
			Long limInf = max(1LL,c-K);
            Long limSup = min((Long)(1e9), c+K);
			if(t == 1){
				st.updateLeft(limInf, limSup, d);
			}else{
				st.updateRight(limInf, limSup, d);
			}
		}
		else{
			ans = st.query(c);
			cout << ans << endl;
		}
	}

	return 0;
}

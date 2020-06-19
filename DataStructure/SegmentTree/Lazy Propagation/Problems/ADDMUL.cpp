#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

const Long MOD = 1e9 + 7;

Long add(Long x , Long y){
	return (x + y) % MOD;
}

Long mult(Long x, Long y){
	return (x * y) % MOD;
}

struct SegmentTree {
	Long t[4 * MX];
	Long lazyMult[4 * MX];
	Long lazySum[4 * MX];
	Long lazyAssignment[4 * MX];
	Long maxN;
	
	void build(vector<Long> &a, Long id , Long tl , Long tr ) { //O(n)
		lazyMult[id] = 1;
		lazySum[id] = 0;
		lazyAssignment[id] = -1;
		if (tl == tr) {
			t[id] = a[tl];
		}else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = add(t[left], t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	void push(Long id, Long tl, Long tr) { //O(1)
		Long left = 2 * id;
		Long right = 2 * id + 1;
		Long tm = (tl + tr) / 2;
		Long szLeft = tm - tl + 1;
		Long szRight = tr - tm;
		//Apply the lazy value of the node to the children
		if(lazyAssignment[id] != -1){
			t[left] = mult(lazyAssignment[id] , szLeft);
			t[right] = mult(lazyAssignment[id] , szRight);
		}
		t[left] = mult(t[left] , lazyMult[id]);
		t[right] = mult(t[right] , lazyMult[id]);
		
		t[left] = add(t[left] , mult(lazySum[id] , szLeft));
		t[right] = add(t[right] , mult(lazySum[id] , szRight));
		
		
		//aggregate the lazy value of the node to the lazy value of the children
		if(lazyAssignment[id] != -1){
			lazyAssignment[left] = lazyAssignment[id] ;
			lazyAssignment[right] = lazyAssignment[id] ;
			lazyMult[left] = lazyMult[right] = 1;
			lazySum[left] = lazySum[right] = 0;
		}
		
		lazyMult[left] = mult(lazyMult[left] , lazyMult[id]);
		lazyMult[right] = mult(lazyMult[right], lazyMult[id]);
		lazySum[left] = mult(lazySum[left] , lazyMult[id]);
		lazySum[right] = mult(lazySum[right] , lazyMult[id]);
		
		lazySum[left] = add(lazySum[left] , lazySum[id]);
		lazySum[right] = add(lazySum[right] , lazySum[id]);
		
		//restart lazy node of the node
		lazyMult[id] = 1;
		lazySum[id] = 0;
		lazyAssignment[id] = -1;
	}

	Long query(Long l, Long r, Long id , Long tl, Long tr ) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		push(id, tl , tr);
		if(r < tm + 1){
			return query(l , r , left , tl , tm);
		}else if(tm < l){
			return query(l , r, right , tm + 1 , tr);  
		} else{
			return add(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Long val, Long type, Long id , Long tl , Long tr) { //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			if(type == 1){
				//add
				Long sz = tr - tl + 1;
				t[id] = add(t[id] , val * sz);
				lazySum[id] = add(lazySum[id], val);
			} else if(type == 2){
				//mult
				t[id] = mult(t[id] , val);
				lazyMult[id] = mult(lazyMult[id] , val);
				lazySum[id] = mult(lazySum[id] , val);
			}else{
				//assignment
				Long sz = tr - tl + 1;
				t[id] = mult(val , sz);
				lazyAssignment[id] = val;
				lazySum[id] = 0;
				lazyMult[id] = 1;
			}
		
		}else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id, tl , tr);
			update(l, r, val , type , left, tl, tm);
			update(l, r, val , type , right, tm + 1, tr);
			t[id] = add(t[left], t[right]);
		}
	}
	
	void update(Long l , Long r, Long val, Long type) {
		assert(maxN > 0);
		update(l, r , val , type, 1 , 0 , maxN - 1);
	}
} st;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, Q;
	cin >> n >> Q;

	vector<Long> A(n);
	REP(i , n){
		cin >> A[i];
	}

	st.build(A);
	REP(q , Q){
		Long type;
		cin >> type;
		Long l , r;
		cin >> l >> r;
		l--;
		r--;
		if(type == 4){
			cout << st.query(l , r ) << "\n";
		} else{
			Long val;
			cin >> val;
			st.update(l , r , val , type);
		}
	}
	return 0;
}

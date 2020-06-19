#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.spoj.com/problems/UPDATEIT/

const Long MX = 1e4;
struct SegmentTree {
	Long t[4 * MX];
	bool marked[4 * MX];
	
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i <  4 * n; i++) {
			t[i] = 0;
			marked[i] = false;
		}
		maxN = n;
	}
	
	void push(Long id){
		if(marked[id]){
			Long left = 2 * id;
			Long right = 2 * id + 1;
			t[left] += t[id];
			t[right] += t[id];
			t[id] = 0;
			marked[id] = false;
			marked[left] = marked[right] = true;
		}
	}
	
	void build(vector<Long> &a, Long id, Long tl, Long tr ) { //O(n)
		marked[id] = false;
		if (tl == tr) {
			t[id] = a[tl];
		}else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = 0;
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long pos, Long id, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			return t[id];
		}	
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1 ;
		push(id);
		if (pos <= tm) {
			return query(pos, left, tl, tm);
		}else {
			return query(pos, right, tm + 1, tr);
		}
	}
	
	Long query(Long pos ) {
		assert(maxN > 0);
		return query(pos , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Long add, Long id, Long tl , Long tr ) { //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			t[id] += add;
			marked[id] = true;
		}else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id);
			update(l, r, add , left, tl, tm);
			update(l, r, add , right, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Long add) {
		assert(maxN > 0);
		update(l , r, add, 1 , 0 , maxN - 1);
	}
	
	void print( Long id , Long tl , Long tr ){
		cout << "a[ " << tl << " ... " << tr << " ] = " << t[id] << endl;
		if (tl == tr) {
			return;
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1 ;
		print(left, tl, tm);
		print(right, tm + 1, tr);
	}
	
	void print(){
		print(1 , 0 , maxN - 1);
	}
} st;



void solve(){
	Long n , u;
	cin >> n >> u;
	st.clear(n);
	REP(i , u){
		Long l , r , val;
		cin >> l >> r >> val;
		st.update(l ,r , val);
	}
	Long q;
	cin >> q;
	REP(i , q){
		Long ind;
		cin >> ind;
		cout << st.query(ind) << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T ;
	REP(t , T) solve();
	return 0;
}

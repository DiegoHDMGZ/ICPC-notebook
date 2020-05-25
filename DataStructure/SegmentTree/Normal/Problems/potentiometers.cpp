#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3238

const Long MX = 2e5;

Long combine(Long x , Long y) {
	return x + y;
}


struct SegmentTree{
	Long t[2 * MX];
	
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i] = 0;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl , Long tr) { //O(n)
		if (tl == tr){
			t[id] = a[tl];
		} else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left] , t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}

	Long query(Long l, Long r, Long id , Long tl , Long tr ) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if(r < tm + 1){
			//only left child
			return query(l , r , left , tl , tm);
		}else if(tm < l){
			//only right child
			return query(l , r, right , tm + 1 , tr); 
		} else{
			//both children
			return combine(query(l, r, left, tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}
	
	void update(Long pos, Long val, Long id, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[id] = val;
		}else{
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val, right, tm + 1, tr);
			}
			t[id] = combine(t[left] , t[right] );
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val, 1 , 0 , maxN - 1);
	}
} st;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	Long cnt = 1;
	cin >> n;
	while(true){
		if(n == 0) break;
		cout << "Case " << cnt++ << ":\n";

		vector<Long> vec;
		for(Long i = 0; i < n; i++){
			Long x;
			cin >> x;
			vec.pb(x);
		}
		st.build(vec);
		string s;
		while(cin >> s){
			if(s[0] == 'E'){
				break;
			}
			if(s[0] == 'S'){
				Long pos;
				cin >> pos;
				pos--;
				Long v;
				cin >> v;
				st.update(pos , v );
			} else {
				Long l , r;
				cin >> l >> r;
				l--;
				r--;
				cout << st.query(l ,r) << "\n";
			}
		}
		cin >> n;
		if(n == 0) break;
		cout << "\n";
	}
	return 0;
}

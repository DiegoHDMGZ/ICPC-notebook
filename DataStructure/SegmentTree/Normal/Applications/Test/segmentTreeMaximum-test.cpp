#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
const Long INF = 1e18;

struct Data{
	Long maxi, cnt;
	Data(){}
	Data(Long maxi, Long cnt = 1) : maxi(maxi), cnt(cnt){}
};

Data combine(Data p1, Data p2) {
	if (p1.maxi > p2.maxi) {
		return p1;
	}
	if (p1.maxi < p2.maxi) {
		return p2;
	}
	return Data(p1.maxi, p1.cnt + p2.cnt);
}

struct SegmentTree {
	Data t[2 * MX]; 
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 2 * n; i++) {
			t[i] = Data(0, 0);
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id, Long tl , Long tr) { //O(n)
		assert(id < 2 * maxN);
		if (tl == tr) {
			t[id] = Data(a[tl]);
		}else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}


	Data query(Long l, Long r, Long id , Long tl , Long tr) { //O(logn)
		if (l <= tl && tr <= r) {
			return t[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = id + 1;
		Long right = id + 2 * (tm - tl + 1) ;
		if(r < tm + 1){
			//only left child
			return query(l , r , left , tl , tm);
		} else if(tm < l){
			//only right child
			return query(l , r, right , tm + 1 , tr); 
		} else {
			//both children
			return combine(query(l, r, left , tl, tm) , query(l, r, right, tm + 1, tr));
		}
	}
	
	Data query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long val, Long id, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[id] = Data(val);
		}
		else {
			Long tm = (tl + tr) / 2;
			Long left = id + 1;
			Long right = id + 2 * (tm - tl + 1) ;
			if (pos <= tm) {
				update(pos, val, left, tl, tm);
			}else {
				update(pos, val, right, tm + 1, tr);
			}
			t[id] = combine(t[left], t[right]);
		}
	}
	
	void update(Long pos, Long val) {
		assert(maxN > 0);
		update(pos , val , 1 , 0 , maxN - 1);
	}
} st;

struct Brute{
	vector<Long> v;
	void build(vector<Long> v){
		this->v = v;
	}
	
	Data query(Long l , Long r){
		Long ans = v[l];
		Long cnt = 1;
		for(Long i = l + 1 ; i <= r; i++){
			if(v[i] > ans){
				ans = v[i];
				cnt = 1;
			} else if(v[i] == ans){
				cnt++;
			}
		}
		return Data(ans , cnt);
	}
	
	void update(Long pos, Long val){
		v[pos] = val;
	}
}brute;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

void solve(){
	Long n = random(1 , 1000);
	vector<Long> v(n);
	for(Long i = 0; i < n; i++){
		v[i] = random(-100, 100);
	}
	/*debug(n);
	for(Long i = 0; i < n; i++){
		cout << v[i] << " ";
	}
	cout << endl;*/
	brute.build(v);
	st.build(v);
	Long q = 1e6 / n;
	for(Long i = 0; i < q; i++){
		Long pos , val;
		pos = random(0 , n - 1);
		val = random( -20 , 40);

		st.update(pos , val);
		brute.update(pos , val);
		Long l = random(0, n - 1);
		Long r = random(l , n - 1);
		Data br = brute.query(l , r);
		Data ac = st.query(l , r);

		assert(br.maxi == ac.maxi);
		assert(br.cnt == ac.cnt);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 10;
	REP(t , T ) solve();
	
	return 0;
}


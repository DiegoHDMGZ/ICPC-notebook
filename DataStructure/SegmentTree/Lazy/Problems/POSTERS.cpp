#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.spoj.com/problems/POSTERS/

const Long MX = 1e6;
struct SegmentTree{
	Long lazy[4 * MX];
	
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			lazy[i] = 0;
			marked[i] = false;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl, Long tr){ //O(n)
		marked[id] = false;
		if(tl == tr){
			lazy[id] = a[tl];
		}
		else{
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			lazy[id] = 0;
		}
	}
	
	void build(vector<Long> &a ) {
		maxN = a.size();
		build(a , 1 , 0 , maxN - 1);
	}
	
	bool marked[4 * MX];
	void push(Long id){ //O(1)
		if(marked[id]){
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			lazy[left] = lazy[right] = lazy[id];
			marked[left] = marked[right] = true;
			marked[id] = false;
		}
	}
	
	Long query(Long pos, Long id , Long tl , Long tr ){ //O(logn)
		if(tl == tr) return lazy[id];	
		if(marked[id]){
			return lazy[id];
		}
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1 ;
		push(id);
		if(pos <= tm){
			return query(pos, left , tl, tm);
		}
		else{
			return query(pos, right, tm + 1, tr);
		}
	}
	
	Long query(Long pos) {
		assert(maxN > 0);
		return query(pos , 1 , 0 , maxN - 1);
	}
	
	void update(Long l, Long r, Long val, Long id, Long tl, Long tr ){ //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			lazy[id] = val;
			marked[id] = true;
		}else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id);
			update(l, r, val , left, tl, tm);
			update(l, r, val , right, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Long val) {
		assert(maxN > 0);
		update(l , r , val, 1 , 0 , maxN - 1);
	}
} st;
void solve(){
	Long n;
	cin >> n;
	map<Long, Long> conv;
	set<Long> s;
	vector<pair<Long,Long>> ranges;
	for(Long i = 0; i < n; i++){
		Long l , r;
		cin >> l >> r;
		ranges.pb({l,r});
		s.insert(l);
		s.insert(r);
		s.insert(l - 1);
		s.insert(r + 1);
	}
	Long cnt = 0;
	for(Long x : s) conv[x] = cnt++;
	for(pair<Long,Long> &p : ranges){
		p.first = conv[p.first];
		p.second = conv[p.second];
	}
	st.clear(s.size());
	for(Long i = 0; i < ranges.size(); i++){
		st.update(ranges[i].first, ranges[i].second, i + 1);
	}
	set<Long> posters;
	for(Long i = 0; i < s.size(); i++){
		Long q = st.query(i);
		if(q != 0){
			posters.insert(q);
		}
		
	}
	cout << posters.size() << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t , T ) solve();

	return 0;
}

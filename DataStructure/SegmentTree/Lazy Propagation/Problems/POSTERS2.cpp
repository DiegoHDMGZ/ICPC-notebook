#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef int Long;

//http://lightoj.com/volume_showproblem.php?problem=1207

const Long MX = 7e5;
struct SegmentTree{
	Long t[4 * MX];
	bool marked[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i < 4 * n; i++) {
			t[i] = 0;
			marked[i] = false;
		}
		maxN = n;
	}
	
	void build(vector<Long> &a, Long id , Long tl, Long tr){ //O(n)
		marked[id] = false;
		if(tl == tr){
			t[id] = a[tl];
		}
		else{
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
	
	void push(Long id){ //O(1)
		if(marked[id]){
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			t[left] = t[right] = t[id];
			marked[left] = marked[right] = true;
			marked[id] = false;
		}
	}
	
	Long query(Long pos, Long id , Long tl , Long tr ){ //O(logn)
		if(tl == tr) return t[id];	
		if(marked[id]){
			return t[id];
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
			t[id] = val;
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

void solve(Long test){
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
		s.insert(l + 1);
		s.insert(r - 1);
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
	cout << "Case "<< test << ": " << posters.size() << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t , T ) solve(t + 1);

	return 0;
}

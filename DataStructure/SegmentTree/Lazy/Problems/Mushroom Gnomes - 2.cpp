#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef long double Double;

const Long MX = 5e5;

struct SegmentTree {
	Double lazy[4 * MX];
	Long maxN;
	
	void clear(Long n) {
		for(Long i = 0; i <  4 * n; i++) {
			lazy[i] = 0;
		}
		maxN = n;
	}
	
	void apply(Double &val, Double parent){
		val = val + parent - val * parent;
	}
	
	void push(Long id){
		Long left = 2 * id;
		Long right = 2 * id + 1;
		//aggregate the lazy value of the node to the lazy value of the children
		apply(lazy[left] , lazy[id]);
		apply(lazy[right] , lazy[id]);
		
		//restart lazy node of the node
		lazy[id] = 0;
	}
	

	Double query(Long pos, Long id, Long tl, Long tr) { //O(logn)
		if (tl == tr) {
			return lazy[id];
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
	
	Double query(Long pos ) {
		assert(maxN > 0);
		return query(pos , 1 , 0 , maxN - 1);
	}

	void update(Long l, Long r, Double prob, Long id, Long tl , Long tr ) { //O(logn)
		if(tr < l || tl > r){
			return;
		}
		if (l <= tl && tr <= r) {
			//aggregate update
			apply(lazy[id] , prob);
		}else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1 ;
			push(id);
			update(l, r, prob , left, tl, tm);
			update(l, r, prob , right, tm + 1, tr);
		}
	}
	
	void update(Long l , Long r, Double prob) {
		assert(maxN > 0);
		update(l , r, prob, 1 , 0 , maxN - 1);
	}
	
} st;

struct Update{
	Long l , r ;
	Double prob;
	Update(){}
	Update(Long l , Long r, Double prob) : l(l), r(r), prob(prob){}
};

struct Mushroom{
	Long pos, power;
	
	Mushroom(){}
	Mushroom(Long pos, Long power) : pos(pos), power(power){}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n , m;
	cin >> n >> m;
	vector<Update> up;
	set<Long> s;
	map<Long, Long> conv;
	REP(i , n){
		Long a , h , l , r;
		cin >> a >> h >> l >> r;
		s.insert(a - h);
		s.insert(a - 1);
		s.insert(a + 1);
		s.insert(a + h);
		up.push_back(Update(a - h , a - 1, l / 100.0));
		up.push_back(Update(a + 1 , a + h , r / 100.0));
	}
	vector<Mushroom> mush;
	REP(i, m){
		Long pos, power;
		cin >> pos >> power;
		mush.pb(Mushroom(pos, power));
		s.insert(pos);
	}
	Long cnt = 0;
	for(Long x : s){
		conv[x] = cnt++;
	}
	st.clear(cnt);
	REP(i , 2 * n){
		up[i].l = conv[up[i].l];
		up[i].r = conv[up[i].r];
		st.update(up[i].l , up[i].r , up[i].prob);
	/*	debug(up[i].l);
		debug(up[i].r);
		debug(up[i].prob);
		cout << endl;*/
	}
	Double ans = 0;
	REP(i , m){
		mush[i].pos = conv[mush[i].pos];
		//debug(mush[i].pos);
		Double prob = 1.0 - st.query(mush[i].pos);
		ans += prob * mush[i].power;
	}
	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}

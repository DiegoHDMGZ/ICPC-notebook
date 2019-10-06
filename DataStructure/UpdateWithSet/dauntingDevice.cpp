#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=6213
const Long MX = 1e5 + 2;

struct Segment {
	Long l ,  r,  c;
	Segment(){
	}
	Segment(Long l, Long r, Long c) : l(l) , r(r), c(c){
	}
};

struct SuperSet{
	set<pair<Long,Long>> endPoint; //(pos , indSegment)
	vector<Segment> v;
	Long cnt[MX];
	
	void clear(Long N, Long C) {
		endPoint.clear();
		v.clear();

		for(Long i = 0; i < C; i++) {
			cnt[i] = 0;
		}
		add(0 , N - 1 , 0);
	}

	Long query(Long c) { //O(1)
		return cnt[c];
	}

	void add(Long l, Long r, Long c) { //O(log n)
		Long ind = v.size();
		v.pb(Segment(l , r , c));
		endPoint.insert({l, ind});
		endPoint.insert({r , ind});
		cnt[c] += r - l + 1;
	}

	void erase(Long ind) { //O(log n)
		endPoint.erase({v[ind].l , ind});
		endPoint.erase({v[ind].r , ind});
		cnt[v[ind].c] -= (v[ind].r - v[ind].l + 1);
	}

	void update(Long l , Long r, Long c) { //O(log n)
		auto it = endPoint.lower_bound({l , -1});
		if(it == endPoint.end()) {
			add(l , r , c);
			return;
		}
		
		if(it != endPoint.begin()) {
			it--;
			Long ind = (*it).second;
			Long pos = (*it).first;
			
			if(pos != v[ind].r) {
				erase(ind);
				if(v[ind].r > r) {
					add(v[ind].l , l - 1 , v[ind].c);
					add(r + 1 , v[ind].r , v[ind].c);
					add(l , r , c);
					return;
				} else {
					add(v[ind].l , l - 1 , v[ind].c);
				}
			}
		}
		it = endPoint.lower_bound({l , -1});
		while(it != endPoint.end()) {
			Long ind = (*it).second;
			if(v[ind].r <= r) {
				erase(ind);
			} else {
				break;
			}
			it = endPoint.lower_bound({l , -1});
		}

		it = endPoint.lower_bound({l , -1});
		if(it == endPoint.end()) {
			add(l , r , c);
			return;
		}
		Long ind = (*it).second;
		if(v[ind].l > r) {
			add(l , r , c);
			return;
		}
		erase(ind);
		add(r + 1 , v[ind].r , v[ind].c);
		add(l , r , c);
	}
}ss;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	//update in range : set to [l,r] value c
	//query for frequency of c in all range
	Long N;
	while(cin >> N){
		Long C, Q;
		cin >> C >> Q;
		ss.clear(N, C);
		REP(i , Q) {
			Long P, X, A ,B;
			cin >> P >> X >> A >> B;
			P--;
			X--;
			Long S = ss.query(P);
		
			Long M1 = (A + S * S ) % N;
			Long M2 = (A + (S + B) * (S + B)) % N;
		
			ss.update(min(M1 , M2) , max(M1 , M2) , X);
		}
		Long ans = 0;
		REP(i , C) {
			Long q = ss.query(i);
			ans = max(ans , q);
		}
		cout << ans << '\n';
	}
	
	return 0;
}

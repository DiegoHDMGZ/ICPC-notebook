#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5 ;
const Long MAXVAL = 1e6 + 1;
const Long EXTRA = 6;
struct FenwickTree{
	Long tree[MX + EXTRA];
	
	void clean(Long n){ //O(nlogn)
		for(Long i = 0; i < n + EXTRA; i++){
			tree[i] = 0;
		}
	}
	
	Long query(Long i){ //O(log n)
		i += EXTRA;
		Long sum = 0;
		while(i > 0){
			sum += tree[i];
			i -= (i & -i);
		}
		return sum;
	}
	
	void update(Long i , Long delta){ //O(log MAX)
		i += EXTRA;
		while(i < MX + EXTRA){
			tree[i] += delta;
			i += (i & -i);
		}
	}
	
	void update(Long l , Long r, Long delta){
		update(l , delta);
		update(r + 1 , -delta);
	}		
} ft;

struct Query{
	Long l, r , pos, ans;
	Query(){}
	Query(Long l , Long r , Long pos) : l(l), r(r), pos(pos) {}
};

bool cmp(Query &Q1 , Query &Q2){
	return Q1.r < Q2.r;
}

void dquery(vector<Long> &v , vector<Query> &queries){
	Long Q = queries.size();
	Long n = v.size();
	vector<Long> lastSeen(MAXVAL , -1);
	sort(queries.begin(), queries.end() , cmp);
	Long i = 0;
	Long q = 0;
	
	while(i < n && q < Q){
		while(i <= queries[q].r){
			ft.update(lastSeen[v[i]] + 1 , i , 1);
			lastSeen[v[i]] = i;
			i++;
		}
		Long fijo = q;
		while(queries[q].r == queries[fijo].r){
			queries[q].ans = ft.query(queries[q].l);
			q++;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	cin >> n;
	vector<Long> v;
	REP(i , n){
		Long num;
		cin >> num;
		v.pb(num);
	}
	vector<Query> queries;
	Long q;
	cin >> q;
	REP(i , q){
		Long l , r;
		cin >> l >> r;
		l--, r--;
		queries.pb(Query(l ,r , i));
	}
	
	dquery(v , queries);
	
	vector<Long> ans(q);
	REP(i , q){
		ans[queries[i].pos] = queries[i].ans;
	}
	REP(i , q){
		cout << ans[i] << "\n";
	}
	
	return 0;
}

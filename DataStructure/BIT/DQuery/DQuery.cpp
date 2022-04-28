#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct BIT {
	vector<Long> tree;

	BIT(int n) {
		tree = vector<Long>(n + 1, 0);
	}
	
	Long query(int r) { //O(log n)
		//a[0] + a[1] + ... + a[r]
		r++;
		if (r <= 0) return 0;
		Long ans = 0;
		while (r > 0) {
			ans += tree[r];
			r -= (r & -r);
		}
		return ans;
	}
	
	Long query(int l, int r) { //O(log n)
		return query(r) - query(l - 1);
	}
	
	void update(int l, Long val) { //O(log n)
		//a[i] += val, i >= l
		l++;
		while (l < tree.size()) {
			tree[l] += val;
			l += (l & -l);
		}
	}
	
	void update(int l, int r, Long add) {
		update(l, add);
		update(r + 1, -add);
	}		
};

struct Query{
	int l, r , pos;
	Query(){}
	Query(int l, int r, int pos) : l(l), r(r), pos(pos) {}
};

bool cmp(Query &Q1 , Query &Q2) {
	return Q1.r < Q2.r;
}

const int MAXVAL = 1e6 + 1;
vector<Long> dquery(vector<Long> &v, vector<Query> &queries){
	int Q = queries.size();
	int n = v.size();
	BIT ft(n);
	vector<Long> lastSeen(MAXVAL , -1);
	sort(queries.begin(), queries.end() , cmp);
	int i = 0;
	int q = 0;
	vector<Long> ans(queries.size());
	while (i < n && q < Q) {
		while (i <= queries[q].r) {
			ft.update(lastSeen[v[i]] + 1, i, 1);
			lastSeen[v[i]] = i;
			i++;
		}
		int low = q;
		while (queries[q].r == queries[low].r) {
			ans[queries[q].pos] = ft.query(queries[q].l);
			q++;
		}
	}
	return ans;
}

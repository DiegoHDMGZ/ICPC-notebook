#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

/*
add(u, v) — add an edge u − v into the graph;
remove(u, v) — add an edge u − v into the graph;
query() — return number of components / is the graph bipartite / etc
or query(u, v) - return if u and v are in the same component / etc
*/

const int MX = 3e5;
struct DSU{
	Long parent[MX];
	Long size[MX];
	vector<Long> history;
	vector<Long> savedCheckpoints;
	Long components;
	
	void make_set(Long u) { //O(1)
		parent[u] = u;
		size[u] = 1;
	}
	
	void build(int n) { //O(n)
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
		components = n;
	}
	
	Long find(Long u) { //O(log n)
		if (u == parent[u]) {
			return u;
		}
		return find(parent[u]);
	}
	
	void join(Long u, Long v) { //O(1)
		u = find(u);
		v = find(v);
		if (u != v) {
			if (size[u] > size[v]) {
				swap(u, v);
			}
			history.push_back(u);
			components--;
			parent[u] = v;
			size[v] += size[u];
		} else {
			history.push_back(u);
		}
	}
	
	void rollback() { //O(1)
		//undo one join
		if (history.empty()) {
			return;
		}
		Long u = history.back();
		Long v = parent[u];
		history.pop_back();
		if (u == v) return;
		components++;
		size[v] -= size[u];
		parent[u] = u;
	}
	
	void save() { //O(1)
		savedCheckpoints.push_back(history.size());
	}
	
	void load() { //O(1) amortized
		//load to the last saved checkpoint
		assert(!savedCheckpoints.empty());
		while (history.size() > savedCheckpoints.back()) {
			rollback();
		}
		savedCheckpoints.pop_back();
	}
	
	Long getComponents() { //O(1)
		return components;
	}
} dsu;

enum {RANGE, QUERY, ADD, REMOVE};
struct Query{
	Long type; 
	Long u , v;
	Long l, r;
	Query(){}
	Query(Long type, Long id, Long u = -1, Long v = -1) :
		type(type), l(id), r(id), u(min(u , v)), v(max(u , v)){}
	bool operator <(const Query &other) const {
		if (other.type == QUERY) return false;
		if (type == QUERY) return true;
		return make_pair(make_pair(u , v), l) 
		< make_pair(make_pair(other.u , other.v), other.l);
	}
};

namespace DynamicConnectivity{
	vector<Query> transform(vector<Query> &queries) { //O(Q log Q)
		sort(queries.begin(), queries.end());
		vector<Query> ans;
		int i = 0;
		while (i < queries.size()) {
			if (queries[i].type == QUERY) {
				//queries
				ans.push_back(queries[i]);
				i++;
			} else {
				//change add-remove type by range type
				//range represents the interval in which the edge is activated
				assert(queries[i].type == ADD);
				Query newQuery = queries[i];
				newQuery.type = RANGE;
				if (i + 1 < queries.size() 
				&& queries[i + 1].u == queries[i].u && queries[i + 1].v == queries[i].v) {
					assert(queries[i + 1].type == REMOVE);
					newQuery.r = queries[i + 1].l;
					i += 2;
				} else {
					newQuery.r = queries.size();
					i++;
				}
				ans.push_back(newQuery);
			}
		}
		return ans;
	}
	
	bool intersect(pair<Long, Long> a, pair<Long, Long> b) { //O(1)
		return max(a.first, b.first) <= min(a.second, b.second);
	}
	
	void process(int l, int r, vector<Query> &queries, vector<Long> &answer) { //O(Q log Q log n)
		dsu.save();
		vector<Query> left;
		vector<Query> right;
		int mid = (l + r) / 2;
		for (Query query : queries) {
			if (query.type == QUERY) {
				if (query.l <= mid) left.push_back(query);
				else right.push_back(query);
			} else {
				if (query.l <= l && r <= query.r) {
					dsu.join(query.u, query.v);
				} else {
					if (intersect({query.l, query.r}, {l , mid})) {
						left.push_back(query);
					}
					if (intersect({query.l, query.r}, {mid + 1 , r})) {
						right.push_back(query);
					}
				}
			}
		}
		if (l == r) {
			for (Query query : queries) {
				if (query.type == QUERY) {
					answer.push_back(dsu.getComponents());
				}
			}
		} else {
			process(l , mid, left, answer);
			process(mid + 1 , r , right, answer);
		}
		dsu.load();
	}
	
	vector<Long> getAnswer(Long n, vector<Query> &queries){ //O(Q log Q log n)
		dsu.build(n);
		vector<Query> transformed = transform(queries);
		vector<Long> answer;
		process(0 , queries.size(), transformed, answer);
		return answer;
	}
};

int main() {
	Long n, m;
	cin >> n >> m;
	vector<Query> queries;
	for (int i = 0; i < m; i++) {
		char op;
		cin >> op;
		if (op == '+') {
			Long u, v;
			cin >> u >> v;
			u--;
			v--;
			queries.push_back(Query(ADD, i , u, v));
		} else if(op == '-') {
			Long u, v;
			cin >> u >> v;
			u--;
			v--;
			queries.push_back(Query(REMOVE, i, u, v));
		} else {
			queries.push_back(Query(QUERY, i));
		}
	}
	vector<Long> answer = DynamicConnectivity::getAnswer(n, queries);
	for (Long i = 0; i < answer.size(); i++) {
		cout << answer[i] << "\n";
	}
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

/*
add(u, v) — add an edge u − v into the graph;
remove(u, v) — add an edge u − v into the graph;
get() — return number of components
*/

const int MX = 1e5;

struct Checkpoint{
	Long u , v, sizeU, sizeV, components;
	Checkpoint(){}
	Checkpoint(Long u, Long v, Long sizeU, Long sizeV, Long components) :
		u(u), v(v), sizeU(sizeU), sizeV(sizeV), components(components){}
};

struct DSU{
	Long parent[MX];
	Long size[MX];
	vector<Checkpoint> history;
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
			history.push_back(Checkpoint(u , v, size[u], size[v], components));
			components--;
			parent[u] = v;
			size[v] += size[u];
		} else {
			history.push_back(Checkpoint(-1, -1, -1, -1, components));
		}
	}
	
	void rollback() { //O(1)
		//undo one join
		if (history.empty()) {
			return;
		}
		Checkpoint checkpoint = history.back();
		history.pop_back();
		components = checkpoint.components;
		if (checkpoint.u == -1) return;
		parent[checkpoint.u] = checkpoint.u;
		parent[checkpoint.v] = checkpoint.v;
		size[checkpoint.u] = checkpoint.sizeU;
		size[checkpoint.v] = checkpoint.sizeV;
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

struct Query{
	Long id;
	Long type; //0 -> range lifetime , 1 -> get , 2 -> add, 3 -> remove
	Long u , v;
	Long l, r;
	
	Query(){}
	Query(Long id, Long type, Long u = -1, Long v = -1) {
		this->id = id;
		this->type = type;
		this->u = min(u ,v);
		this->v = max(u , v);
	}
		
	void setRange(Long l, Long r, bool lifetime = true, int newId = -1) {
		this->l = l;
		this->r = r;
		if (lifetime) {
			type = 0;
		}
		id = newId;
	}
	
	bool operator <(const Query &other) const {
		return make_pair(make_pair(u , v), id) 
		< make_pair(make_pair(other.u , other.v), other.id);
	}
};

namespace DynamicConnectivity{
	vector<Query> transform(vector<Query> &queries, Long &cntGet) { //O(Q log Q)
		sort(queries.begin(), queries.end());
		vector<Query> ans;
		int i = 0;
		cntGet = 0;
		while (i < queries.size()) {
			Query newQuery;
			if (queries[i].type == 1) {
				//get
				newQuery = queries[i];
				newQuery.setRange(queries[i].id, queries[i].id, false, cntGet);
				i++;
				cntGet++;
			} else {
				//range
				assert(queries[i].type == 2);
				if (i + 1 < queries.size() && queries[i + 1].u == queries[i].u && queries[i + 1].v == queries[i].v) {
					assert(queries[i + 1].type == 3);
					newQuery = queries[i];
					newQuery.setRange(queries[i].id, queries[i + 1].id, true);
					i += 2;
				} else {
					newQuery = queries[i];
					newQuery.setRange(queries[i].id, queries.size(), true);
					i++;
				}
			}
			ans.push_back(newQuery);
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
			if (query.type == 1) {
				if (query.l <= mid) {
					left.push_back(query);
				} else {
					right.push_back(query);
				}
			} else {
				assert(query.type == 0);
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
				if (query.type == 1) {
					assert(l == query.l);
					answer[query.id] = dsu.getComponents();
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
		Long cntGet = 0;
		vector<Query> transformed = transform(queries, cntGet);
		vector<Long> answer(cntGet);
		process(0 , queries.size(), transformed, answer);
		return answer;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

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
	
	void reset() { //O(1) amortized
		while(!history.empty()) rollback();
	}
	
	Long getComponents() { //O(1)
		return components;
	}
} dsu;

int main() {
	return 0;
}

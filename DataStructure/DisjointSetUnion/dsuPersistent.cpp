#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

struct Checkpoint{
	Long u , v, sizeU, sizeV;
	Checkpoint(){}
	Checkpoint(Long u, Long v, Long sizeU, Long sizeV) :
		u(u), v(v), sizeU(sizeU), sizeV(sizeV){}
};
struct DSU{
	Long parent[MX];
	Long size[MX];
	vector<Checkpoint> history;
	
	void make_set(Long u) { //O(1)
		parent[u] = u;
		size[u] = 1;
	}
	
	void build(int n) {
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
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
			history.push_back(Checkpoint(u , v, size[u], size[v]));
			parent[u] = v;
			size[v] += size[u];
		} else {
			history.push_back(Checkpoint(-1, -1, -1, -1));
		}
	}
	
	void rollback() { //O(1)
		if (history.empty()) {
			return;
		}
		Checkpoint checkpoint = history.back();
		history.pop_back();
		if (checkpoint.u == -1) return;
		parent[checkpoint.u] = checkpoint.u;
		parent[checkpoint.v] = checkpoint.v;
		size[checkpoint.u] = checkpoint.sizeU;
		size[checkpoint.v] = checkpoint.sizeV;
	}
} dsu;

int main() {
	return 0;
}

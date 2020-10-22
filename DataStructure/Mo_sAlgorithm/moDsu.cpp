#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

//Given a graph G with N nodes and no edges. a 
//Given  a list of M edges and Q queries [l ,r] 
//for each query find the number of connected components
//in G with edges from l to r

const int MX = 5e4 + 1;
const int SZ_BLOCK = 223; //Aprox sqrt(N) or N / sqrt(Q)

//Block sqrt(N) -> overall O((M + Q) sqrt(M) log N)
//Block N / sqrt(Q) -> overall O(M sqrt(Q) log N) (best option)

struct DSU{
	int parent[MX];
	int size[MX];
	vector<int> history;
	vector<int> savedCheckpoints;
	int components;
	
	void make_set(int u) { //O(1)
		parent[u] = u;
		size[u] = 1;
	}
	
	void build(int n) { //O(n)
		for (int i = 0; i < n; i++) {
			make_set(i);
		}
		components = n;
	}
	
	int find(int u) { //O(log n)
		if (u == parent[u]) {
			return u;
		}
		return find(parent[u]);
	}
	
	void join(int u, int v) { //O(1)
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
		int u = history.back();
		int v = parent[u];
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
		if (savedCheckpoints.empty()) return;
		while (history.size() > savedCheckpoints.back()) {
			rollback();
		}
		savedCheckpoints.pop_back();
	}
	
	void reset() { //O(1) amortized
		while(!history.empty()) rollback();
	}
	
	int getComponents() { //O(1)
		return components;
	}
} dsu;

struct Query{
	int id, l, r;
	Query(){}
	Query(int id, int l, int r): id(id), l(l) , r(r){}
	
	bool operator <(const Query &other) const {
		//queries are sorted in increasing order of the block of l
		int curBlock = l / SZ_BLOCK ;
		int otherBlock = other.l / SZ_BLOCK;
		if (curBlock != otherBlock) return curBlock < otherBlock;
		
		//If queries are in the same blocks sort in increasing order of r
		return r < other.r;
	}
};

struct Edge{
	int u, v;
	Edge(){}
	Edge(int u, int v) : u(u), v(v){}
};

struct Mo{
	int getBlock(int i){
		return i / SZ_BLOCK;
	}
	
	int lowerLim(int i){
		return getBlock(i) * SZ_BLOCK;
	}
	
	int upperLim(int i, int sz){
		return min(lowerLim(i) + SZ_BLOCK - 1 , sz - 1);
	}
	
	vector<int> process(int n, vector<Edge> &edges, vector<Query> &queries) { //O(M sqrt(Q) log N)
		sort(queries.begin() , queries.end());
		dsu.build(n);
		vector<int> answer(queries.size());
		int q = 0;
		while (q < queries.size()) {
			int curBlock = getBlock(queries[q].l);
			dsu.reset();
			int curR = upperLim(queries[q].l, edges.size()) + 1;
			while (q < queries.size() && curBlock == getBlock(queries[q].l)) {
				if (getBlock(queries[q].l) == getBlock(queries[q].r)) {
					//same block -> bruteforce
					for (int i = queries[q].l; i <= queries[q].r; i++) {
						dsu.join(edges[i].u, edges[i].v);
					}
					answer[queries[q].id] = dsu.getComponents();
					dsu.reset();
				} else {
					dsu.load();
					for (int i = curR; i <= queries[q].r; i++) {
						dsu.join(edges[i].u, edges[i].v);
					}
					dsu.save();
					curR = queries[q].r + 1;
					for (int i = upperLim(queries[q].l, edges.size()); i >= queries[q].l; i--) {
						dsu.join(edges[i].u, edges[i].v);
					}
					answer[queries[q].id] = dsu.getComponents();
				}
				q++;
			}
		}
		return answer;
	}
}mo;

int main() {
	return 0;
}

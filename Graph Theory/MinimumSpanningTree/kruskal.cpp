#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;

struct DisjointSetUnion{
	Long parent[MAX];
	Long size[MAX];
	
	void make_set(Long v){ //O(1)
		parent[v] = v;
		size[v] = 1;
	}
	
	Long find_set(Long v){ //O(log(N))
		if(v==parent[v]){
			return v;
		}
		
		return parent[v] = find_set(parent[v]);
	}
	
	void union_sets(Long a, Long b){ //O(1)
		a = find_set(a);
		b = find_set(b);
		if(a != b){
			if(size[a] < size[b]){
				swap(a,b);
			}
			parent[b] = a;
			size[a] += size[b];
		}
	}
} dsu;

struct Edge{
	Long u,v,w;
	Edge() {}
	Edge(Long u, Long v, Long w) : u(u) , v(v) , w(w) {}
	bool operator <(Edge const &other) const{
        return w < other.w;
    }
};

struct Graph{
	vector<Edge> edges;
	vector<Long> tree[MAX];
	
	void clear(Long N) { //O(n+m)
		REP(i, N) {
			tree[i].clear();
		}
		edges.clear();
	}
	
	void addEdge(Long u, Long v, Long w) {
		u--;
		v--;
		edges.pb(Edge(u , v , w));
	}
	
	Long kruskal(Long N) { //O(mlogn)
		Long cost = 0;
		REP ( i , N ){
			dsu.make_set(i);
		}
		sort(edges.begin(),edges.end());
		
		for( Edge e : edges ) {
			if(dsu.find_set(e.u) != dsu.find_set(e.v)){
				cost += e.w;
				tree[e.u].pb(e.v);
				tree[e.v].pb(e.u);
				dsu.union_sets(e.u,e.v);				
			}
		}
		return cost;
	}
} G;

int main() {
	return 0;
}

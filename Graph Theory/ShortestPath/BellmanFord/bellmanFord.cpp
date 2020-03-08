#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e4;
const Long INF = 1e18;

struct Edge{
	Long u,v,weight;
	Edge(){}
	Edge(Long u, Long v, Long weight) : u(u) , v(v) , weight(weight) {}
};

struct Graph{
	vector<Edge> E;
	Long d[MX];
	Long parent[MX];
	
	void clear(Long N = MX) {
		E.clear();
	}

	void addEdge(Long u, Long v, Long w) {
		E.pb(Edge(u, v , w));
	}
	
	deque<Long> retrieveCycle(Long v, Long n){
		REP ( i , n) {
			v = parent[v]; //go back n times just in case
		}
		
		deque<Long> path;
		for(Long actual = v; ; actual = parent[actual]){
			path.push_front(actual);
			if(actual == v && path.size() > 1){
				break;
			}
		}
		return path;
	}
	
	deque<Long> retrievePath(Long v){
		if(parent[v] == -1){
			return {};
		}
		deque<Long> path;
		while(v != -1){
			path.push_front(v);
			v = parent[v];
		}
		return path;
	}
	
	bool bellmanFord(Long n, Long m, Long root = 0){ //O(nm)
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			parent[i] = -1;
		}
		d[root] = 0;
	
		Long negaCycle; //negative cycle flag
		REP(i , n) {
			negaCycle = -1; 
			REP ( j , m ) {
				if (d[E[j].u] < INF) {
					if (d[E[j].v] > d[E[j].u] + E[j].weight) {
						d[E[j].v] = max(-INF,d[E[j].u] + E[j].weight); //avoiding overflow
						parent[E[j].v] = E[j].u;
						negaCycle = E[j].v;
					}
				}
			}
			if(negaCycle == -1) break;
		}
		if(negaCycle == -1){
			return false; //no negative cycle
		}
		else{
			return true;
			//retrieveCycle(negaCycle, n);
		}
	
	}
} G;

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MX = 1e4;
const Long INF = 1e18;

struct Edge{
	Long u,v,cost;
	
	Edge(){
	}
	Edge(Long u, Long v, Long cost) : u(u) , v(v) , cost(cost) {
	}
	
};

struct Graph{
	vector<Edge> E;
	Long d[MX];
	Long p[MX];
	
	deque<Long> path;
	
	void clear(Long N) {
		REP(i , N) {
			d[i] = INF;
			p[i] = -1;
		}
		E.clear();
	}
	
	void addEdge(Long u, Long v, Long w) {
		E.pb(Edge(u, v , w));
	}
	
	void retrieveCycle(Long y, Long n){
		REP ( i , n) {
			y = p[y]; //retrocedemos por si acaso n veces. No hay perdida porque es un ciclo
		}
		
		path.clear();
		for(Long actual = y; ; actual = p[actual]){
			path.push_front(actual);
			if(actual == y && path.size() > 1){
				break;
			}
		}
	}
	
	bool beLongmanFord(Long n, Long m, Long root = 0){ //O(nm)
		REP(i , n) {
			d[i] = INF;
			p[i] = -1;
		}
		d[root] = 0;
	
		Long x;
		REP(i , n) {
			x = -1; //indicador de ciclo negativo
			bool mejora = false;
			REP ( j , m ) {
				if (d[E[j].u] < INF) {
					if (d[E[j].v] > d[E[j].u] + E[j].cost) {
						d[E[j].v] = max(-INF,d[E[j].u] + E[j].cost); //para evitar el overflow
						p[E[j].v] = E[j].u;
						x = E[j].v;
						mejora = true;
					}
				}
			}
			
			if(!mejora) break;
		}
		
		if(x == -1){
			return false; //no hay ciclo negativo
		}
		else{
			return true;
		
			retrieveCycle(x, n);
		}
	
	}
} G;


int main() {
	return 0;
}



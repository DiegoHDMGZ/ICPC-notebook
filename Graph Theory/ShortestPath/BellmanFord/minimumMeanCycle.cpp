#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef long double Double;

const Long MAX = 1e4;
const Double INF = 1e18;
const Double ERROR = 1e-6;	

struct Edge{
	Long u,v,cost;
	
	Edge(){
	}
	Edge(Long u, Long v, Long cost) : u(u) , v(v) , cost(cost) {
	}
};

struct Graph {
	vector<Edge> E;
	Double d[MAX];
	
	void clear(Long N = MAX-1) {
		REP(i , N+1) {
			d[i] = INF;
		}
		E.clear();
	}
	
	void addEdge(Long u, Long v, Long w) {
		E.pb(Edge(u, v , w));
	}
	
	bool beLongmanFord(Double c, Long n , Long m){
		d[0] = 0;
	
		Long x;
		REP( i , n) {
			x = -1; //indicador de ciclo negativo
			bool mejora = false;
			REP ( j , m) {
				if (d[E[j].u] < INF) {
					if (d[E[j].v] > d[E[j].u] + E[j].cost-c) {
						d[E[j].v] = max(-INF,d[E[j].u] + E[j].cost-c); //para evitar el overflow
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
		}
	
	}
	
	void init(Long &n, Long &m) {
		REP (i , n) {
			addEdge(0 , i + 1 , 0);
			m++;
		}
		n++;
	}
	
	Double minMeanCycle(Double ini, Double fin, Long n, Long m){
		init(n, m);
		if(!beLongmanFord(fin+1, n , m)){
			return -1;
		}
		
		while(fin-ini > ERROR){
			Double med = (ini+fin)/2.0;
			
			if(!beLongmanFord(med, n , m)){
				ini = med;
			}
			else{
				fin = med;
			}
		}
		return ini;
	}
	
}G;

Long caso = 1;

void doit(){
	Long n,m;
	cin >> n >> m;
	
	G.clear(n);
	Long maximo = 1;
	REP(i,m){
		Long u , v , w;  //1-indexed
		cin >> u >> v >> w;
		
		G.addEdge(u, v , w);
		maximo = max(maximo,w+1);
	}
	
	Double resp = G.minMeanCycle(0,maximo, n , m);
	cout << "Case #" << caso++ << ": ";
	
	if(resp == -1) cout << "No cycle found.\n";
	else cout << fixed << setprecision(2) << resp << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long T = 1;
	cin >> T;
	while(T--){
		doit();
	}
	return 0;
}

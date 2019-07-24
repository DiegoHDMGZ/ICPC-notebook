#include <bits/stdc++.h>
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
const Long MAX = 500;
const Long INF = 1e18;

struct Graph {
	Long d[MAX][MAX];
	Long w[MAX][MAX];
	Long p[MAX][MAX];
	vector<Long> path;
	
	void clean( Long N) {
		REP(i , N) {
			REP( j , N) {
				w[i][j] = INF, 
				d[i][j] = INF;
				p[i][j] = -1;
			}
		}
	}
	
	void addEdge(Long u, Long v, Long cost) {
		u--;
		v--;
		w[u][v] = min(w[u][v],cost);
		w[v][u] = w[u][v];
		d[u][v] = min(d[u][v],cost);
		d[v][u] = d[u][v];
	}
	
	void retrievePath(Long i, Long j, bool clean = true){ //O(n)
		
		if(clean){
			path.clear();
			clean = false;
			path.pb(i);
			if(i == j) return;
		}
		
		if(p[i][j] == -1){
			
			path.pb(j);
			return;
		}
		
		retrievePath(i,p[i][j],clean);
		retrievePath(p[i][j],j,clean);
	}
	
	void floydWarshall(Long n){ //O(n³)
		REP(i, n) {
			d[i][i] = 0;
		}
		
		REP(k,n){
			REP(i,n){
				REP(j,n){
					if(d[i][k] < INF && d[k][j] < INF){
						//if (d[i][k] + d[k][j] < d[i][j] - EPS)  //real weights
						if(d[i][j] > d[i][k]+d[k][j]){
							d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
							p[i][j] = k;
						}
						
					}
				}
			}
		}
		
		//negative cycle
		REP(i,n){
			REP(j,n){
				REP(k,n){
					if(d[i][k] < INF && d[k][j] < INF && d[k][k] < 0){
						d[i][j] = -INF;
					}
				}
			}
		}
	
	}
} G;






int main() {
	return 0;
}



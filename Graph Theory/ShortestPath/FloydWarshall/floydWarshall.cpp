#include <bits/stdc++.h>
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const int MX = 500;
const Long INF = 1e18;
struct Graph{
	Long d[MX][MX];
	Long parent[MX][MX];
	
	void initialize(Long n) {
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				d[u][v] = INF;
				parent[u][v] = -1;
			}
			d[u][u] = 0;
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		d[u][v] = min(d[u][v], w);
	}
	
	vector<Long> getPath(Long u, Long v) {
		if (d[u][v] == INF) return {};
		if (u == v) {
			return {u};
		}
		if (parent[u][v] == -1) {
			return {u, v};
		}
		vector<Long> left = getPath(u, parent[u][v]);
		vector<Long> right = getPath(parent[u][v], v);
		left.pop_back();
		for (Long x : right) {
			left.push_back(x);
		}
		return left;
	}
	
	void floydWarshall(Long n) { //O(V^3)
		for (int k = 0; k < n; k++) {
			for (int u = 0; u < n; u++) {
				for (int v = 0; v < n; v++) {
					if (d[u][k] == INF) continue;
					if (d[k][v] == INF) continue;
					if (d[u][k] + d[k][v] < d[u][v]) {
						d[u][v] = d[u][k] + d[k][v];
						parent[u][v] = k;
					}
				}
			}
		}
		//negative cycles
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				for (int k = 0; k < n; k++) {
					if (d[k][k] < 0 && d[u][k] != INF && d[k][v] != INF) {
						d[u][v] = -INF;
					}
				}
			}
		}
	}
}G;

int main() {
	return 0;
}

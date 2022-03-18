#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef int Cap;
const int MX = 3000;

//This template does not build the entire transitive edges

struct GraphFlow {
	//max flow template
	//Use 2 * MX + 2 for the array sizes
	void clear(int n);
	void addEdge(int u, int v, Cap w, bool dir);
	Cap maxFlow(int s, int t, int n);
} GFlow;

struct Graph{
	void clear(int n) {GFlow.clear(2 * n + 2);}
	int left(int u) {return 2 * u;}
	int right(int u) {return 2 * u + 1;}
	
	void addEdge(int u, int v) {
		GFlow.addEdge(left(u), right(v), MX, true);
	}

	int maxAntiChain(int n) {
		//O(E * V) for FF/Dinic
		//n is the number of nodes in the original graph
		int s = 2 * n;
		int t = 2 * n + 1;
		for (int u = 0; u < n; u++) {
			GFlow.addEdge(s, left(u), 1, true);
			GFlow.addEdge(right(u), t, 1, true);
			GFlow.addEdge(right(u), left(u), n, true);
		}
		return n - GFlow.maxFlow(s, t, 2 * n + 2);
	}
} G; 

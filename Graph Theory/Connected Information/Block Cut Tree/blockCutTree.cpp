#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 1e5;  

struct Edge{
	Long u, v;
	Edge(Long u , Long v) : u(u) , v(v){
	}
	Edge(){
	}
	
	bool operator == (const Edge &E) const {
		return E.u == u && E.v == v;
	}
	
	bool operator != (const Edge &E) const {
		return !(E == *this);
	}
};

struct Graph {
	vector <Long> adj[3 * MAX];
	bool vis[3 * MAX];
	Long tIn[3 * MAX];//tiempo de entrada al nodo
	Long low[3 * MAX];//minimo tiempo al que puede ir ese nodo o uno de sus descendientes por medio de cualquier arista(tree o back edge) 
	Long timer = 0;
	vector<Edge> bridge;
	vector<Long> articulation;
	bool isArticulation[3 * MAX];
	bool usedArticulation[3 * MAX];
	Long biconnectedComponent[3 * MAX];
	Long component = 0;
	stack<Edge> edges;
	
	Graph* BCT;
	
	void clear(Long N ) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			tIn[i] = -1;
			low[i] = -1;
			isArticulation[i] = false;
			biconnectedComponent[i] = 0;
			usedArticulation[i] = false;
		}
		bridge.clear();
		articulation.clear();
		timer = 0;
		component = N;
		BCT = new Graph();
	}
	
	void addEdge(Long u, Long v, bool disminuir = true) {
		if(disminuir){
			u--;
			v--;
		}
		
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	/*void addBiconnectedComponent(Long u, Long v) {
		cout << "Component :" << endl;
		while(!edges.empty() && edges.top() != Edge(u,v)){
			cout << edges.top().u + 1 << " " << edges.top().v + 1 << endl;
			biconnectedComponent[edges.top().u] = biconnectedComponent[edges.top().v] = component;
			edges.pop();
		}
		cout << edges.top().u + 1 << " " << edges.top().v + 1 << endl;
		biconnectedComponent[edges.top().u] = biconnectedComponent[edges.top().v] = component;
		edges.pop();
		debug(u + 1);
		debug(component + 1);
		cout << "*****************" << endl;
		component++;
	}*/
	
	void addBiconnectedComponent(Edge e){
		if(edges.empty()) return;
		vector<Edge> aux;
		cout << "Component :" << endl;
		while(!edges.empty() && edges.top() != e){
			cout << edges.top().u + 1 << " " << edges.top().v + 1 << endl;
			biconnectedComponent[edges.top().u] = biconnectedComponent[edges.top().v] = component;
			aux.pb(edges.top());
			usedArticulation[edges.top().u] = usedArticulation[edges.top().v] = false;
			edges.pop();
		}
		if(!edges.empty()){
			cout << edges.top().u + 1 << " " << edges.top().v + 1 << endl;
			biconnectedComponent[edges.top().u] = biconnectedComponent[edges.top().v] = component;
			aux.pb(edges.top());
			usedArticulation[edges.top().u] = usedArticulation[edges.top().v] = false;
			edges.pop();
		}
		for(Edge x : aux){
			if(isArticulation[x.u] && !usedArticulation[x.u]) {
				usedArticulation[x.u] = true;
				BCT->addEdge(x.u, component, false);
			}
			if(isArticulation[x.v] && !usedArticulation[x.v]) {
				usedArticulation[x.v] = true;
				BCT->addEdge(x.v, component, false);
			}
		}
		cout << "*****************" << endl;
		component++;
	}
	
	void dfs(Long u, Long p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		Long children = 0;
		for(Long v : adj[u]) {
			
			if(v == p) continue;
			/*debug(u + 1);
			debug(v + 1);
			cout << endl;
			*/
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
				if(tIn[v] < tIn[u]){
					edges.push(Edge(u , v));
				}
			} else {
				edges.push(Edge(u , v));
				dfs(v , u);
				
				low[u] = min(low[u] , low[v]);
				if(low[v] > tIn[u]) {
					bridge.pb(Edge(u , v));
				}
				if(low[v] >= tIn[u] && p != -1 ) {
					if(!isArticulation[u]){
						articulation.pb(u);
						isArticulation[u] = true;
					} 
					addBiconnectedComponent(Edge(u, v));
				}
				children++;
			}
		}
		
		if(p == -1 ) {
			if(children > 1){
				articulation.pb(u);
				isArticulation[u] = true;
			}
			addBiconnectedComponent(Edge(-1 , -1));
		} 
		
	}
	
	void calculate(Long n) { //O(N + M)
		for(Long i = 0; i < n; i++) {
			if(!vis[i]) {
				dfs(i);
			}
		}
	}
	
	void printBlockCutTree(Long n){
		REP(i , n){
			cout << "biconnectedComponent[" << i + 1 << "] = " << biconnectedComponent[i] + 1 << endl;
		}
		REP(i , 3 * n){
			for(Long v : BCT->adj[i]){
				cout << i + 1 << " -> " << v + 1 << endl;
			}
		}
	}
	
	void printBridges() {
		cout << "Bridges = ";
		REP(i , bridge.size()){
			cout << "( " << bridge[i].u + 1 << " - " << bridge[i].v + 1 << " ) ; ";
		}
	} 	
	
	void printArticulations() {
		cout << "Articulations = ";
		REP(i , articulation.size()) {
			cout << articulation[i] + 1 << " ";
		}
		cout << endl;
	}
	
} G;
 
/*
11 14
1 2
1 3
2 3
2 4
2 5
3 5
4 9
9 10
9 11
10 11
5 7
5 6
6 7
6 8
 
11 13
1 11
11 2
2 3
2 4
3 4
11 5
5 6
5 7
7 6
11 8
8 9
9 10
10 8
 

*/

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n >> m;
	G.clear(n);
	REP(i , m) {
		Long u , v;
		cin >> u >> v;
		G.addEdge(u , v);
	}
	G.calculate(n);
	G.printArticulations();
	G.printBlockCutTree(n);
	
	return 0;
}


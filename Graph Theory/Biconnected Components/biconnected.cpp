#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(int i = 0; i < (int)n ; i++)

using namespace std;

//biconnected component is a maximal subgrah that does not have articulation points

struct Edge{
	int u, v;
	Edge(int u , int v) : u(min(u , v)) , v(max(u,v)){
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

const int MX = 1e5;
const int MX2 = 2 * MX;

struct BlockCutTree{
	vector<int> adj[MX2];
	
	void addEdge(int u , int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void clear(int N){
		REP(i , N){
			adj[i].clear();
		}
	}
};

struct Graph{
	vector<int> adj[MX];
	bool vis[MX];
	int tIn[MX];
	int low[MX];
	int timer;
	stack<Edge> edges;
	bool isArticulation[MX];
	map<int,bool> isBridge[MX];
	
	int bcn[MX]; //biconnected component of node. Articulation are considered separated
	map<int,int> bce[MX]; //biconnected component of edge
	vector<int> articulation;
	vector<Edge> bridge;
	int lastComponent[MX];
	
	BlockCutTree bct;
	int numComponent;
	
	void clear(int N){
		articulation.clear();
		bridge.clear();
		timer = numComponent = 0;
		bct.clear(2 * N);
		REP(i , N){
			adj[i].clear();
			tIn[i] = low[i] = 0;
			isArticulation[i] = false;
			vis[i] = false;
			isBridge[i].clear();
			bce[i].clear();
			lastComponent[i] = -1;
		}
	}
	
	Graph(){
		clear(MX);
	}
	void addEdge(int u , int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void addArticulation(int u){
		if(!isArticulation[u]){
			isArticulation[u] = true;
			bcn[u] = numComponent++;
			articulation.push_back(u);
		}
	}
	
	void addEdgeBCT(int u){
		if(!isArticulation[u]){
			bcn[u] = numComponent;
		} else {
			if(lastComponent[u] != numComponent){
				bct.addEdge(bcn[u] , numComponent);
				lastComponent[u] = numComponent;
			}
		}
	}
	
	void addBiconnectedComponent(Edge e){
		if(edges.empty()) return;
		
		while(!edges.empty()){
			Edge cur = edges.top();
			int u = cur.u;
			int v = cur.v;
			addEdgeBCT(u);
			addEdgeBCT(v);
			bce[u][v] = numComponent;
			edges.pop();
			if(cur == e){
				break;
			}
		}
		numComponent++;
	}
	
	void dfs(int u = 0, int p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		int children = 0;
		for(int v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
				if(tIn[v] < tIn[u]){
					edges.push(Edge(u , v));
				}
			} else {
				edges.push(Edge(u , v));
				dfs(v , u );
				low[u] = min(low[u] , low[v]);
				if(low[v] > tIn[u]) {
					isBridge[min(u,v)][max(u,v)] = true;
					bridge.push_back(Edge(u , v));
				}
				if(low[v] >= tIn[u] && p != -1 ) {
					addArticulation(u);
					addBiconnectedComponent(Edge(u,v));
				}
				children++;
				if(p == -1 && children > 1){
					addArticulation(u);
					addBiconnectedComponent(Edge(u,v));
				}
			}
		}
		if(p == -1 ) {
			addBiconnectedComponent(Edge(-1,-1));
		} 
	}
	
	void buildBicomponents(int n){
		for(int i = 0; i < n; i++){
			if(!vis[i]) dfs(i);
		}
	}
	
	void printBlockCutTree(int n){
		REP(i , n){
			cout << "biconnectedComponent[" << i + 1 << "] = " << bcn[i] + 1 << endl;
		}
		REP(i , 2 * n){
			for(int v : bct.adj[i]){
				cout << i + 1 << " -> " << v + 1 << endl;
			}
		}
	}
	
	void printBridges() {
		cout << "Bridges = ";
		REP(i , bridge.size()){
			cout << "( " << bridge[i].u + 1 << " - " << bridge[i].v + 1 << " ) ; ";
		}
		cout << endl;
	} 	
	
	void printArticulations() {
		cout << "Articulations = ";
		REP(i , articulation.size()) {
			cout << articulation[i] + 1 << " ";
		}
		cout << endl;
	}
} G;

int main(){
	return 0;
}

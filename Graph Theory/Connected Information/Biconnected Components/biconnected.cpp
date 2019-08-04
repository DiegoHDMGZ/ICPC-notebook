#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(int i = 0; i < (int)n ; i++)
#define pb push_back

using namespace std;

//https://www.spoj.com/problems/POLQUERY/

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

const int MAX = 1e5;
const int MAX2 = 2 * MAX;

struct BCT{
	vector<int> adj[MAX2];
	
	void addEdge(int u , int v){
		adj[u].pb(v);
		adj[v].pb(u);
	}
};


struct Graph{
	vector<int> adj[MAX];
	bool vis[MAX];
	int tIn[MAX];
	int low[MAX];
	int timer;
	stack<Edge> edges;
	bool isArticulation[MAX];
	unordered_map<int,bool> isBridge[MAX];
	
	int bcn[MAX]; //biconnected component of node. Articulation are considered separated
	unordered_map<int,int> bce[MAX]; //biconnected component of edge
	vector<int> articulation;
	vector<Edge> bridge;
	
	BCT bct;
	int numComponent;
	Graph(){
		timer = 0;
		numComponent = 0;
	}
	void addEdge(int u , int v){
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void addBiconnectedComponent(Edge e){
		if(edges.empty()) return;
		
		unordered_set<int> processed; //articulation processed
		while(!edges.empty()){
			Edge cur = edges.top();
			int u = cur.u;
			int v = cur.v;
	
			if(!isArticulation[u]){
				bcn[u] = numComponent;
			} else {
				if(processed.find(u) == processed.end()){
					bct.addEdge(bcn[u] , numComponent);
					processed.insert(u);
				}
			}
			if(!isArticulation[v]){
				bcn[v] = numComponent;
			} else {
				if(processed.find(v) == processed.end()){
					bct.addEdge(bcn[v] , numComponent);
					processed.insert(v);
				}
			}
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
					if(!isArticulation[u]){
						isArticulation[u] = true;
						bcn[u] = numComponent++;
						articulation.push_back(u);
					}
					Edge e = Edge(u,v);
					addBiconnectedComponent(e);
				}
				children++;
				if(p == -1 && children > 1){
					if(!isArticulation[u]){
						isArticulation[u] = true;
						bcn[u] = numComponent++;
						articulation.push_back(u);
					}
					Edge e = Edge(u,v);
					addBiconnectedComponent(e);
				}
			}
		}
		if(p == -1 ) {
			Edge e = Edge(-1,-1);
			addBiconnectedComponent(e);
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
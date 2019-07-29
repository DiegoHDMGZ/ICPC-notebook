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
const int loga = 18;

struct SparseTable{
	pair<int,int> st[2 * MAX2][loga + 1]; //<min height , node>
	
	pair<int,int> f(pair<int,int> a, pair<int,int> b){
		return min(a , b);
	}

	pair<int,int> f(pair<int,int> a){
		return a;
	}
	
	void build(vector<pair<int,int>> &A){ // O(n log n)
		int n = A.size();
		for(int i = 0; i < n; i++){
			st[i][0] = f(A[i]);
		}
		
		for(int j = 1; (1 << j) <= n; j++){
			for(int i = 0; i + (1 << j) <= n; i++){
				st[i][j] = f(st[i][j-1], st[i + (1 << (j-1))][j-1]);
			}
		}
	}
	
	int query(int L, int R){ //O(1)
		int T = R - L + 1;
		int lg = 31 - (__builtin_clz(T));
		return f(st[L][lg], st[R- (1LL << lg) + 1][lg]).second;
	}
	
}st;
 
struct BCT{
	vector<int> adj[MAX2];
	vector<pair<int,int>> euler;
	int first[MAX2];
	int height[MAX2];
	int tIn[MAX2];
	int tOut[MAX2];
	int timer = 0;
	
	void addEdge(int u , int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int u = 0, int p = -1){ //O(n+m)
		tIn[u] = timer++;
		first[u] = euler.size();
		euler.push_back({height[u], u });
		for ( int v : adj[u] ) {
			if(p != v){
				height[v] = height[u] + 1;
				dfs(v , u);
				euler.push_back({height[u], u});
			}
		}
		tOut[u] = timer++;
	}

	void precalculate(int N, int root = 0){ //O(nlogn)
		height[root] = 0;
		dfs(root);
		st.build(euler);
	}
	
	int lca(int u, int v){ //O(logn)
		return st.query(min(first[u] , first[v]) , max(first[u] , first[v]));
	}
	
	bool isAncestor(int u, int v){ //is u ancestor of v ?
		return tIn[u] < tIn[v] && tOut[u] > tOut[v];
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
	
	//vector<int> articulation;
	//vector<Edge> bridge;
	
	BCT bct;
	
	int numComponent;
	Graph(){
		timer = 0;
		numComponent = 0;
	}
	void addEdge(int &u , int &v){
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void addBiconnectedComponent(Edge &e){
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
					//bridge.push_back(Edge(u , v));
				}
				
				if(low[v] >= tIn[u] && p != -1 ) {
					if(!isArticulation[u]){
						isArticulation[u] = true;
						bcn[u] = numComponent++;
						//articulation.push_back(u);
					}
					Edge e = Edge(u,v);
					addBiconnectedComponent(e);
				}
				
				children++;
				if(p == -1 && children > 1){
					if(!isArticulation[u]){
						isArticulation[u] = true;
						bcn[u] = numComponent++;
						//articulation.push_back(u);
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
	
	bool inPath(int &A, int &B, int &C) {
		int x = bct.lca(A , B); 
		if(C == x) {
			return true;
		}
		if(bct.isAncestor(x , C) && bct.isAncestor(C, A)) {
			return true;
		}
		if(bct.isAncestor(x , C)  && bct.isAncestor(C, B)) {
			return true;
		}
		return false;
	}
	
	bool query(int &A, int &B, int &G1, int &G2) {
		A--;
		B--;
		G1--;
		G2--;
		
		if(adj[A].size() == 1) {
			if(G1 == A || G2 == A) {
				return false;
			} 
		}
		if(adj[B].size() == 1){
			if(G1 == B || G2 == B) {
				return false;
			}
		}
		
		if(isBridge[min(G1 , G2) ][max(G1,G2)]) {
			int C = bce[min(G1 , G2) ][ max(G1,G2)];
			A = bcn[A];
			B = bcn[B];
			return !inPath(A, B , C);
		} else {
			//no es puente
			return true;
		}
		
		
		return true;
	}	 
	
	bool query(int &A, int &B, int &C) {
		A--;
		B--;
		C--;
		
		if(bcn[A] == bcn[B]) {
			return true;
		}
		if(bcn[B] == bcn[C]) {
			return true;
		}
		if(bcn[A] == bcn[C]) {
			return true;
		}
		
		if(!isArticulation[C]){
			return true;
		}
		int x = bcn[A];
		int y = bcn[B];
		int z = bcn[C];
		/*debug(x);
		debug(y);
		debug(z);*/
		return !inPath(x , y , z);
	}
	
	/*void printBlockCutTree(int n){
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
	}*/
} G;

int main(){
	
	int n, m;
	scanf("%d %d", &n , &m);
	REP(i , m) {
		int u , v;
		scanf("%d %d", &u , &v);
		G.addEdge(u , v);
	}
	G.dfs();
	G.bct.precalculate(G.numComponent);
	
	int Q;
	scanf("%d", &Q);
	REP(q , Q) {
		int tipo;
		scanf("%d", &tipo);
		if(tipo == 1){
			int A, B, G1 , G2;
			scanf("%d %d %d %d", &A , &B, &G1 , &G2);
			if(G.query(A, B , G1 , G2)) {
				printf("da\n" );
			} else {
				printf("ne\n" );
			}
		} else {
			int A , B , C;
			scanf("%d %d %d", &A , &B, &C);
			if(G.query(A, B , C)) {
				printf("da\n" );
			} else {
				printf("ne\n" );
			}
		}
	}
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/contest/1253/problem/F
 
const Long MX = 3e5;
bool used[MX];
const Long loga = log2(MX)+1;

struct EndPoint{
	Long node, w;
	EndPoint(){}
	EndPoint(Long node, Long w) : node(node), w(w) {}
};

 
struct Path{
	Long node, weight, ini;
	Path(){}
	Path(Long node , Long weight, Long ini) : node(node), weight(weight) , ini(ini){}
	bool operator < (const Path &P) const{
		if(weight == P.weight){
			return node > P.node;
		}
		return weight > P.weight;
	}
};
 
const Long INF = 1e18;
 

struct Tree{
	vector<EndPoint> adj [MX];
	
	Long anc[MX][loga]; //anc[i][j] : ancestor of i at distance 2^j
	Long height[MX]; 
	pair<Long,Long> st[MX][loga]; //st[i][j] : min/max edge starting at i and ending at anc[i][j]
	int tIn[MX];
	int tOut[MX];
	int timer = 0;
	
	void addEdge(Long u , Long v, Long w) {
		adj[u].push_back(EndPoint(v , w));
		adj[v].push_back(EndPoint(u , w));
	}
	
	void dfs(Long u = 0){ //O(n+m)
		tIn[u] = timer++;
	
		for(EndPoint e : adj[u]){
			Long v = e.node;
			Long w = e.w;
			if(anc[u][0] != v){
				anc[v][0] = u;
				st[v][0] = {w, w};
				height[v] = height[u] + 1;
				dfs(v);
			}
		}
		tOut[u] = timer++;
	}
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return {min(a.first,b.first) , max(a.second, b.second)}; 
	}
	
	
	void precalculate(Long n, Long root = 0){ //O(nlogn)
		anc[root][0] = -1;
		height[root] = 0;
		dfs(root);
		
		for(int j = 1; (1 << j) < n; j++){
			for(int i = 0; i < n; i++){
				if(anc[i][j-1] != -1){
					anc[i][j] = anc[anc[i][j-1]][j-1];
					st[i][j] = f(st[i][j-1],st[anc[i][j-1]][j-1]);
				} else {
					anc[i][j] = -1;
				}
			}
		}
	}
	
	pair<Long,Long> bestOnPath(Long u, Long v){ //O(logn) <min, max>
		if(height[u] < height[v]){
			swap(u,v);
		}
		int lg = 31 - (__builtin_clz(height[u]));
		
		pair<Long,Long> bestU,bestV;
		bestU = bestV = {INF, -INF}; //cambiar para min
		for(Long i = lg; i >= 0; i--){
			if(height[u] - (1 << i) >= height[v]){
				bestU = f(bestU,st[u][i]);
				u = anc[u][i];
			}
		}
		
		if(u == v){
			return bestU;
		}
		
		for(int i = lg; i >= 0; i--){
			if(anc[u][i] != anc[v][i]){
				bestU = f(bestU,st[u][i]);
				bestV = f(bestV,st[v][i]);
				u = anc[u][i], v = anc[v][i];
			}
		}
		bestU = f(bestU , st[u][0]);
		bestV = f(bestV , st[v][0]); 
		return f( bestU, bestV );
	}
	
	bool isAncestor(Long u, Long v){ //is u ancestor of v ?
		return tIn[u] < tIn[v] && tOut[u] > tOut[v];
	}	
}G3;

struct DSU{
	Long parent[MX];
	Long size[MX];
	
	void make_set(Long v){ //O(1)
		parent[v] = v;
		size[v] = 1;
	}
	
	Long find(Long v){ //O(1) amortized
		if(v==parent[v]){
			return v;
		}
		
		return parent[v] = find(parent[v]);
	}
	
	void join(Long a, Long b){ //O(1) amortized
		a = find(a);
		b = find(b);
		
		if(a != b){
			if(size[a] < size[b]){
				swap(a,b);
			}
			parent[b] = a;
			size[a] += size[b];
		}
	}
} dsu;

struct Edge{
	Long u,v,w;
	Edge() {}
	Edge(Long u, Long v, Long w) : u(u) , v(v) , w(w) {}
	bool operator <(Edge const &other) const{
        return w < other.w;
    }
};

struct Graph2{
	vector<Edge> edges;

	
	void addEdge(Long u, Long v, Long w) {
		edges.pb(Edge(u , v , w));
	}
	
	void kruskal(Long N) { //O(mlogn)
		REP ( i , N ){
			dsu.make_set(i);
		}
		sort(edges.begin(),edges.end());
		
		for( Edge e : edges ) {
			if(dsu.find(e.u) != dsu.find(e.v)){
				G3.addEdge(e.u , e.v, e.w);
				dsu.join(e.u,e.v);				
			}
		}
	}
} G2;
 
struct Graph{
	vector<Path> adj[MX];
	bool vis[MX];
	Long reachedBy[MX];
	Long d[MX];
	
 
	void clear(Long n){
		REP(i , n){
			d[i] = INF;
		}
	}
	
	void addEdge(Long u, Long v, Long w ){
		adj[u].pb(Path(v, w, -1));
		adj[v].pb(Path(u, w, -1));
	}
	
	void dijkstra(vector<Long> &root ,Long n){
		priority_queue<Path> q;
		Long c = 0;
		REP(i , n){
			reachedBy[i] = -1;
		}
		for(Long u  : root){
			d[u] = 0;
			reachedBy[u] = u;
			q.push(Path(u, d[u] , u));
		}
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			Long u = p.node;
			//debug(u);
			if(reachedBy[u] != p.ini){
				G2.addEdge(reachedBy[u] , p.ini , d[u] + p.weight);
			}
			if(vis[u]) {
				continue;
			}
			
			vis[u] = true;
			for(Path x : adj[u]){
				Long v = x.node;
				//debug(v);
				if(p.ini != reachedBy[v] && reachedBy[v] != -1){
					G2.addEdge(reachedBy[v] , p.ini , x.weight + d[v] + p.weight);
				}
				if(vis[v]) {
					continue;
				}
				if(d[u] + x.weight < d[v]){
					d[v] = d[u] + x.weight;
					q.push(Path(v , d[v] , p.ini));
					reachedBy[v] = p.ini;
				} 
			}
		}
		
	}
}G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n , m , k , q;
	cin >> n >> m >> k >> q;
	G.clear(n);
	vector<Long> root;
	REP(i, k){
		root.pb(i);
		dsu.make_set(i);
	}
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		u--;v--;
		G.addEdge(u , v , w);
	}
	G.dijkstra(root , n);
	
	G2.kruskal(n);
	G3.precalculate(k);
	REP(i , q){
		Long u , v;
		cin >> u >> v;
		u--;
		v--;
		cout << G3.bestOnPath(u , v).second << "\n";
	}
	return 0;
}

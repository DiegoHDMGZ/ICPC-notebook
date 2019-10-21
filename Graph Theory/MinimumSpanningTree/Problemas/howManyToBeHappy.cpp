#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://codeforces.com/gym/101667/attachments

const Long MX = 300;
const Long INF = 1e18;
const Long loga = log2(MX)+1;

struct DisjointSetUnion{
	Long parent[MX];
	Long size[MX];
	
	void make_set(Long v){ //O(1)
		parent[v] = v;
		size[v] = 1;
	}
	
	Long find(Long v){ //O(log(N))
		if(v==parent[v]){
			return v;
		}
		
		return parent[v] = find(parent[v]);
	}
	
	void join(Long a, Long b){ //O(1)
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

struct Tree{
	vector<Long> adj [MX];
	vector<Long> cost[MX];
	
	Long anc[MX][loga]; //anc[i][j] : ancestor of i at distance 2^j
	Long height[MX]; 
	pair<Long,Long> st[MX][loga]; //st[i][j] : min/max edge starting at i and ending at anc[i][j]
	int tIn[MX];
	int tOut[MX];
	int timer = 0;
	
	void clear(Long N) {
		for(Long i = 0; i < N; i++) {
			adj[i].clear();
			cost[i].clear();
		}
		timer = 0;
	}
	
	void addEdge(Long u , Long v, Long w) {
		adj[u].push_back(v);
		adj[v].push_back(u);
		cost[u].push_back(w);
		cost[v].push_back(w);
	}
	
	void dfs(Long u = 0){ //O(n+m)
		tIn[u] = timer++;

		for ( Long i = 0; i < adj[u].size(); i++) {
			Long v = adj[u][i];
			Long w = cost[u][i];
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
	
	
	void precalculate(Long N, Long root = 0){ //O(nlogn)
		anc[root][0] = -1;
		height[root] = 0;
		dfs(root);
		
		for(int j = 1; (1 << j) < N; j++){
			for(int i = 0; i < N; i++){
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
} tree;

struct Graph{
	vector<Edge> edges;
	bool used[MX];
	
	void addEdge(Long u, Long v, Long w) {
		edges.pb(Edge(u , v , w));
	}
	
	Long kruskal(Long N, Long indEdge) { //O(mlogn)
		tree.clear(N);
		Edge fixed = edges[indEdge];
		REP ( i , N ){
			dsu.make_set(i);
		}

		dsu.join(fixed.u , fixed.v);
		tree.addEdge(fixed.u, fixed.v, fixed.w);
		
		
		for( Edge e : edges ) {
			if(dsu.find(e.u) != dsu.find(e.v)){
				dsu.join(e.u,e.v);
				tree.addEdge(e.u , e.v, e.w);				
			}
		}
		tree.precalculate(N);
		Long ans = 0;
		for(Edge e : edges){
			if(e.w < tree.bestOnPath(e.u, e.v).second){
				ans++;
			}
		}
		if(ans > 0){
			cout <<"fixed = " << fixed.u + 1 << " " << fixed.v + 1 << " " << fixed.w << endl;
			debug(ans);
			cout << endl;
		}
		return ans;
	}
} G;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n,m;
	cin >> n >> m;
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		u--; v--;
		G.addEdge(u , v , w);
	}
	Long ans = 0;
	sort(G.edges.begin(),G.edges.end());
	REP(i , m){
		ans += G.kruskal(n, i);
	}
	cout << ans << endl;
	return 0;
}

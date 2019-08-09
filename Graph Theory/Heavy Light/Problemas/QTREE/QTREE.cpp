#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://www.spoj.com/problems/QTREE/

const Long MAX = 1e4+10;
Long nTree;

Long combine(Long x , Long y) {
	return max(x, y);
}

struct SegmentTree{
	Long t[4 * MAX];
	Long maxN;
	
	void setN(Long x) {
		maxN = x;
	}

	Long query(Long l, Long r, Long v , Long tl , Long tr ) { //O(logn)
		if (l > r) {
			return 0;
		}
		if (l == tl && r == tr) {
			return t[v];
		}
		Long tm = (tl + tr) / 2;
		return combine(query(l, min(r, tm), 2 * v, tl, tm) , query(max(l, tm + 1), r, 2 * v + 1, tm + 1, tr));
	}
	
	Long query(Long l , Long r) {
		assert(maxN > 0);
		return query(l , r , 1 , 0 , maxN - 1);
	}

	void update(Long pos, Long valor, Long v, Long tl , Long tr) { //O(logn)
		if (tl == tr) {
			t[v] = valor;
		}
		else{
			Long tm = (tl + tr) / 2;
			if (pos <= tm) {
				update(pos, valor, 2 * v, tl, tm);
			}
			else {
				update(pos, valor, 2 * v + 1, tm + 1, tr);
			}
			t[v] = combine( t[2 * v] , t[2 * v + 1] );
		}
	}
	
	void update(Long pos, Long valor) {
		assert(maxN > 0);
		update(pos , valor, 1 , 0 , maxN - 1);
	}
} st;

struct Graph {
	vector <Long> adj[MAX];
	Long parent[MAX];
	Long depth[MAX];
	Long heavy[MAX];
	Long head[MAX];
	Long pos[MAX];
	Long curPos = 0;
	
	void clear(Long N = MAX) { //O(N)
		REP( i , N) {
			adj[i].clear();
			parent[i] = -1;
			heavy[i] = -1;
			depth[i] = head[i] = pos[i] = 0;
		}
		curPos = 0;
		//st.clear(N);
	}
	
	void addEdge(Long u, Long v) { //O(1)
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	Long dfs(Long u = 0){ //O(N + M)
		Long sz = 1;
		Long maxSize = 0;
		heavy[u] = -1;
		for(Long v : adj[u]){
			if(v != parent[u]) {
				parent[v] = u;
				depth[v] = depth[u] + 1;
				Long szV = dfs(v);
				sz += szV;
				if(szV > maxSize) {
					maxSize = szV;
					heavy[u] = v;
				}
			}
		}
		
		return sz;
	}
	
	void decompose(Long u , Long h ) { //O(N + M)
		head[u] = h;
		pos[u] = curPos++;
		if(heavy[u] != -1) {
			decompose(heavy[u] , h);
		}
		
		for(Long v : adj[u]) {
			if(v != parent[u] && v != heavy[u] ) {
				decompose(v , v);
			}
		}
	}
	
	void decompose(Long u = 0){
		curPos = 0;
		depth[u] = 0;
		parent[u] = -1;
		dfs(u);
		decompose(u , u);
	}
	
	void update(Long u, Long w) {
		st.update(pos[u] , w);
	}
	
	Long query(Long u , Long v) {	//O( O( data query) log N)
		Long ans = -1e18;
		

		while(head[u] != head[v]) {
			
			if(depth[head[u]] > depth[head[v]]) {
				swap(u , v);
			}
			
			Long curHeavyMax = st.query(pos[head[v]], pos[v]);
			ans = max(ans , curHeavyMax);
			
			v = parent[head[v]];
		}
		
		if(depth[u] > depth[v]) {
			swap(u , v);
		}

		u = heavy[u];

		//last heavy path
		Long lastMax = st.query(pos[u], pos[v]);
		ans = max(ans, lastMax);
		return ans;
	}
} G;

struct Edge{
	Long u,v,w;
	Edge() {
	}
	Edge(Long u, Long v, Long w) : u(u) , v(v), w(w){}
};

int main() {
/*
1
12
1 2 8
2 4 2
2 5 5
2 6 7
1 3 3
3 7 9
7 8 2
7 9 1
8 10 1
8 11 1
4 12 1
QUERY 2 4


*/
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	Long T;
	cin >> T;
	REP(test , T) {
		Long N;
		cin >> N;
		nTree = N;
		G.clear(N);
		vector<Edge> edge;
		REP(i , N - 1) {
			Long u,v,w;
			cin >> u >> v >> w;
			u--;
			v--;
			edge.pb(Edge(u, v ,w));
			G.addEdge(u,v);
		}
		
		G.decompose();
		st.setN(N);
		REP(i , edge.size()) {
			if(G.depth[edge[i].u] > G.depth[edge[i].v]) {
				G.update(edge[i].u , edge[i].w);
			}
			else{
				G.update(edge[i].v , edge[i].w);
			}
		}
		
		while(true) {
			string s;
			cin >> s;
			if(s[0] == 'D') {
				break;
			}
			if(s[0] == 'Q') {
				Long u,v;
				cin >>u >> v;
				u--;
				v--;
				cout << G.query(u,v) << '\n';
			} else{
				Long e , w;
				cin >> e >> w;
				e--;
				if(G.depth[edge[e].u] > G.depth[edge[e].v]) {
					G.update(edge[e].u , w);
				}
				else{
					G.update(edge[e].v , w);
				}
			}
		}
	}
	
	return 0;
}

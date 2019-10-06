#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 4e5;  

struct Edge{
	Long u, v;
	Edge(Long u , Long v) : u(u) , v(v){
	}
	Edge(){
	}
};

struct Graph {
	vector <Long> adj[MX];
	bool vis[MX];
	Long tIn[MX];//tiempo de entrada al nodo
	Long low[MX];//minimo tiempo al que puede ir ese nodo o uno de sus descendientes por medio de cualquier arista(tree o back edge) 
	Long timer = 0;
	vector<Edge> bridge;
	vector<Long> articulation;
	bool isArticulation[MX];
	unordered_map<Long,bool> isBridge[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			vis[i] = false;
			isArticulation[i] = false;
			isBridge[i].clear();
		}
		bridge.clear();
		articulation.clear();
		timer = 0;
	}
	
	void addEdge(Long u, Long v) {
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	void dfs(Long u, Long p = -1){ //O(N + M)
		vis[u] = true;
		tIn[u] = low[u] = timer++;
		Long children = 0;
		for(Long v : adj[u]) {
			if(v == p) continue;
			if(vis[v]) {
				low[u] = min(low[u] , tIn[v]);
			} else {
				dfs(v , u);
				low[u] = min(low[u] , low[v]);
				if(low[v] > tIn[u]) {
					bridge.pb(Edge(u , v));
					isBridge[min(u,v)][max(u,v)] = true;
				}
				if(low[v] >= tIn[u] && p != -1 && !isArticulation[u]) {
					articulation.pb(u);
					isArticulation[u] = true;
				}
				children++;
				if(p == -1 && children > 1){
					if(!isArticulation[u]){
						isArticulation[u] = true;
						articulation.push_back(u);
					}
				}
			}
		}
	}
	
	void calculate(Long n) { //O(N + M)
		for(Long i = 0; i < n; i++) {
			if(!vis[i]) {
				dfs(i);
			}
		}
	}
} G;

map<string , Long> vertex;
string name[MX];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Long N;
	cin >> N;
	Long T = 1;
	while(true){
		G.clear(N);
		vertex.clear();
		REP(i , N){
			string s;
			cin >> s;
			name[i] = s;
			vertex[s] = vertex.size() + 1;
		}
		Long M;
		cin >> M;
		REP(i , M){
			string a, b;
			cin >> a >> b;
			G.addEdge(vertex[a] , vertex[b]);
		}
		G.calculate(N);
		cout << "City map #" << T << ": " << G.articulation.size() << " camera(s) found" << "\n";
		vector<string> ans;
		REP(i , N){
			if(G.isArticulation[i]){
				ans.pb(name[i]);
			}
		}
		sort(ans.begin(), ans.end());
		REP(i , ans.size()){
			cout << ans[i] << "\n";
		}
		cin >> N;
		if(N == 0) break;
		cout << "\n";
		T++;
	}
	return 0;
}

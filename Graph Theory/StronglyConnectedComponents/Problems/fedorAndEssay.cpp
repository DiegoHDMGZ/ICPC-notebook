#include <bits/stdc++.h>
#define REP(i, n) for(Long i = 0; i < (Long) n; i++)
#define pb push_back
#define debug(x) cout << #x << " = " << x << endl;
 
using namespace std;
 
typedef long long Long;
 
const Long MX = 5e5;
 
//Una componente fuertemente conexa (SCC) es aquella en la que entre todo par de vertices u, v. u es alcanzable por v y viceversa
//Se puede condensar el grafo en sus componentes conexas. Este grafo es un DAG
 
//https://codeforces.com/contest/467/problem/D

Long cost[MX];
const Long INF = 1e18;
string word[MX];
 
Long cntR(string &s){
	Long ans = 0;
	REP(i , s.size()){
		if(s[i] == 'r'){
			ans++;
		}
	}
	return ans;
}
 
struct Graph {
	vector <Long> adj[MX];
	vector <Long> rev[MX];
	bool vis1[MX];
	bool vis2[MX];
	vector<Long> order,component;
	Long numComponent = 0;
	Long scc[MX];
	pair<Long,Long> costSCC[MX];
	map<Long , bool> added[MX];
	
	void clear(Long N = MX) {
		REP( i , N) {
			adj[i].clear();
			rev[i].clear();
			vis1[i] = vis2[i] = false;
			added[i].clear();
			costSCC[i] = {INF,INF};
		}
		order.clear();
		component.clear();
		numComponent = 0;
	}
	
	void addEdge(Long u, Long v) {
		if(added[u][v] ) return;
		if(u == v) return;
		added[u][v] = true;
		adj[u].pb(v);
		rev[v].pb(u);
	}
	
	void dfs1(Long u){ //O(N + M)
		vis1[u] = true;
		for(Long v : adj[u]) {
			if(!vis1[v]) {
				dfs1(v);
			}
		}
		order.pb(u);
	}
	
	void dfs2(Long u) { //O(N + M)
		vis2[u] = true;
		component.pb(u);
		for(Long v : rev[u]) {
			if(!vis2[v]) {
				dfs2(v);
			}
		}
	}
	
	void calculateSCC(Long N) { //O(N + M)
		REP(i, N){
			if(!vis1[i]) dfs1(i);
		}
		REP(i , N ) {
			Long u = order[N - 1 - i];
			if(!vis2[u]) {
				dfs2(u);
				
				for(Long v : component) {
					scc[v] = numComponent;
					costSCC[numComponent] = min(costSCC[numComponent] , {cntR(word[v]) , word[v].size()});
				}
				
				numComponent++;
				component.clear();
			}
		}
	}
} G;
 
 
 
struct CondensationGraph{
	pair<Long,Long> dp[MX];
	bool used[MX];
	vector<Long> adj[MX];
	map<Long, bool> added[MX];
	
	void addEdge(Long u , Long v){
		if(u == v) return;
		if(added[u][v] ) return;
		added[u][v] = added[v][u] = true;
		adj[u].pb(v);
	}
	
	pair<Long,Long> f(Long u){
		if(used[u]){
			return dp[u];
		}
		used[u] = true;
		dp[u] = G.costSCC[u];
		
		for(Long v : adj[u]){
			dp[u] = min(dp[u] , f(v));
		}
		return dp[u];
	}
}G2;
 
 
map<string, Long> node;
 
void toLower(string &s){
	REP(i , s.size()){
		s[i] = tolower(s[i]);
	}
}
 
string essay[MX];
 
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n, m;
	cin >> n;
	
	
	Long cnt = 1;
	REP(i , n){
		cin >> essay[i];
		toLower(essay[i]); 
		if(node[essay[i]] == 0){
			node[essay[i]] = cnt;
			word[cnt - 1] = essay[i];
			cnt++;
		}
	}
	cin >> m;
	G.clear(n + 2 * m);
	REP(i , m){
		string a , b;
		cin >> a >> b;
		toLower(a);
		toLower(b);
		if(node[a] == 0){
			node[a]= cnt;
			word[cnt - 1] = a;
			cnt++;
		}
		if(node[b] == 0){
			node[b] = cnt;
			word[cnt - 1] = b;
			cnt++;
		}
		G.addEdge(node[a] - 1 , node[b] - 1);
	}
	cnt--;
	G.calculateSCC(cnt);
	
	REP(u , cnt){
		for(Long v : G.adj[u]){
			G2.addEdge(G.scc[u] , G.scc[v]);
		}
	}
	
	pair<Long,Long> ans = {0,0};
	REP(i , n){
		Long u = node[essay[i]];
		ans.first += G2.f(G.scc[u - 1]).first;
		ans.second += G2.f(G.scc[u - 1]).second;
	}
	cout << ans.first << " " << ans.second << endl;
	
	return 0;
}

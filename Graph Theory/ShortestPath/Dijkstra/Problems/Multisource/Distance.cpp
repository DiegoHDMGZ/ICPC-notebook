#include <bits/stdc++.h>
#define fore(i,a,b) for(Long i=a,to=b;i<to;i++)
#define SZ(v) (int)v.size()
#define pb push_back
#define REP(i , n) for(Long i = 0; i < (Long) n ; i++)
#define debug(x) cout << #x << " = " << x << endl;
 
using namespace std;
 
typedef long long Long;

//https://codeforces.com/gym/100714
 
const Long MX = 3e5;
bool used[MX];
 
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
 
Long ans = INF;
 
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
	
	void dijkstra(vector<Long> &root, Long n){
		priority_queue<Path> q;
		for(Long u  : root){
			d[u] = 0;
			reachedBy[u] = u;
			q.push(Path(u, d[u] , u));
		}
		while(!q.empty()){
			Path p = q.top();
			q.pop();
			Long u = p.node;
		
			if(vis[u]) {
				continue;
			}
			
			vis[u] = true;
			for(Path x : adj[u]){
				Long v = x.node;
				//debug(v);
				if(p.ini != reachedBy[v]){
					ans = min(ans , 3 * (p.weight + x.weight + d[v]));
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
 
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long k, n , m;
	cin >> k >> n >> m;
	
	G.clear(n);
	vector<Long> contestant;
	
	bool zero = false;
	REP(i , k){
		Long x;
		cin >> x;
		x--;
		contestant.pb(x);
		if(used[x]) zero = true;
		used[x] = true;
	}
	
	REP(i , m){
		Long u , v , w;
		cin >> u >> v >> w;
		u--;
		v--;
		G.addEdge(u , v , w);
	}
	
	
	if(zero) {
		cout << 0 << endl;
		return 0;
	}
	G.dijkstra(contestant, n);
	cout << ans << endl;
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1498

const Long MX = 1e5;
const Long INF = 1e18;

struct EndPoint{
	Long node, weight;
	EndPoint(){}
	EndPoint(Long node, Long weight) : node(node) , weight(weight) {}
};

struct Graph{
	vector<EndPoint> adj[MX];
	vector<EndPoint> rev[MX];
	Long d[MX];
	bool cycle[MX];
	
	deque<Long> path;
	
	void clear(Long N = MX) {
		REP(i , N) {
			adj[i].clear();
			rev[i].clear();
			vis[i] = false;
		}
	}
	
	void addEdge(Long u, Long v, Long w) {
		adj[u].push_back(EndPoint(v, w));
		rev[v].push_back(EndPoint(u , w));
	}

	bool spfa(Long n, Long m, Long root = 0){ //O(nm)
		for(Long i = 0; i < n; i++){
			d[i] = INF;
			cycle[i] = false;
		}
		queue<Long> q;
		vector<bool> inQueue(n , false);
		vector<Long> cnt(n, 0);
		d[root] = -100;
		inQueue[root] = true;
		q.push(root);
		bool c = false;
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			inQueue[u] = false;
			if(cnt[u] == n){
				cycle[u] = true;
				c = true;
				continue;
			}
			cnt[u]++;
			for(EndPoint e : adj[u]){
				Long v = e.node;
				if(d[u] + e.weight < d[v] && d[u] < 0){
					d[v] = d[u] + e.weight;
					if(!inQueue[v]){
						q.push(v);
					}
					inQueue[v] = true;
				}
			}
		}
		return c;
	}
	
	
	bool vis[MX];
	bool reachCycle(Long u){
		if(cycle[u]) return true;
		vis[u] = true;
		for(auto e : rev[u]){
			Long v = e.node;
			if(!vis[v]){
				if(reachCycle(v)) return true;
			}
		}
		return false;
	}
} G;


Long energy[MX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	while(cin >> n){
		if(n == -1) break;
		G.clear(n);
		vector<pair<Long,Long>> edges;
		REP(u, n){
			cin >> energy[u];
			Long neigh;
			cin >> neigh;
			REP(i , neigh){
				Long v;
				cin >> v;
				v--;
				edges.pb({u , v});
			}
		}
		for(pair<Long,Long> e : edges){
			G.addEdge(e.first, e.second, -energy[e.second]);
		}
	
		if((G.spfa(n, edges.size()) && G.reachCycle( n - 1)) || G.d[n - 1] < 0){
			cout << "winnable\n";
		} else {
			cout << "hopeless\n";
		}
	}

	return 0;
}

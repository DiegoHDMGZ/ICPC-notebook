#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 3000;
const Long INF = 1e18;

//testing
struct Graph{
	vector<Long> adj[MX];
	Long cap[MX][MX]; 
	Long flow[MX][MX];
	bool vis[MX];
	bool added[MX][MX];
	Long parent[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			vis[i] = false;
			parent[i] = -1;
			for(Long j = 0; j < N; j++) {
				cap[i][j] = 0;
				flow[i][j] = 0;
				added[i][j] = false;
			}
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir ){
		if(!added[min(u, v)][max(u , v)]) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		added[min(u , v)][max(u , v)] = true;
		cap[u][v] += w;
		if(!dir){
			cap[v][u] += w;
		}
		
	}
	
	void transition(Long s , Long t, Long inc){
		Long cur = t;
		
		while(cur != s){
			Long prev = parent[cur];
			flow[prev][cur] += inc;
			flow[cur][prev] -= inc;
			cur = prev;
		}
	}
	
	Long bfs(Long s, Long t ){ //O(E)
		deque<pair<Long,Long> > q; //< node, capacity>
		q.push_back({s , INF});
		vis[s] = true;
		while(!q.empty()){
			Long u = q.front().first;
			Long c = q.front().second;
			q.pop_front();
			if(u == t){
				return c;
			}
			for(Long v : adj[u]){
				Long cf = cap[u][v] - flow[u][v];
				if(!vis[v] && cf > 0){
					parent[v] = u;
					vis[v] = true;
					Long x = min(c , cf);
					q.push_back({v , x});
				}
			}
		}
		return 0;
	}
	
	Long maxFlow(Long s, Long t , Long n){ //O(E * min(E * V , |F|))
		Long ans = 0;
		while(true){ //O( min (E * V , |F| ) ) iterations
			fill(vis, vis + n, false);
			fill(parent, parent + n, -1);
			Long inc = bfs(s, t);
			if(inc == 0) break;
			ans += inc;
			transition(s , t , inc);
		}
		return ans;
	}
	
} G;


Long color[MX];
bool colored[MX];
vector<Long> adjColor[MX];
map<Long, bool> used[MX];

void clear(Long n){
	REP(i , n){
		colored[i] = false;
		adjColor[i].clear();
		color[i] = 0;
		used[i].clear();
	}
}

void coloring(Long u, Long c){
	color[u] = c;
	colored[u] = true;
	for(Long v : adjColor[u]){
		if(!colored[v]){
			coloring(v , (c + 1) % 2);
		}
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	while(cin >> n){
		
		Long s = 0;
		Long t = n + 1;
		G.clear(t + 1);
		clear(t + 1);
		vector<pair<Long,Long> > lovers;
		REP(k , n){
			string str;
			cin >> str;
			Long u = 0;
			REP(x , (Long)str.size() - 1){
				u = u * 10 + (str[x] - '0');
			}
			u++;
			cin >> str;
			Long num = 0;
			for(Long x = 1; x + 1 < str.size(); x++){
				num = num * 10 + (str[x] - '0');
			}
			REP(i, num){
				Long v;
				cin >> v;
				v++;
				if(used[min(u,v)][max(u,v)]) continue;
				used[min(u,v)][max(u, v)]= true;
				adjColor[u].pb(v);
				adjColor[v].pb(u);
				lovers.pb({u,v});
			}
		}
		for(Long i = 1; i <= n; i++){
			if(!colored[i]){
				coloring(i , 0);
			}
		}
		
		for(Long u = 1; u <= n; u++){
			if(color[u] == 0){
				G.addEdge(s , u, 1 , true); 
			} else {
				G.addEdge(u , t , 1 , true);
			}
		}
		for(auto love : lovers){
			if(color[love.first] == 0){
				G.addEdge(love.first, love.second, 1 , true);
			} else {
				G.addEdge(love.second, love.first, 1 , true);
			}
		}
		cout << n - G.maxFlow(s , t, t + 1) << endl;
	}
	
	return 0;
}

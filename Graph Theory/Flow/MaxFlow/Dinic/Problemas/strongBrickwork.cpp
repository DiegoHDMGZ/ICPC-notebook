#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e4 + 3;
const Long MX2 = 200;
const Long INF = 1e18;
Long A[MX2][MX2];

struct Graph{
	vector<Long> adj[MX];
	map<Long,Long> cap[MX]; 
	map<Long,Long> flow[MX];
	map<Long,bool> added[MX];
	Long level[MX];
	Long nextEdge[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
			cap[i].clear();
			flow[i].clear();
			added[i].clear();
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir){
		//cout << u << " -> " << v << endl;
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
	
	Long dfs(Long u, Long t ,Long f){ 
		if(u == t) return f;
		
		for(Long &i = nextEdge[u]; i < adj[u].size(); i++){
			Long v = adj[u][i];
			Long cf = cap[u][v] - flow[u][v];
			if(cf == 0 || level[v] != level[u] + 1) continue;
			
			Long ret = dfs(v, t, min(f, cf) );
			
			if(ret > 0){
				flow[u][v] += ret;
				flow[v][u] -= ret;
				return ret;
			}
		}
		return 0;
	}
	
	bool bfs(Long s, Long t ){ //O(E)
		deque<Long> q; 
		q.push_back(s);
		level[s] = 0;
		while(!q.empty()){
			Long u = q.front();
			q.pop_front();
			REP(i , adj[u].size()){
				Long v = adj[u][i];
				Long cf = cap[u][v] - flow[u][v];
				if(level[v] == -1 && cf > 0){
					level[v] = level[u] + 1;
					q.push_back(v);
				}
			}
		}
		return level[t] != -1;
	}
	
	Long maxFlow(Long s, Long t, Long n){//General: O(E * V^2), Unit Cap: O(E * min(E^(1/2) , V^(2/3))), Unit Network: O(E * V^(1/2))
		//unit network is a network in which all the edges have unit capacity,
		//and for any vertex except s and t either incoming or outgoing edge is unique.
		Long ans = 0;
		while(true){ //O(V) iterations
			fill(level, level + n, -1);
			if(!bfs(s, t) ){
				break;
			}
			//after bfs, the graph is a DAG
			fill(nextEdge, nextEdge + n , 0);
			Long inc;
			do{
				inc = dfs(s , t , INF);
				ans += inc;
			} while (inc > 0);
		}
		return ans;
	}
} G;

vector<Long> adjColor[MX];
bool colored[MX];
Long color[MX];


Long ans[MX2][MX2];

void coloring(Long u, Long c){
	color[u] = c;
	colored[u] = true;
	REP(i , adjColor[u].size()){
		Long v = adjColor[u][i];
		if(!colored[v]){
			coloring(v , (c + 1) % 2);
		}
	}
}

Long n, m;
bool valid(Long x, Long y){
	return x >= 0 && x < n && y >= 0 && y < m;
}

void addEdge(Long u , Long v){
	adjColor[u].pb(v);
}

Long conv(Long i, Long j){
	return i * m + j + 1;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	

	cin >> n >> m;
	REP(i , n){
		REP(j , m){
			cin >> A[i][j];
		}
	}
	Long s = 0;
	Long t = n * m + 1;
	vector<pair<Long, Long> > edge;
	REP(i , n){
		REP(j , m){
			for(Long a = -1; a <= 1; a++){
				for(Long b = -1; b <= 1; b++){
					if(valid(a + i, b + j) && abs(a) + abs(b) == 1 && A[a + i][b + j] != A[i][j]){
						addEdge(conv(i , j ) , conv(i + a , b + j)); 
						edge.pb({conv(i , j ) , conv(i + a , b + j)});
					}
				}
			}
		}
	}
	for(Long i = 1; i <= n * m; i++){
		if(!colored[i]){
			coloring(i , 0);
		}
	}
	for(Long i = 1; i <= n * m; i++){
		if(color[i] == 0){
			G.addEdge(s , i, 1 , true);
		} else {
			G.addEdge(i , t , 1 , true);
		}
	}
	REP(i , edge.size()){
		pair<Long,Long> p = edge[i];
		assert(color[p.first] != color[p.second]);
		if(color[p.first] == 0){
			G.addEdge(p.first, p.second , 1 , true);
		}
	}
	Long aux = G.maxFlow(s , t , t + 1);
	if(aux != n * m / 2){
		cout << -1 << endl;
	} else {
		Long ind = 1;
		REP(i , n){
			REP(j , m){
				if(ans[i][j] != 0) continue;
				bool ok = false;
				for(Long a = -1; a <= 1; a++){
					if(ok) break;
					for(Long b = -1; b <= 1; b++){
						if(valid(a + i, b + j) && abs(a) + abs(b) == 1 && A[a + i][b + j] != A[i][j]){
							if(G.flow[conv(i , j)][conv(i + a , b + j)] == 1){
								ans[i][j] = ind;
								ans[i + a][b + j] = ind;
								ind++;
								ok = true;
								break;
							}
						}
					}
				}
			}
		}
		REP(i , n){
			REP(j , m){
				cout <<ans[i][j] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}

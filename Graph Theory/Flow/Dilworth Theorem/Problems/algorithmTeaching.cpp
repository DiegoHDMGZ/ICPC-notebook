#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef int Long;

//https://codeforces.com/gym/102428

const Long MX = 2 * (1e5 + 3000);
const Long INF = 1e9;

struct Edge{
	Long to, cap, flow;
	Edge *rev;
	Edge(): rev(NULL) {}
	Edge(Long to, Long cap) : to(to), cap(cap), flow(0), rev(NULL) {}
};

struct GraphFlow{
	vector<Edge*> adj[MX];
	Long level[MX];
	Long nextEdge[MX];
	
	void clear(Long N = MX){
		for(Long i = 0 ; i < N; i++){
			adj[i].clear();
			level[i] = -1;
			nextEdge[i] = 0;
		}
	}
	
	void addEdge(Long u, Long v, Long w, bool dir){
		Edge *forward = new Edge(v , w);
		Edge *backward = new Edge(u , 0);
		forward->rev = backward;
		backward->rev = forward;

		adj[u].pb(forward);
		adj[v].pb(backward);

		if(!dir){
			forward = new Edge(u , w);
			backward = new Edge(v , 0);
			forward->rev = backward;
			backward->rev = forward;
			adj[v].pb(forward);
			adj[u].pb(backward);
		}
	}
	
	Long dfs(Long u, Long t ,Long f){ 
		if(u == t) return f;
		for(Long &i = nextEdge[u]; i < adj[u].size(); i++){
			Edge *e = adj[u][i];
			Long v = e->to;
			Long cf = e->cap - e->flow;
			if(cf == 0 || level[v] != level[u] + 1) continue;
			
			Long ret = dfs(v, t, min(f, cf) );
			if(ret > 0){
				e->flow += ret;
				e->rev->flow -= ret;
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
			for(Edge *e: adj[u]){
				Long v = e->to;
				Long cf = e->cap - e->flow;
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
} GFlow;

map<string , Long> id; 
map<vector<Long>, Long> node;

Long getBit(Long mask, Long i){
	return (mask >> i) & 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n;
	cin >> n;
	Long c = 0;
	Long nodes = 0;
	vector< pair<Long,Long> > edges;
	REP(it , n){
		Long K;
		cin >> K;
		vector<Long> A;
		REP(k , K){
			string s;
			cin >> s;
			if(id.find(s) == id.end()){
				id[s] = c++;
			}
			A.pb(id[s]);
		}

		sort(A.begin(), A.end());
		Long sz = A.size();
		for(Long mask = 1; mask < (1 << sz); mask++){
			vector<Long> subsetU;
			for(Long i = 0; i < sz; i++){
				if(getBit(mask , i) == 1){
					subsetU.pb(A[i]);
				}
			}
			
			if(node.find(subsetU) == node.end()){
				node[subsetU] = nodes++;
			}
			
			Long u = node[subsetU];
			for(Long mask2 = mask; mask2 > 0; mask2 = (mask2 - 1) & mask){
				if(mask2 == mask) continue;
				vector<Long> subsetV;
				for(Long i = 0; i < sz; i++){
					if(getBit(mask2 , i) == 1){
						subsetV.pb(A[i]);
					}
				}
				if(node.find(subsetV) == node.end()){
					node[subsetV] = nodes++;
				}
				Long v = node[subsetV];

				edges.pb({u,v});
			}
		}
	}
	Long s = 0;
	Long t = 2 * nodes + 1;
	for(Long i = 0; i < nodes; i++){
		GFlow.addEdge(s , i + 1 , 1 , true);
		GFlow.addEdge(i + 1 + nodes , t , 1 , true);
	}
	for(pair<Long,Long> e : edges){
		GFlow.addEdge(e.first + 1 , e.second + 1 + nodes, 1 , true);
	}
	cout << nodes - GFlow.maxFlow(s , t, t + 1) << endl;
	return 0;
}

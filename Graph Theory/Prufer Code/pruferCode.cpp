#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://cp-algorithms.com/graph/pruefer_code.html


struct Graph{
	vector<vector<Long>> adj;
	vector<Long> parent;
	
	Graph(Long n){
		adj = vector<vector<Long>>(n , vector<Long>(0));
		parent = vector<Long>(n , -1);
	}
	
	void addEdge(Long u , Long v){
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(Long u, Long p = -1){
		parent[u] = p;
		for(Long v : adj[u]){
			if(v == p) continue;
			dfs(v, p);
		}
	}
};

vector<Long> prufer(Graph &G){
	Long n = G.adj.size();
	G.dfs(n - 1);
	
	Long ptr = -1;
	vector<Long> degree(n);
	
	for(Long i = 0; i < n; i++){
		degree[i] = G.adj[i].size();
		if(degree[i] == 1 && ptr == -1){
			ptr = i;
		}
	}
	
	vector<Long> code(n - 2);
	Long leaf = ptr;
	for(Long i = 0; i < n - 2; i++){
		Long next = G.parent[leaf];
		code[i] = next;
		degree[next]--;
		if(degree[next] == 1 && next < ptr){
			leaf = next;
		} else {
			//search
			ptr++;
			while(degree[ptr] != 1){
				ptr++;
			}
			leaf = ptr;
		}
	}
	return code;
}

struct Edge{
	Long u , v;
	Edge(){}
	Edge(Long u , Long v) : u(u), v(v){}
};

vector<Edge> getTree(vector<Long> &code){
	Long n = code.size() + 2;
	vector<Long> degree(n , 1);
	for(Long u : code){
		degree[u]++;
	}
	Long ptr = 0;
	while(degree[ptr] != 1){
		ptr++;
	}
	Long leaf = ptr;
	
	vector<Edge> tree;
	for(Long u : code){
		tree.push_back(Edge(leaf , u));
		degree[u]--;
		if(degree[u] == 1 && u < ptr){
			leaf = u;
		} else {
			ptr++;
			while(degree[ptr] != 1){
				ptr++;
			}
			leaf = ptr;
		}
	}
	tree.push_back(Edge(leaf , n - 1));
	return tree;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

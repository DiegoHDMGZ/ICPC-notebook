#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//code : http://e-maxx.ru/algo/matching_edmonds
//theory : https://math.mit.edu/~goemans/18438F09/lec2.pdf

const Long MX = 1e5;
struct Graph{
	vector<Long> adj[MX];
	Long p[MX];
	Long match[MX];
	Long base[MX]; //base of the flower
	bool used[MX];
	bool blossom[MX];
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
		}
	}
	
	void addEdge(Long u , Long v){
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	Long lca(Long u , Long v , Long n){ //O(n)
		vector<bool> marked(n);
		while(true){
			u = base[u]; //blossom compression
			marked[u] = true;
			if(match[u] == -1){
				//we reach the root : unexposed vertex
				break;
			}
			u = p[match[u]];
		}
		while(true){
			v = base[v];
			if(marked[v]){
				return v;
			}
			v = p[match[v]];
		}
		return -1;
	}
	
	void markPath(Long u, Long b, Long children){
		while(base[u] != b){
			blossom[base[u]] = blossom[base[match[u]]] = true;
			p[u] = children;
			children = match[u];
			u = p[match[u]];
		}
	}
	
	void compress(Long u, Long v, Long n, queue<Long> &q){
		Long curBase = lca(u , v, n); //base of the flower
		assert(curBase != -1);
		fill(blossom, blossom + n , false);

		markPath(u , curBase, v);
		markPath(v , curBase , u);
		for(int i = 0; i < n; i++){
			if(blossom[base[i]]){
				base[i] = curBase;
				if(!used[i]){
					used[i] = true;
					q.push(i);
				}
			}
		}
	}
	
	Long findPath(Long root, Long n){
		for(Long i = 0; i < n; i++){
			base[i] = i;
			used[i] = false;
			p[i] = -1;
		}
		used[root] = true;
		queue<Long> q;
		q.push(root);
		while(!q.empty()){
			Long u = q.front();
			q.pop();
			for(Long to : adj[u]){
				if(base[u] == base[to] || match[u] == to){
					continue;
				}
				if(to == root || (match[to] != -1 && p[match[to]] != -1)){
					//we find a blossom
					compress(u , to, n , q);
				} else if(p[to] == -1){
					//augmenting path or continue bfs
					p[to] = u;
					if(match[to] == -1){
						//we find an augmenting path
						return to;
					}
					//we continue the bfs
					to = match[to];
					used[to] = true;
					q.push(to);
				}
			}
		}
		return -1;
	}
	
	Long maxMatching(Long n){ //O(n^3)
		fill(match, match + n , -1);
		Long ans = 0;
		for(Long u = 0; u < n; u++){
			if(match[u] == -1){
				Long v = findPath(u, n);
				if(v != -1){
					ans++;
					while(v != -1){
						Long nextVertex = match[p[v]];
						match[v] = p[v];
						match[p[v]] = v;
						v = nextVertex;
					}
				}
			}
		}
		return ans;
	}
}G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	return 0;
}

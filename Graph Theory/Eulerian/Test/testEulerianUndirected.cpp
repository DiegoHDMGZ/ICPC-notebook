#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

struct Graph{
	vector<Long> adj[MX];
	vector<pair<Long,Long>> edges;

	void clear(Long n){
		edges.clear();
		REP(i , n){
			adj[i].clear();
		}
	}
	void addEdge(Long u , Long v){
		adj[u].push_back(v);
		adj[v].push_back(u);
		edges.push_back({u, v});
	}

	vector<Long> hierholzer(Long n, Long start = 0){
		vector<vector<pair<Long,Long>>> endpoint(n);
		for(Long i = 0; i < edges.size(); i++){
			auto e = edges[i];
			Long u = e.first;
			Long v = e.second;
			endpoint[u].push_back({v , i});
			endpoint[v].push_back({u, i});
		}

		vector<bool> used(edges.size(), false);
		vector<Long> curPath = {start};
		vector<Long> path;
		
		while(!curPath.empty()){
			Long u = curPath.back();
			while(!endpoint[u].empty() && used[endpoint[u].back().second]){
				endpoint[u].pop_back();
			}
			if(endpoint[u].empty()){
				path.push_back(curPath.back());
				curPath.pop_back();
			} else{
				Long v = endpoint[u].back().first;
				curPath.push_back(v);
				used[endpoint[u].back().second] = true;
				endpoint[u].pop_back();
			}
		}
		return path;
	}

	vector<Long> getEulerianCycle(Long n){
		//it has to be connected (or strongly connected)
		//undirected -> all vertices have to have even degree
		//directed -> in all vertices indegree = outdegree
		for(Long u = 0; u < n; u++){
			assert((adj[u].size() & 1)== 0);
		}
		return hierholzer(n);
	}

	vector<Long> getEulerianPath(Long n){
		//it has to be connected (or strongly connected)
		//undirected -> there has to be exactle 2 nodes with odd degree
		//directed -> in all vertices indegree = outdegree 
		//except for two vertices. 
		//The first with outdegree - indegree = 1
		//The last with indegree - outdegree = 1
		vector<Long> odd;
		for(Long u = 0; u < n; u++){
			if((adj[u].size() & 1) == 1){
				odd.push_back(u);
			}
		}
		assert(odd.size() == 2);
		vector<Long> path = hierholzer(n , odd[0]);
		return path;
	}

	map<Long, Long> cnt[MX];
	bool checkEulerPath(vector<Long> &path, Long n){
		REP(i , n){
			cnt[i].clear();
		}
		for(auto e : edges){
			cnt[e.first][e.second]++;
			cnt[e.second][e.first]++;
		}
		for(Long i = 0; i + 1 < path.size(); i++){
			if(cnt[path[i]][path[i + 1]] == 0) return false;
			cnt[path[i]][path[i + 1]]--;
			cnt[path[i + 1]][path[i]]--;
		}
		REP(i , n){
			for(pair<Long,Long> c : cnt[i]){
				if(c.second != 0) return false;
			}
		}
		
		return true;
		
	}

	bool checkEulerCycle(vector<Long> &cycle, Long n){
		return checkEulerPath(cycle, n) && cycle[0] == cycle.back();
	}

	bool testRandom(bool isCycle){
		Long n = random(10, 50);
		clear(n);
		
		Long minEdges = random(n, n * n );
		vector<bool> picked(n, false); 
		Long first = random(0 , n - 1);
		Long u = first;
		picked[u] = true;
		while(edges.size() < minEdges){
			Long v = random(0 , n - 1);
			while(v == u){
				v = random(0 , n - 1);
			}
			addEdge(u , v);
			picked[v] = true;
			u = v;
		}
		for(Long i = 0; i < n; i++){
			if(!picked[i]){
				addEdge(u , i);
				u = i;
			}
		}
		if(isCycle && u != first){
			addEdge(u , first);
		}
		if(!isCycle && u == first){
			Long v = random(0 , n - 1);
			while(v == u) v = random(0 , n - 1);
			addEdge(u , v);
		}
		shuffle(edges.begin(), edges.end(), rng);

		if(isCycle){
			auto cycle = getEulerianCycle(n);
			return checkEulerCycle(cycle, n);
		}
		else {
			auto path = getEulerianPath(n);
			return checkEulerPath(path, n);
		}
	}
}G;

/*
5 6
1 2
2 5
5 1
2 3
3 4
4 2

5 6
4 2
3 4
2 3
5 1
2 5
1 2
*/

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Long T = 1000;
	REP(t, T){
		assert(G.testRandom(random(0 , 1)));
	}
	return 0;
}

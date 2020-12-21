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
	Long indegree[MX];
	Long outdegree[MX];
	vector<pair<Long,Long>> edges;

	void clear(Long n){
		edges.clear();
		REP(i , n){
			indegree[i] = outdegree[i] = 0;
		}
	}
	void addEdge(Long u , Long v){
		indegree[v]++;
		outdegree[u]++;
		edges.push_back({u, v});
	}

	vector<Long> hierholzer(Long n, Long start = 0){
		vector<vector<Long>> endpoint(n);
		for(Long i = 0; i < edges.size(); i++){
			auto e = edges[i];
			Long u = e.first;
			Long v = e.second;
			endpoint[u].push_back(v);
		}

		vector<Long> curPath = {start};
		vector<Long> path;
		
		while(!curPath.empty()){
			Long u = curPath.back();
			if(endpoint[u].empty()){
				path.push_back(curPath.back());
				curPath.pop_back();
			} else{
				Long v = endpoint[u].back();
				curPath.push_back(v);
				endpoint[u].pop_back();
			}
		}
		reverse(path.begin(), path.end());
		return path;
	}

	vector<Long> getEulerianCycle(Long n){
		//it has to be strongly connected
		//in all vertices, indegree = outdegree
		for(Long u = 0; u < n; u++){
			assert(indegree[u] == outdegree[u]);
		}
		return hierholzer(n);
	}

	vector<Long> getEulerianPath(Long n){
		//it has to be strongly connected
		//in all vertices, indegree = outdegree except for two vertices. 
		//The first with outdegree - indegree = 1
		//The last with indegree - outdegree = 1
		Long first = -1;
		Long last = -1;
		for(Long u = 0; u < n; u++){
			assert(abs(outdegree[u] - indegree[u]) <= 2);
			if(outdegree[u] - indegree[u] == 1){
				assert(first == -1);
				first = u;
			}
			if(indegree[u] - outdegree[u] == 1){
				assert(last == -1);
				last = u;
			}
		}

		vector<Long> path = hierholzer(n , first);
		assert(path.back() == last);
		return path;
	}

	map<Long, Long> cnt[MX];
	bool checkEulerPath(vector<Long> &path, Long n){
		REP(i , n){
			cnt[i].clear();
		}
		for(auto e : edges){
			cnt[e.first][e.second]++;
		}
		for(Long i = 0; i + 1 < path.size(); i++){
			if(cnt[path[i]][path[i + 1]] == 0) return false;
			cnt[path[i]][path[i + 1]]--;
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
		Long n = random(70, 80);
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
		//shuffle(edges.begin(), edges.end(), rng);
		/*debug(n);
		debug(first + 1);
		debug(isCycle);
		cout << "edges = " << endl;
		for(Long i = 0; i < edges.size(); i++){
			cout << edges[i].first + 1 << " " << edges[i].second + 1 << endl;
		}
		cout << endl;*/
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Long T = 100;
	REP(t, T){
		assert(G.testRandom(random(0 , 1)));
	}
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//http://www.math.caltech.edu/~2014-15/1term/ma006a/class8.pdf

const Long MX = 1e5;

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
}G;

int main() {
    return 0;
}

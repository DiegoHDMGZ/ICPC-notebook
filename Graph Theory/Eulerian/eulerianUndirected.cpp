#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//http://www.math.caltech.edu/~2014-15/1term/ma006a/class8.pdf

const Long MX = 1e5;

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
        reverse(path.begin(), path.end());
        return path;
    }
    
    vector<Long> getEulerianCycle(Long n){
        //it has to be connected 
        //all vertices have to have even degree
        for(Long u = 0; u < n; u++){
			if((adj[u].size() & 1) != 0) {
				return {}; //no cycle
			}
        }
        return hierholzer(n);
    }
    
	vector<Long> getEulerianPath(Long n){
		//it has to be connected 
        //there has to be exactly 2 nodes with odd degree
        vector<Long> odd;
        for(Long u = 0; u < n; u++){
            if((adj[u].size() & 1) == 1){
                odd.push_back(u);
            }
        }
        if(odd.size() != 2) return {}; //no path
        
        vector<Long> path = hierholzer(n , odd[0]);
        return path;
	}
}G;

int main() {
    return 0;
}

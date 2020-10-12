#include <bits/stdc++.h>
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//https://codeforces.com/blog/entry/43230
//First run dfs and calculate tIn and tOut of each node
//If we have a query(u , v)
//Let's assume tIn[u] <= tIn[v]
//Case 1 : lca(u, v) == u , then use the range [tIn[u] , tIn[v]]
//Case 2 : use the range [tOut[u] , tIn[v]] U [tIn[lca(u , v)] , tIn[lca(u,v]]
//When answering the queries in this range, 
//only counts the elements that appears once

const Long MX = 1e5;
const Long block = 400;

const Long loga = 32 - __builtin_clz(MX);

struct SparseTable{
	pair<Long,Long> st[2 * MX][loga + 1]; //<min height , node>
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return min(a , b);
	}
	
	void build(vector<pair<Long,Long>> &A){ // O(n log n)
		Long n = A.size();
		for(Long i = 0; i < n; i++){
			st[i][0] = A[i];
		}
		
		for(Long j = 1; (1 << j) <= n; j++){
			for(Long i = 0; i + (1 << j) <= n; i++){
				st[i][j] = f(st[i][j-1], st[i + (1 << (j-1))][j-1]);
			}
		}
	}
	
	Long query(Long L, Long R){ //O(1)
		Long T = R - L + 1;
		Long lg = 31 - (__builtin_clz(T));
		return f(st[L][lg], st[R- (1LL << lg) + 1][lg]).second;
	}
	
}st;



struct Graph {
	vector<Long> adj[MX];
	vector<pair<Long,Long>> euler;
	Long first[MX];
	Long height[MX];
	Long node[2 * MX];
	Long tIn[MX];
	Long tOut[MX];
	
	Long timer = 0;
	
	void clear(Long n){
		for(Long i = 0; i < n; i++){
			adj[i].clear();
		}
		euler.clear();
		timer = 0;
	}
	
	void addEdge(Long u , Long v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(Long u = 0, Long p = -1){ //O(n+m)
		node[timer] = u;
		tIn[u] = timer++;
		first[u] = euler.size();
		euler.push_back({height[u], u });
		for ( Long v : adj[u] ) {
			if(p != v){
				height[v] = height[u] + 1;
				dfs(v , u);
				euler.push_back({height[u], u});
			}
		}
		node[timer] = u;
		tOut[u] = timer++;
	}

	void precalculate( Long root = 0){ //O(nlogn)
		height[root] = 0;
		dfs(root);
		st.build(euler);
	}
	
	Long lca(Long u, Long v){ //O(1)
		return st.query(min(first[u] , first[v]) , max(first[u] , first[v]));
	}
} G;

struct Query{
	Long id, l , r, lca ;
	Query(){}
	Query(Long id, Long l, Long r, Long lca): id(id), l(l) , r(r),  lca(lca){}
};

bool cmp(const Query &x, const Query &y){
	// queries are sorted in increasing order blocks 
	Long bx = x.l / block ;
	Long by = y.l / block;
	if (bx != by) return bx < by;
	
	//in the same blocks, if the block is odd sort in ascending order
	//otherwise, in descending order, in order to be more efficient
	if(bx & 1 == 1){
		return x.r < y.r;
	} else{
		return x.r > y.r;
	}
}

struct Mo{
	vector<Query> q;
	Long answer[MX];
	Long A[MX];
	bool activated[MX];
	
	void clear(Long n){
		q.clear();
		fill(activated, activated + 2 * n, false);
	}

	void addQuery(Long u , Long v) {
		Long id = q.size();
		Long lca = G.lca(u , v);
		if(G.tIn[u] > G.tIn[v]){
			swap(u , v);
		}
		if(u == lca){
			q.push_back( Query(id , G.tIn[u] , G.tIn[v] , lca));
		}else{
			q.push_back( Query(id ,G.tOut[u] , G.tIn[v], lca));
		}
	}
	
	void add(Long x, Long &ans){
		ans += A[x];
	}
	
	void remove(Long x, Long &ans){
		ans -= A[x];
	}
	
	void change(Long pos, Long &ans){
		Long u = G.node[pos];
		activated[u] ^= 1;
		if(activated[u]){
			add(u , ans);
		}else{
			remove(u , ans );
		}
	}
	
	void process(Long N) { //O((N + Q) sqrt(N) |F|)
	    sort(q.begin() , q.end(), cmp);
	    
	    Long currL = 0, currR = 0;
	    Long ans = 0;
		Long sz = q.size();
		
	    REP(i, sz) {
	        // L and R values of current range
	        Long l = q[i].l, r = q[i].r;
			while(currR <= r){//f(l , r + 1)
				change(currR, ans);
				currR++;
			}
			while(currL > l){ //f(l - 1 , r)
				currL--;
				change(currL , ans);
			}
			while(currL < l){ // f(l + 1 , r)
				change(currL , ans);
				currL++;
			}
			while(currR > r + 1){ //f(l , r - 1)
				currR--;
				change(currR , ans);
			}
			Long u = G.node[l];
	        Long v = G.node[r];
	        if(q[i].lca != u && q[i].lca != v){
				//Case 2
				change(G.tIn[q[i].lca], ans );
			}
			answer[q[i].id] = ans;
			if(q[i].lca != u && q[i].lca != v){
				//Case 2
				change(G.tIn[q[i].lca], ans );
			}
	    }
	}
	
	Long query(Long id){
		return answer[id];
	}
	
}mo;
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    return 0;
}

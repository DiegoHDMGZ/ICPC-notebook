#include <bits/stdc++.h>
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//https://codeforces.com/blog/entry/43230
//First run dfs and calculate tIn and tOut of each node
//If we have a query(u , v)
//Let's assume tIn[u] <= tIn[v]
//Case 1 : lca(u, v) == u , then use the range [tIn[u] , tIn[v]]
//Case 2 : use the range [tOut[u] , tIn[v]] U {tIn[lca(u , v)}
//Take care of repeated elements in the range !
//only counts the elements that appears once (ignore the others)

const Long MX = 1e5;
const Long SZ_BLOCK = 400; //Aprox sqrt(N) or N / sqrt(Q)

const Long loga = 32 - __builtin_clz(MX);

struct SparseTable{
	pair<Long, Long> st[2 * MX][loga + 1]; //<min height , node>
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b) {
		return min(a , b);
	}
	
	void build(vector<pair<Long,Long>> &A) { // O(n log n)
		Long n = A.size();
		for (Long i = 0; i < n; i++) {
			st[i][0] = A[i];
		}
		for (Long j = 1; (1 << j) <= n; j++) {
			for (Long i = 0; i + (1 << j) <= n; i++) {
				st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	
	Long query(Long L, Long R) { //O(1)
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
	Long timer;
	
	void clear(Long n) {
		for (Long i = 0; i < n; i++) {
			adj[i].clear();
		}
	}
	
	void addEdge(Long u , Long v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(Long u = 0, Long p = -1) { //O(n)
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

	void precalculate(Long root = 0) { //O(n logn)
		height[root] = 0;
		timer = 0;
		euler.clear();
		dfs(root);
		st.build(euler);
	}
	
	Long lca(Long u, Long v) { //O(1)
		return st.query(min(first[u] , first[v]) , max(first[u] , first[v]));
	}
} G;

struct Query{
	Long id, l , r, lca ;
	Query(){}
	Query(Long id, Long u , Long v) {
		this->id = id;
		lca = G.lca(u , v);
		if (G.tIn[u] > G.tIn[v]) {
			swap(u , v);
		}
		if (u == lca) {
			l = G.tIn[u];
			r = G.tIn[v];
		} else {
			l = G.tOut[u];
			r = G.tIn[v];
		}
	}
	
	bool operator <(const Query &other) const {
		//queries are sorted in increasing order of the block of l
		Long curBlock = l / SZ_BLOCK ;
		Long otherBlock = other.l / SZ_BLOCK;
		if (curBlock != otherBlock) return curBlock < otherBlock;
		
		//If queries are in the same blocks
		//if the block is odd, sort in increasing order of r
		//otherwise, in decreasing order of r
		if (curBlock & 1 == 1) {
			return r < other.r;
		} else{
			return r > other.r;
		}
	}
};

struct Mo{
	bool activated[MX];

	void add(Long val, Long &ans) {
		ans += val;
	}

	void remove(Long val, Long &ans) {
		ans -= val;
	}

	void change(Long pos, Long &ans, vector<Long> &A) {
		Long u = G.node[pos];
		activated[u] ^= 1;
		if(activated[u]){
			add(A[u] , ans);
		}else{
			remove(A[u] , ans );
		}
	}

	vector<Long> process(vector<Long> &A, vector<Query> &queries) { //O(N sqrt(Q) |F|)
		int n = A.size();
		fill(activated, activated + n, false);
		sort(queries.begin() , queries.end());
		Long curL = 0, curR = 0;
		Long acum = 0;
		vector<Long> answer(queries.size());
		for (int i = 0; i < queries.size(); i++) {
			Long l = queries[i].l;
			Long r = queries[i].r;
			while (curR <= r) {//f(l , r + 1)
				change(curR, acum, A);
				curR++;
			}
			while (curL > l) { //f(l - 1 , r)
				curL--;
				change(curL , acum, A);
			}
			while (curL < l) { // f(l + 1 , r)
				change(curL , acum, A);
				curL++;
			}
			while (curR > r + 1) { //f(l , r - 1)
				curR--;
				change(curR , acum, A);
			}
			Long u = G.node[l];
			Long v = G.node[r];
			if (queries[i].lca != u && queries[i].lca != v) {
				//Case 2
				change(G.tIn[queries[i].lca], acum, A);
			}
			answer[queries[i].id] = acum;
			if (queries[i].lca != u && queries[i].lca != v) {
				//Case 2
				change(G.tIn[queries[i].lca], acum, A);
			}
		}
		return answer;
	}
}mo;
 
int main(){
    return 0;
}

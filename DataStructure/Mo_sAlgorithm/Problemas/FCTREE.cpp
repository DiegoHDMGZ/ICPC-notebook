#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef int Long;

//https://www.codechef.com/problems/FCTRE

const Long MXVAL = 1e6 + 5;
bool isPrime[MXVAL];
Long fact[MXVAL];
vector<Long> primes;

void extSieve(){ //O(MX)
	//x = i * p. p is the smallest prime factor
	fill(isPrime, isPrime + MXVAL , true);
	isPrime[1] = false;
	for(Long i = 2; i  < MXVAL; i++){
		if(isPrime[i]) {
			primes.pb(i);
			fact[i] = i;
		}
		for(Long j = 0 ; j < primes.size() && i * primes[j] < MXVAL; j++){
			isPrime[i * primes[j]] = false;
			fact[i * primes[j]] = primes[j];
			if(i % primes[j] == 0) {
				break;
			}
		}
	}
}

struct Factor{
	Long base,exp;
	Factor(){
	}
	Factor(Long b, Long e){
		base = b;
		exp = e;
	}
};

vector<Factor> factorize(Long x){ //O(log x)
	vector<Factor> factors;
	while(x > 1){
		Long f = fact[x];
		Long exp = 0;
		while(x % f == 0){
			x /= f;
			exp++;
		}
		factors.push_back(Factor(f,exp));
	}
	return factors;
}

const Long MOD = 1e9 + 7;

Long mult(Long a, Long b){
	return ((long long)a * b )% MOD;
}

Long fastPow(Long a, Long b ){ //O(logb)
	Long ans = 1;
	while(b > 0){
		if(b & 1 == 1){ //b % 2 == 1
			ans = mult(ans ,a );
		}
		a = mult(a , a  );
		b >>= 1; //b /= 2;
	}
	return ans;
}
Long modInverse(Long a){
	return fastPow(a, MOD - 2);
}

Long inv[MXVAL];

Long division(Long a, Long b){
	return mult(a, inv[b]);
}

const Long MX = 1e5 + 2;
const Long loga = 32 - __builtin_clz(MX);

struct SparseTable{
	pair<Long,Long> st[2 * MX][loga + 1]; //<min height , node>
	
	pair<Long,Long> f(pair<Long,Long> a, pair<Long,Long> b){
		return min(a , b);
	}

	pair<Long,Long> f(pair<Long,Long> a){
		return a;
	}
	
	void build(vector<pair<Long,Long>> &A){ // O(n log n)
		Long n = A.size();
		for(Long i = 0; i < n; i++){
			st[i][0] = f(A[i]);
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

Long node[2 * MX];
Long tIn[MX];
Long tOut[MX];

struct Graph {
	vector<Long> adj[MX];
	vector<pair<Long,Long>> euler;
	Long first[MX];
	Long height[MX];
	
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
	Query(Long id, Long l, Long r, Long lca): id(id), l(l) , r(r),  lca(lca){}
};

const Long block = 400;

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


vector<Factor> factors[MX];

struct Mo{
	vector<Query> q;
	Long answer[MX];
	Long frequency[MXVAL];
	bool activated[MX];
	
	void clear(Long n){
		q.clear();
		for(int p : primes){
			frequency[p] = 1;
		}
		fill(activated, activated + 2 * n, false);
	}

	void addQuery(Long u , Long v) {
		Long id = q.size();
		Long lca = G.lca(u , v);
		if(tIn[u] > tIn[v]){
			swap(u , v);
		}
		if(u == lca){
			q.push_back( Query(id ,tIn[u] , tIn[v] , lca));
		}else{
			q.push_back( Query(id ,tOut[u] , tIn[v], lca));
		}
	}
	
	void processNode(Long u , Long &ans, Long op, bool update = true){
		for(Factor f: factors[u]){
			if(op == 1){
				ans = mult(ans , division(frequency[f.base] + f.exp , frequency[f.base]));
			}else{
				ans = mult(ans , division(frequency[f.base] - f.exp , frequency[f.base]));
			}
			
			if(update){
				if(op == 1){
					frequency[f.base] = frequency[f.base] + f.exp;
				}else{
					frequency[f.base] = frequency[f.base] - f.exp;
				}
			}	
		}
	}
	
	void change(Long pos, Long &ans){
		Long u = node[pos];
		activated[u] ^= 1;
		if(activated[u]){
			processNode(u , ans , 1);
		}else{
			processNode(u , ans , -1);
		}
	}
	
	
	void process(Long N) { //O((N + Q) sqrt(N) |F|)
	    sort(q.begin() , q.end(), cmp);
	    
	    Long currL = 0, currR = 0;
	    Long ans = 1;
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
			Long u = node[l];
	        Long v = node[r];
	        if(q[i].lca != u && q[i].lca != v){
				//Case 2
				change(tIn[q[i].lca], ans );
			}
			answer[q[i].id] = ans;
			if(q[i].lca != u && q[i].lca != v){
				//Case 2
				change(tIn[q[i].lca], ans );
			}
	    }
	}
	
	Long query(Long id){
		return answer[id];
	}
	
}mo;

void solve(){
	Long n;
	cin >> n;
	G.clear(n);
	mo.clear(n);
	REP(i , n - 1){
		Long u , v;
		cin >> u >> v;
		u--;
		v--;
		G.addEdge(u , v);
	}
	G.precalculate();
	REP(i , n){
		Long x;
		cin >> x;
		factors[i] = factorize(x);
	}
	
	Long Q;
	cin >> Q;
	
	REP(q, Q){
		Long u , v;
		cin >> u >> v;
		u--;
		v--;
		mo.addQuery(u , v);		
	}
	mo.process(n);
	REP(q, Q){
		cout << mo.query(q) << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	extSieve();

	for(Long i = 1; i <= MX; i++){
		inv[i] = modInverse(i);
	}
	Long T;
	cin >> T;
	REP(t, T) solve();

	return 0;
}

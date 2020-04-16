#include <bits/stdc++.h>
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Credits : https://www.geeksforgeeks.org/mos-algorithm-query-square-root-decomposition-set-1-introduction/
//For a good explanation check : https://www.hackerearth.com/practice/notes/mos-algorithm/
//And check : https://cp-algorithms.com/data_structures/sqrt_decomposition.html

const Long MX = 1e5;
const Long block = 400;
//Conditions
//1) No update
//2) Offline
//3) Knowing f([l,r]) , we can compute f([l + 1 , r]) , f([l - 1 , r]) , f([l, r + 1]) , f([l , r - 1]) in O(|f|)
//=> Overall complexity O((N + Q) sqrt(N) |F|)

struct Query{
    Long id, l, r;
    Query(){}
    Query(Long id, Long l, Long r): id(id), l(l) , r(r){}
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
	
	void clear(){
		q.clear();
	}

	void addQuery(Long l , Long r) {
		Long id = q.size();
		q.push_back( Query(id ,l , r));
	}
	
	void add(Long x, Long &ans){
		ans += A[x];
	}
	
	void remove(Long x, Long &ans){
		ans -= A[x];
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
				add(currR, ans);
				currR++;
			}
			while(currL > l){ //f(l - 1 , r)
				currL--;
				add(currL , ans);
			}
			while(currL < l){ // f(l + 1 , r)
				remove(currL , ans);
				currL++;
			}
			while(currR > r + 1){ //f(l , r - 1)
				currR--;
				remove(currR , ans);
			}
			answer[q[i].id] = ans;
	    }
	}
	
	Long query(Long id){
		return answer[id];
	}
	
}mo;
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Long N;
	cin >> N;
	REP(i, N){
		cin >> mo.A[i];
	}
	Long q;
	cin >> q;
	REP(i,q){
		Long l,r;
		cin >> l >> r;
		mo.addQuery( l , r);
	}
    mo.process(N);
    REP(i,q){
    	cout << mo.query(i) << endl;
	}
    return 0;
}

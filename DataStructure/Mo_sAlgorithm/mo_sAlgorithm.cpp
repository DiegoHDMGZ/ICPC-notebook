#include <bits/stdc++.h>
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Credits : https://www.geeksforgeeks.org/mos-algorithm-query-square-root-decomposition-set-1-introduction/
//For a good explanation check : https://www.hackerearth.com/practice/notes/mos-algorithm/

const Long MAX = 1e5;

//Conditions
//1) No update
//2) Offline
//3) Knowing f([l,r]) , we can compute f([l + 1 , r]) , f([l - 1 , r]) , f([l, r + 1]) , f([l , r - 1]) in O(|f|)

struct Query{
    Long id, l, r;

    Query(){}
    Query(Long id, Long l, Long r): l(l) , r(r), id(id){}

};

//sum query 

Long block;

bool compara(const Query &x, const Query &y){
	// queries are sorted in increasing order blocks and R values.
	if (x.l / block != y.l / block) return x.l / block < y.l / block;
	
	return x.r < y.r;
}

	

struct Mo{
	
	vector<Query> q;
	Long answer[MAX];
	Long A[MAX];

	void addQuery(Long l , Long r) {
		l--;
		r--;
		Long id = q.size();
		q.push_back( Query(id ,l , r));
	}
	
	void process(Long N) { //O((N + Q) sqrt(N) |F|)
	    block = (Long)sqrt(N);
	 
	    sort(q.begin() , q.end(), compara);
	    
	    Long currL = 0, currR = 0;
	    Long currSum = 0;
		Long sz = q.size();
		
	    REP(i, sz) {
	        // L and R values of current range
	        Long l = q[i].l, r = q[i].r;
	 
	        // Remove extra elements of previous range. For example if previous range is [0, 3] and current
	        // range is [2, 5], then a[0] and a[1] are subtracted
	        while (currL < l){
	            currSum -= A[currL];
	            currL++;
	        }
	 
	        // Add Elements of current Range
	        while (currL > l) {
	            currSum += A[currL-1];
	            currL--;
	        }
	        while (currR <= r){
	            currSum += A[currR];
	            currR++;
	        }
	 
	        // Remove elements of previous range.  For example when previous range is [0, 10] and current range
	        // is [3, 8], then a[9] and a[10] are subtracted
	        while (currR > r+1){
	            currSum -= A[currR-1];
	            currR--;
	        }
	 		
			answer[q[i].id] = currSum;
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


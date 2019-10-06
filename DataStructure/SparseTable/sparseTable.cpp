#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e6;
const Long loga = (Long)log2(MX)+1;

struct SparseTable{
	Long st[MX][loga];
	
	Long f(Long a, Long b){
		return a + b;
	}

	Long f(Long a){
		return a;
	}
	
	void build(vector<Long> &A){ // O(n log n)
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
	
	Long query(Long L, Long R){ //O(logn)
		Long ans = 0;
		Long T = R-L+1;
		Long lg = 31 - (__builtin_clz(T)); //te dice cuántos ceros hay a la izquierda
		
		for(Long j = lg; j >= 0; j--){
			if((1LL << j) <= T){
				ans = f(ans, st[L][j]);
				L += (1LL << j);
				T -= (1LL << j);
			}
		}
		
		return ans;
	}
	
	Long queryFast(Long L, Long R){ //O(|f|)
		//special cases : overlapping(  min, max, gcd)
		Long T = R - L + 1;
		Long lg = 31 - (__builtin_clz(T));
		return f(st[L][lg], st[R- (1LL << lg) + 1][lg]);
	}
	
}st;


int main() {
	return 0;
}


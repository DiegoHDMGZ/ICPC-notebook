#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MAX = 10;

void pow2(Long a[MAX][MAX], Long N, Long mod){ //O(N^3)
	Long b[MAX][MAX];
	REP(i,N){
		REP(j,N){
			b[i][j] = 0;
			REP(k,N){
				b[i][j] = (b[i][j] + (a[i][k]*a[k][j]) %mod)%mod;
			}
		}
	}
	
	REP(i,N){
		REP(j,N){
			a[i][j] = b[i][j];
		}
	}
}

void mult(Long a[MAX][MAX], Long b[MAX][MAX], Long c[MAX][MAX], Long N, Long mod){ //O(N^3)
	REP(i,N){
		REP(j,N){
			c[i][j] = 0;
			REP(k,N){
				c[i][j] = (c[i][j] + (a[i][k]*b[k][j]) %mod)%mod;
			}
		}
	}
}

void matPow(Long a[MAX][MAX], Long N , Long K,Long mod){
	//O(n³ log k)
	if(K == 0){
		REP(i,N){
			REP(j,N){
				a[i][j] = (i == j ) ? 1 : 0;
			}
		}
		return;
	}
	
	Long temp[MAX][MAX];
	
	REP(i,N){
		REP(j,N){
			temp[i][j] = a[i][j];
		}
	}
	matPow(temp, N, K/2, mod);

	pow2(temp, N, mod);

	if(K%2==1){
		Long temp2[MAX][MAX];
		mult(temp , a , temp2, N, mod);
		
		REP(i,N){
			REP(j,N){
				a[i][j] = temp2[i][j];
			}
		}
	}
	else{
		REP(i,N){
			REP(j,N){
				a[i][j] = temp[i][j];
			}
		}
	}
}

int main() {
	return 0;
}




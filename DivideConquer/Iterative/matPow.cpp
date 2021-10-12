#include <bits/stdc++.h>
#define getMatrix(n , m) Matrix(n , vector<Long>(m, 0))
using namespace std;

typedef long long Long;
typedef vector<vector<Long>> Matrix;

const Long MOD = 1e9 + 7;
Long add(Long a , Long b ){
	return (a + b) % MOD;
}

Long sub(Long a, Long b){
	return (a - b + MOD) % MOD;
}

Long mult(Long a, Long b){
	if(a * b < 0){
		return sub( 0 , abs(a * b) % MOD );
	}
	return (a * b) % MOD;
}


Matrix operator *(const Matrix &A, const Matrix &B){ //O( n^3)
	Long n1 = A.size();
	Long m1 = A[0].size();
	Long n2 = B.size();
	Long m2 = B[0].size();
	assert(m1 == n2);
	
	Long n = n1;
	Long m = m2;
	Matrix C(n, vector<Long>(m , 0));
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			for(Long k = 0; k < m1; k++){
				C[i][j] = add(C[i][j] , mult(A[i][k] , B[k][j]));
			}
		}
	}
	return C;
}

Matrix matPow(Matrix A, Long b){ //O(n^3 log b) only square matrix
	Long n = A.size();
	Matrix ans = Matrix(n , vector<Long>(n , 0));
	for(Long i = 0; i < n; i++){
		ans[i][i] = 1;
	}
	while(b > 0){
		if(b & 1){ //b % 2 == 1
			ans = ans * A;
		}
		A = A * A;
		b >>= 1; //b /= 2;
	}
	return ans;
}

void print(Matrix &A){
	Long n = A.size();
	Long m = A[0].size();
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	return 0;
}

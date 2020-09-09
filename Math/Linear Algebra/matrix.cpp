#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
#define getMatrix(n , m) Matrix(n , vector<Long>(m, 0))

using namespace std;

typedef long long Long;

typedef vector<vector<Long> > Matrix;

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

Matrix operator +(const Matrix &a , const Matrix &b){ //O(n * m)
	Long n = a.size();
	Long m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	
	Matrix c(n , vector<Long> (m ));
	
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j <m; j++){
			c[i][j] = add(a[i][j] , b[i][j] );
		}
	}
	return c;
}

Matrix operator *(const Matrix &a, const Matrix &b){ //O( n^3)
	Long n1 = a.size();
	Long m1 = a[0].size();
	Long n2 = b.size();
	Long m2 = b[0].size();
	assert(m1 == n2);
	
	Long n = n1;
	Long m = m2;
	Matrix c(n, vector<Long>(m , 0));
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			for(Long k = 0; k < m1; k++){
				c[i][j] = add(c[i][j] , mult(a[i][k] , b[k][j]));
			}
		}
	}
	return c;
}

void print(Matrix a , string nombre){
	cout << nombre << " = " << endl;
	Long n = a.size();
	Long m = a[0].size();
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
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

Long modInverse(Long a){ //O(logm) , m prime , a , m coprimes
	return fastPow(a, MOD - 2);
}

Long determinant(Matrix M){
	assert(M.size() == M[0].size());
	Long n = M.size();
	Long det = 1;
	for(Long i = 0; i < n; i++){
		if(M[i][i] == 0){
			for(Long j = i + 1; j < n; j++){
				if(M[j][i] != 0 ){
					swap(M[i], M[j]);
					det = mult(det, -1 );
					break;
				} 
			}
		}
		if(M[i][i] == 0) {
			return 0;
		}
		det = mult(det , M[i][i] );
		Long x = modInverse(M[i][i]);
		for(Long j = i + 1; j < n; j++){
			M[i][j] = mult(M[i][j] , x);
		}
		
		for(Long j = i + 1; j < n; j++){
			if(M[j][i] != 0){
				for(Long k = i + 1; k < n; k++){
					M[j][k] = sub(M[j][k] , mult(M[i][k] , M[j][i] ) );
				}
			}
		}
	}
	return det;
}

Matrix identity(Long n){
	Matrix ans = getMatrix(n , n);
	for(Long i = 0; i < n; i++) ans[i][i] = 1;
	return ans;
}

Matrix inverse(Matrix M){
	assert(M.size() == M[0].size());
	Long n = M.size();
	Matrix ans = identity(n);
	
	for(Long i = 0; i < n; i++){
		if(M[i][i] == 0){
			for(Long j = i + 1; j < n; j++){
				if(M[j][i] != 0 ){
					swap(M[i], M[j]);
					swap(ans[i], ans[j]);
					break;
				} 
			}
		}
		assert(M[i][i] != 0);
		Long x = modInverse(M[i][i]);
		for(Long j = 0; j < n; j++){
			M[i][j] = mult(M[i][j] , x);
			ans[i][j] = mult(ans[i][j] , x);
		}
		
		for(Long j = i + 1; j < n; j++){
			if(M[j][i] != 0){
				Long c = M[j][i];
				for(Long k = 0; k < n; k++){
					M[j][k] = sub(M[j][k] , mult(M[i][k] , c ) );
					ans[j][k] = sub(ans[j][k] , mult(ans[i][k] , c));
				}
			}
		}
	}
	
	for(Long i = n - 2; i >= 0; i--){
		for(Long j = i + 1; j < n; j++){
			if(M[i][j] != 0){
				Long c = M[i][j];
				for(Long k = 0; k < n; k++){
					M[i][k] = sub(M[i][k] , mult(M[j][k] , c));
					ans[i][k] = sub(ans[i][k] , mult(ans[j][k] , c));
				}
			}
		}
	}
	
	return ans;
}

/*
7 
5 6 -5 9 12 38 18
20 69 -2 3 15 22 17
1 -2 0 3 47 -38 -12
-1 -2 -3 0 0 0 0
4 3 2 5 6 8 1
3 9 8 1 3 2 1
-5 0 5 6 7 8 9
Rpta = 987646945
*/

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	
	Long n ;
	cin >> n;
	Matrix a(n , vector<Long> (n , 0));
	REP(i , n){
		REP(j , n){
			cin >> a[i][j];
		}
	}
	cout << determinant(a) << endl;
	return 0;
}

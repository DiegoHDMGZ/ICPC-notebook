#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

typedef vector<vector<Long> > Matrix;

Long add(Long a , Long b , Long m){
	return (a + b) % m;
}

Long sub(Long a, Long b, Long m){
	return (a - b + m) % m;
}

Long mult(Long a, Long b, Long m){
	if(a * b < 0){
		return sub( 0 , abs(a * b) % m , m);
	}
	return (a * b) % m;
}

const Long MOD = 1e9 + 7;

Matrix operator +(const Matrix &a , const Matrix &b){ //O(n * m)
	Long n = a.size();
	Long m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	
	Matrix c(n , vector<Long> (m ));
	
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j <m; j++){
			c[i][j] = add(a[i][j] , b[i][j], MOD );
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
				c[i][j] = add(c[i][j] , mult(a[i][k] , b[k][j], MOD), MOD);
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

Long fastPow(Long a, Long b , Long mod){ //O(logb)
	Long ans = 1;
	while(b > 0){
		if(b & 1 == 1){ //b % 2 == 1
			ans = mult(ans ,a , mod);
		}
		a = mult(a , a  , mod);
		b >>= 1; //b /= 2;
	}
	return ans;
}

Long modInverse(Long a, Long m){ //O(logm) , m prime , a , m coprimes
	return fastPow(a,m-2,m);
}

Long determinant(Matrix M, Long mod){
	assert(M.size() == M[0].size());
	Long n = M.size();
	Long det = 1;
	for(Long i = 0; i < n; i++){
		if(M[i][i] == 0){
			for(Long j = i + 1; j < n; j++){
				if(M[j][i] != 0 ){
					swap(M[i], M[j]);
					det = mult(det, -1 , mod);
					break;
				} 
			}
		}
		if(M[i][i] == 0) {
			return 0;
		}
		det = mult(det , M[i][i] , mod);
		Long x = modInverse(M[i][i], mod);
		for(Long j = i + 1; j < n; j++){
			M[i][j] = mult(M[i][j] , x, mod);
		}
		
		for(Long j = i + 1; j < n; j++){
			if(M[j][i] != 0){
				for(Long k = i + 1; k < n; k++){
					M[j][k] = sub(M[j][k] , mult(M[i][k] , M[j][i] , mod) , mod);
				}
			}
		}
	}
	return det;
}
/*
7 1000000007
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

	
	Long n , mod;
	cin >> n >> mod;
	Matrix a(n , vector<Long> (n , 0));
	REP(i , n){
		REP(j , n){
			cin >> a[i][j];
		}
	}
	cout << determinant(a, mod) << endl;
	return 0;
}

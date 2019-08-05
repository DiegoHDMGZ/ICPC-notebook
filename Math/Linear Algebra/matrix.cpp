#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-6;
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



Matrix add(const Matrix &a , const Matrix &b){ //O(n * m)
	Long n = a.size();
	Long m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	
	Matrix c(n , vector<Long> (m ));
	
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j <m; j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

Matrix mult(const Matrix &a, const Matrix &b){ //O( n^3)
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
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

void print(Matrix &a){
	Long n = a.size();
	Long m = a[0].size();
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

Long fastPow(Long a, Long b, Long c){ //O(logb)
	if(b == 0){
		return 1;
	}
	
	Long temp = fastPow(a,b/2,c);
	
	temp = (temp*temp)%c;
	
	return (b%2 == 0)? temp : (a%c*temp)%c;
}

Long modInverse(Long a, Long m){ //O(logm)
	//m debe ser primo
	//if(__gcd(a,m) != 1) return -1;
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
		for(Long j = i + 1; j < n; j++){
			if(M[j][i] != 0){
				for(Long k = i + 1; k < n; k++){
					M[j][k] = sub(M[j][k] , mult( mult(M[i][k] , M[j][i] , mod) , modInverse(M[i][i], mod) , mod) , mod);
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

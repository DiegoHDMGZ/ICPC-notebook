#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;
typedef vector<vector<Long> > Matrix;

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

Matrix mult( Matrix &a,   Matrix &b , Long mod) { //O( n^3)
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
				c[i][j] %= mod;
			}
		}
	}
	return c;
}


Matrix matPow( Matrix a, Long b , Long mod){ //O(n^3 log b) only square matrix
	Long n = a.size();
	Matrix ans = Matrix(n , vector<Long>(n , 0));
	for(Long i = 0; i < n; i++){
		ans[i][i] = 1;
	}
	while(b > 0){
		if(b & 1 == 1){ //b % 2 == 1
			ans = mult(ans , a , mod);
		}
		a = mult(a , a , mod);
		b >>= 1; //b /= 2;
	}
	return ans;
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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Long n , b ,mod;
	cin >> n >> b >> mod;
	Matrix a(n , vector<Long>(n));
	REP(i , n){
		REP(j , n){
			cin >> a[i][j];
		}
	}
	
	Matrix c = matPow(a , b , mod);
	print(c);
	return 0;
}

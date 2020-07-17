#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
#define getMatrix(n , m) Matrix(n , vector<Double>(m))
using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-6;
typedef vector<vector<Double> > Matrix;

Matrix operator +(const Matrix &a , const Matrix &b){ //O(n * m)
	Long n = a.size();
	Long m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	
	Matrix c(n , vector<Double> (m ));
	
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j <m; j++){
			c[i][j] = a[i][j] + b[i][j];
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
	Matrix c(n, vector<Double>(m , 0));
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			for(Long k = 0; k < m1; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

Double determinant(Matrix M){
	assert(M.size() == M[0].size());
	Long n = M.size();
	Double det = 1.0;
	for(Long i = 0; i < n; i++){
		Long pivot = i;
		//heuristic to find pivot
		for(Long j = i + 1; j < n; j++){
			if(fabs(M[j][i]) > fabs(M[pivot][i]) ){
				pivot = j;
			} 
		}
		if(fabs(M[pivot][i]) < EPS) {
			return 0;
		}
		if(i != pivot){
			swap(M[i] , M[pivot]);
			det *= -1.0;
		}
		det *= M[i][i];
		for(Long j = i + 1; j < n; j++){
			if(fabs(M[j][i]) >= EPS){
				for(Long k = i + 1; k < n; k++){
					M[j][k] -= (Double)M[i][k] * M[j][i] / M[i][i];
				}
			}
		}
	}
	return det;
}

void print(Matrix a, string name){
	cout << name << " = " << endl;
	Long n = a.size();
	Long m = a[0].size();
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			if(fabs(a[i][j]) < EPS) {
				cout << 0 << " ";
			} else {
				cout << a[i][j] << " ";
			}
			
		}
		cout << endl;
	}
	cout << endl;
}

Matrix inverse(Matrix M){
	assert(M.size() == M[0].size());
	Long n = M.size();
	Matrix ans(n , vector<Double>(n, 0));
	for(Long i = 0; i < n; i++){
		ans[i][i] = 1;
	}
	
	for(Long i = 0; i < n; i++){
		Long pivot = i;
		//heuristic to find pivot
		for(Long j = i + 1; j < n; j++){
			if(fabs(M[j][i]) > fabs(M[pivot][i]) ){
				pivot = j;
			} 
		}
	
		if(i != pivot){
			swap(M[i] , M[pivot]);
			swap(ans[i], ans[pivot]);
		}
		assert(fabs(M[i][i]) >= EPS);
		double c = M[i][i];
		for(Long j = 0; j < n; j++){
			M[i][j] /= c;
			ans[i][j] /= c;
		}
		for(Long j = i + 1; j < n; j++){
			if(fabs(M[j][i]) >= EPS){
				double c = M[j][i];
				for(Long k = 0; k < n; k++){
					M[j][k] -= M[i][k] * c   ;
					ans[j][k] -= ans[i][k] * c; 
				}
			}
		}
	}
	
	for(Long i = n - 2; i >= 0; i--){
		for(Long j = i + 1; j < n; j++){
			if(fabs(M[i][j]) >= EPS){
				Double c = M[i][j];
				for(Long k = 0; k < n; k++){
					M[i][k] -= M[j][k] * c;
					ans[i][k] -= ans[j][k] * c;
				}
			}
		}
	}
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	
	Long n;
	cin >> n;
	Matrix a(n , vector<Double>(n));
	REP(i , n){
		REP(j , n){
			cin >> a[i][j];
		}
	}
	Matrix inv = inverse(a);
	print(a * inv, "I");

	return 0;
}

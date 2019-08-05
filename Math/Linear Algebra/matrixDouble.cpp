#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-6;
typedef vector<vector<Double> > Matrix;

Matrix add(const Matrix &a , const Matrix &b){ //O(n * m)
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

Matrix mult(const Matrix &a, const Matrix &b){ //O( n^3)
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

	
	Long n;
	cin >> n;
	Matrix a(n , vector<Double>(n));
	REP(i , n){
		REP(j , n){
			cin >> a[i][j];
		}
	}
	cout << fixed << setprecision(3) << determinant(a) << endl;
	return 0;
}

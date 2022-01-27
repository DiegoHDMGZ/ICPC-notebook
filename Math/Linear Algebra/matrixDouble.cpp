#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
#define getMatrix(n , m) Matrix(n , vector<Double>(m, 0))
using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-6;
typedef vector<vector<Double>> Matrix;

Matrix operator +(const Matrix &a , const Matrix &b){ //O(n * m)
	Long n = a.size();
	Long m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	
	Matrix c = getMatrix(n , m);
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

Matrix operator *(const Matrix &a, const Matrix &b){ //O(n^3)
	Long n1 = a.size();
	Long m1 = a[0].size();
	Long n2 = b.size();
	Long m2 = b[0].size();
	assert(m1 == n2);
	
	Long n = n1;
	Long m = m2;
	Matrix c = getMatrix(n, m);
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			for(Long k = 0; k < m1; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

Double determinant(Matrix M) { //O(n^3)
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

Long linearSystem(Matrix M, vector<Double> &ans) { //O(m * n * min(n, m))
	//AX = b
	//M = [A|b]
	Long n = M.size();
	Long m = (Long)M[0].size() - 1;
	
	Long row = 0;
	vector<Long> position(m, -1);
	for (Long col = 0; col < m; col++) {
		if (row == n) break;
		Long pivot = row;
		for(Long i = row + 1; i < n; i++){
			if(fabs(M[i][col]) > fabs(M[pivot][col]) ){
				pivot = i;
			} 
		}
		if(row != pivot){
			swap(M[row] , M[pivot]);
		}
		if (fabs(M[row][col]) <= EPS) {
			continue;
		}
		position[col] = row;
		for(Long j = col + 1; j <= m; j++){
			M[row][j] /= M[row][col];
		}
		M[row][col] = 1;
		for(Long i = 0; i < n; i++){
			if (i == row) continue;
			if(fabs(M[i][col]) >= EPS){
				for(Long j = col + 1; j <= m; j++){
					M[i][j] -= M[row][j] * M[i][col];
				}
				M[i][col] = 0;
			}
		}
		row++;
	}
	ans = vector<Double>(m, 0);
	bool infinite = false;
	for (Long i = 0; i < m; i++) {
		if (position[i] != -1) {
			ans[i] = M[position[i]][m];
		} else {
			infinite = true;
		}
	}
	for (int i = 0; i < n; i++) {
		bool allZero = true;
		for (int j = 0; j < m; j++) {
			if (M[i][j] != 0) {
				allZero = false;
			}
		}
		if (allZero && M[i][m] != 0) {
			ans = {};
			return 0;
		}
	}
	if (infinite) return 2;
	return 1;
}

Matrix inverse(Matrix M) { //O(n^3)
	assert(M.size() == M[0].size());
	Long n = M.size();
	Matrix ans = getMatrix(n , n);
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
		for(Long j = 0; j < n; j++){
			if (j == i) continue;
			if(fabs(M[j][i]) >= EPS){
				double c = M[j][i];
				for(Long k = 0; k < n; k++){
					M[j][k] -= M[i][k] * c   ;
					ans[j][k] -= ans[i][k] * c; 
				}
			}
		}
	}
	return ans;
}

int main(){
	return 0;
}

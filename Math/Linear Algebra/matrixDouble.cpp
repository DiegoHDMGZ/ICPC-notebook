#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define getMatrix(n , m) Matrix(n , vector<Double>(m, 0))
using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-6;
typedef vector<vector<Double>> Matrix;

Double near(Double a, Double b) {
	return fabs(a - b) < EPS;
}

Matrix operator +(const Matrix &a , const Matrix &b){ //O(n * m)
	int n = a.size();
	int m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	Matrix c = getMatrix(n , m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

Matrix operator *(const Matrix &a, const Matrix &b){ //O(n^3)
	int n1 = a.size();
	int m1 = a[0].size();
	int n2 = b.size();
	int m2 = b[0].size();
	assert(m1 == n2);
	int n = n1;
	int m = m2;
	Matrix c = getMatrix(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m1; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}

Matrix identity(int n) { //O(n)
	Matrix ans = getMatrix(n , n);
	for (int i = 0; i < n; i++) ans[i][i] = 1;
	return ans;
}


Matrix matPow(Matrix A, Long b) { //O(n^3 log b)
	int n = A.size();
	Matrix ans = identity(n);
	while (b > 0) {
		if (b & 1) ans = ans * A;
		A = A * A;
		b >>= 1;
	}
	return ans;
}


int findPivot(Matrix &M, int row, int col) {
	//heuristic to find pivot
	int pivot = row;
	for (int i = row + 1; i < M.size(); i++) {
		if(fabs(M[i][col]) > fabs(M[pivot][col])){
			pivot = i;
		} 
	}
	return pivot;
}

Double determinant(Matrix M) { //O(n^3)
	assert(M.size() == M[0].size());
	int n = M.size();
	Double det = 1.0;
	for (int i = 0; i < n; i++) {
		int pivot = findPivot(M, i, i);
		if (near(M[pivot][i], 0)) return 0;
		if (i != pivot) {
			swap(M[i] , M[pivot]);
			det *= -1.0;
		}
		det *= M[i][i];
		for (int j = i + 1; j < n; j++) {
			if (!near(M[j][i], 0)) {
				for (int k = i + 1; k < n; k++) {
					M[j][k] -= M[i][k] * M[j][i] / M[i][i];
				}
			}
		}
	}
	return det;
}

Matrix inverse(Matrix M) { //O(n^3)
	assert(M.size() == M[0].size());
	int n = M.size();
	Matrix ans = identity(n);

	for (int i = 0; i < n; i++) {
		int pivot = findPivot(M, i, i);
		if (i != pivot) {
			swap(M[i], M[pivot]);
			swap(ans[i], ans[pivot]);
		}
		if (near(M[i][i], 0)) return {};
		double c = M[i][i];
		for (int j = 0; j < n; j++) {
			M[i][j] /= c;
			ans[i][j] /= c;
		}
		for (int j = 0; j < n; j++){
			if (j == i) continue;
			if (!near(M[j][i], 0)){
				double c = M[j][i];
				for (int k = 0; k < n; k++) {
					M[j][k] -= M[i][k] * c;
					ans[j][k] -= ans[i][k] * c; 
				}
			}
		}
	}
	return ans;
}

int linearSystem(Matrix M, vector<Double> &ans) { //O(m * n * min(n, m))
	//AX = b
	//M = [A|b]
	int n = M.size();
	int m = (Long)M[0].size() - 1;
	
	int row = 0;
	vector<int> position(m, -1);
	for (int col = 0; col < m; col++) {
		if (row == n) break;
		int pivot = findPivot(M, row, col);
		if (row != pivot) swap(M[row] , M[pivot]);
		if (near(M[row][col], 0)) continue;
		position[col] = row;
		for (int j = col + 1; j <= m; j++) {
			M[row][j] /= M[row][col];
		}
		M[row][col] = 1;
		for (int i = 0; i < n; i++) {
			if (i == row) continue;
			if (!near(M[i][col], 0)) {
				for (int j = col + 1; j <= m; j++) {
					M[i][j] -= M[row][j] * M[i][col];
				}
				M[i][col] = 0;
			}
		}
		row++;
	}
	ans = vector<Double>(m, 0);
	bool infinite = false;
	for (int i = 0; i < m; i++) {
		if (position[i] != -1) {
			ans[i] = M[position[i]][m];
		} else {
			infinite = true;
		}
	}
	for (int i = 0; i < n; i++) {
		bool allZero = true;
		for (int j = 0; j < m; j++) {
			if (!near(M[i][j], 0)) {
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

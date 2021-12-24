#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back
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

Matrix operator +(const Matrix &a , const Matrix &b){ //O(n * m)
	Long n = a.size();
	Long m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	
	Matrix c = getMatrix(n , m);
	
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
	Matrix c = getMatrix(n, m);
	for(Long i = 0; i < n; i++){
		for(Long j = 0; j < m; j++){
			for(Long k = 0; k < m1; k++){
				c[i][j] = add(c[i][j] , mult(a[i][k] , b[k][j]));
			}
		}
	}
	return c;
}

void print(Matrix a , string name){
	cout << name << " = " << endl;
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

Long invert(Long a){ //O(logm) , m prime , a , m coprimes
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
		Long x = invert(M[i][i]);
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

Long linearSystem(Matrix M, vector<Long> &ans) {
	//AX = b
	//M = [A|b]
	Long n = M.size();
	Long m = (Long)M[0].size() - 1;
	
	Long row = 0;
	vector<Long> position(m, -1);
	for (Long col = 0; col < m; col++) {
		if (row == n) break;
		if (M[row][col] == 0) {
			for(Long i = row + 1; i < n; i++){
				if(M[i][col] != 0 ){
					swap(M[i], M[row]);
					break;
				} 
			}
		}
		if (M[row][col] == 0) {
			continue;
		}
		position[col] = row;
		Long x = invert(M[row][col]);
		for(Long j = col ; j <= m; j++){
			M[row][j] = mult(M[row][j] , x);
		}
		
		for(Long i = 0; i < n; i++){
			if (i == row) continue;
			if(M[i][col] != 0){
				for(Long j = col + 1; j <= m; j++){
					M[i][j] = sub(M[i][j] , mult(M[row][j] , M[i][col]));
				}
				M[i][col] = 0;
			}
		}
		row++;
	}
	ans = vector<Long>(m, 0);
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
		Long x = invert(M[i][i]);
		for(Long j = 0; j < n; j++){
			M[i][j] = mult(M[i][j] , x);
			ans[i][j] = mult(ans[i][j] , x);
		}
		
		for(Long j = 0; j < n; j++){
			if (j == i) continue;
			if(M[j][i] != 0){
				Long c = M[j][i];
				for(Long k = 0; k < n; k++){
					M[j][k] = sub(M[j][k] , mult(M[i][k] , c));
					ans[j][k] = sub(ans[j][k] , mult(ans[i][k] , c));
				}
			}
		}
	}
	return ans;
}

int main(){
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define getMatrix(n , m) Matrix(n , vector<ModInt>(m, 0))

using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
struct ModInt {
	Long val;
	ModInt(Long val = 0) {
		val %= MOD;
		if (val < 0) val += MOD;
		this->val = val;
	}
	ModInt operator +(const ModInt &other) const {
		if (val + other.val < MOD) return val + other.val;
		return val + other.val - MOD;
	}
	ModInt operator -(const ModInt &other) const {
		if (val - other.val >= 0) return val - other.val;
		return val - other.val + MOD;
	}
	ModInt operator -() const {
		return MOD - val;
	}
	ModInt operator *(const ModInt &other) const {
		return (val * other.val) % MOD;
	}
	ModInt operator +=(const ModInt &other) {
		*this = *this + other;
		return *this;
	}
	ModInt operator -=(const ModInt &other) {
		*this = *this - other;
		return *this;
	}
	ModInt operator *=(const ModInt &other) {
		*this = *this * other;
		return *this;
	}
	//Exponentiation
	//(a ^ x) % mod = (a ^ r) % mod 
	//Fermat's little theorem : r = x % (mod - 1), mod prime
	//Euler's theorem : r = x % phi(mod), (a, mod coprimes)
	ModInt pow(Long b) const { //O(log b)
		ModInt ans = 1;
		ModInt a = val;
		while (b > 0) {
			if (b & 1) ans *= a;
			a *= a;
			b >>= 1;
		}
		return ans;
	}
	ModInt invert() const { //O(log mod) 
		//mod prime
		return pow(MOD - 2);
	}
	ModInt operator /(const ModInt &other) const {
		return *this * other.invert();
	}
	ModInt operator /=(const ModInt &other) {
		*this = *this / other;
		return *this;
	}
	bool operator ==(const ModInt &other) const {
		return val == other.val;
	}
	bool operator !=(const ModInt &other) const {
		return val != other.val;
	}
	bool operator <(const ModInt &other) const {
		return val < other.val;
	}
	bool operator >(const ModInt &other) const {
		return val > other.val;
	}
};

istream & operator >> (istream &in, ModInt &A){
	Long val;
	in >> val;
	A = ModInt(val);
	return in;
}

ostream & operator << (ostream &out, const ModInt &A){
	out << A.val;
	return out;
}

typedef vector<vector<ModInt>> Matrix;

Matrix operator +(const Matrix &a , const Matrix &b) { //O(n * m)
	int n = a.size();
	int m = a[0].size();
	assert(a.size() == b.size() );
	assert(a[0].size() == b[0].size());
	Matrix c = getMatrix(n , m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

Matrix operator *(const Matrix &a, const Matrix &b) { //O(n^3)
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
	if (M[row][col] != 0) return row;
	for (int i = row + 1; i < M.size(); i++) {
		if(M[i][col] != 0) return i;
	}
	return row;
}

ModInt determinant(Matrix M){ //O(n^3)
	assert(M.size() == M[0].size());
	int n = M.size();
	ModInt det = 1;
	for (int i = 0; i < n; i++) {
		int pivot = findPivot(M, i, i);
		if (pivot != i) {
			swap(M[i], M[pivot]);
			det *= ModInt(-1);
		}
		if (M[i][i] == 0) return 0;
		det *= M[i][i];
		ModInt inv = M[i][i].invert();
		for (int j = i + 1; j < n; j++){
			M[i][j] *= inv;
		}
		
		for (int j = i + 1; j < n; j++) {
			if (M[j][i] != 0) {
				for (int k = i + 1; k < n; k++) {
					M[j][k] -= M[i][k] * M[j][i];
				}
			}
		}
	}
	return det;
}

Matrix invert(Matrix M) { //O(n^3)
	assert(M.size() == M[0].size());
	int n = M.size();
	Matrix ans = identity(n);
	for (int i = 0; i < n; i++) {
		int pivot = findPivot(M, i, i);
		if (i != pivot) {
			swap(M[i], M[pivot]);
			swap(ans[i], ans[pivot]);
		}
		if (M[i][i] == 0) return {};
		ModInt inv = M[i][i].invert();
		for (int j = 0; j < n; j++) {
			M[i][j] *= inv;
			ans[i][j] *= inv;
		}
		for (int j = 0; j < n; j++) {
			if (j == i) continue;
			if (M[j][i] != 0) {
				ModInt c = M[j][i];
				for (int k = 0; k < n; k++){
					M[j][k] -= M[i][k] * c;
					ans[j][k] -= ans[i][k] * c;
				}
			}
		}
	}
	return ans;
}

struct Solution {
	//Solution for the linear system solver
	vector<ModInt> X;
	vector<vector<ModInt>> basis;
	//All solutions are X + a linear combination of the vector of basis
	//empty X means no solution
	//Any X but empty basis means unique solution
};

Solution linearSystem(Matrix M) { //O(m * n * min(n, m))
	//AX = b
	//M = [A|b]
	Solution solution;
	int n = M.size();
	int m = (int)M[0].size() - 1;
	//n equations, m variables
	int row = 0;
	vector<int> dependent(n, -1);
	for (int col = 0; col < m; col++) {
		if (row < n) {
			int pivot = findPivot(M, row, col);
			swap(M[row], M[pivot]);
		}
		if (row == n || M[row][col] == 0) {
			//independent variable
			vector<ModInt> vec(m);
			vec[col] = 1;
			for (int i = 0; i < row; i++) {
				vec[dependent[i]] = -M[i][col];
			}
			solution.basis.push_back(vec);
			continue;
		}
		if (row == n) continue;
		dependent[row] = col;
		ModInt inv = M[row][col].invert();
		for (int j = col ; j <= m; j++) {
			M[row][j] *= inv;
		}
		for (int i = 0; i < n; i++) {
			if (i == row) continue;
			if (M[i][col] != 0){
				for (int j = col + 1; j <= m; j++) {
					M[i][j] -= M[row][j] * M[i][col];
				}
				M[i][col] = 0;
			}
		}
		row++;
	}
	solution.X = vector<ModInt>(m, 0);
	for (int i = 0; i < n; i++) {
		if (dependent[i] != -1) {
			solution.X[dependent[i]] = M[i][m];
		} 
	}
	for (int i = 0; i < n; i++) {
		if (M[i][m] != 0) {
			M[i].pop_back();
			if (M[i] == vector<ModInt>(m)) {
				solution.X = {};
				solution.basis = {};
				return solution;
			}
		}
	}
	return solution;
}

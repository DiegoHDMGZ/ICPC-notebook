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

Matrix mul(const Matrix &a, const Matrix &b){ //O( n^3)
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

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	
	Long n, m;
	cin >> n >> m;
	Matrix a(n , vector<Long>(m));
	REP(i , n){
		REP(j , m){
			cin >> a[i][j];
		}
	}
	cin >> n >> m;
	Matrix b(n , vector<Long>(m));
	REP(i , n){
		REP(j , m){
			cin >> b[i][j];
		}
	}
	
	Matrix c = mul(a , b);
	print(c);
	return 0;
}

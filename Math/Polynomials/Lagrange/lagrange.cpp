#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

typedef vector<Long> polynomial;

const Long MOD = 1e9 + 7;

Long add(Long a, Long b){
	return (a + b) % MOD;
}

Long subs(Long a, Long b){
	return (a - b + MOD) % MOD;
}

Long mult(Long a , Long b){
	return (a * b) % MOD;
}

Long fastPow(Long a, Long b){ //O(logb)
	Long ans = 1;
	while(b > 0){
		if(b & 1 == 1){ 
			ans = mult(ans ,a );
		}
		a = mult(a , a  );
		b >>= 1; 
	}
	return ans;
}

Long modInverse(Long a){
	return fastPow(a , MOD - 2);
}

Long divide(Long a, Long b){
	return mult(a, modInverse(b));
}

polynomial operator *(const polynomial &a, const polynomial &b) {
	Long n = a.size();
	Long m = b.size();
	polynomial ans(n + m - 1 , 0);
	REP(i , n){
		REP(j , m){
			ans[i + j] = add(ans[i + j] , mult(a[i] , b[j]));
		}
	}
	return ans;
} 

polynomial operator +(const polynomial &a, const polynomial &b){
	Long n = a.size();
	Long m = b.size();
	polynomial ans(max(n , m) , 0);
	for(int i = 0; i < max(n , m); i++){
		Long x = 0 , y = 0;
		if(i < a.size()) x = a[i];
		if(i < b.size()) y = b[i];
		ans[i] = add(x , y);
	}
	return ans;
}

Long derivative(polynomial &p, Long x){
	if(p.size() == 1){
		return {0};
	}
	Long ans = 0;
	Long cur = 1;
	for(int i = 1; i < p.size(); i++){
		ans = add(ans , mult(mult(i , p[i]) , cur));
		cur = mult(cur , x);
	}
	return ans;
}

polynomial ruffini(polynomial &p , Long c){
	Long n = p.size();
	polynomial ans(n - 1);
	Long r = 0;
	for(Long i = n - 2; i >= 0; i--){
		ans[i] = add(p[i + 1] , r);
		r = mult(ans[i] , c);
	}
	return ans;
}

polynomial lagrange(vector<Long> &X, vector<Long> &Y){ //O(n^2)
	//hidden constant
	polynomial ans(X.size(), 0);
	polynomial f = {1};
	for(int i = 0; i < X.size(); i++){
		f = f * polynomial({MOD - X[i] , 1});
	}
	for(int i = 0; i < X.size(); i++){
		polynomial cur = polynomial({mult(Y[i] , modInverse(derivative(f , X[i])))}) * f;
		cur = ruffini(cur , X[i]);
		ans = ans + cur;
	}
	return ans;
}

Long interpolate(Long x, vector<Long> &xSample, vector<Long> &ySample){//O(n^2)
	Long y = 0;
	for(int i = 0; i < xSample.size(); i++){
		Long cur = ySample[i];
		Long den = 1;
		for(int j = 0; j < xSample.size(); j++){
			if(i == j) continue;
			den = mult(den ,  subs(xSample[i] , xSample[j]));
			cur = mult(cur , subs(x , xSample[j]));
		}
		cur = divide(cur , den);
		y = add(y , cur);
	}
	return y;
}

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef long double Double;

typedef vector<Double> polynomial;


polynomial operator *(const polynomial &a, const polynomial &b) {
	Long n = a.size();
	Long m = b.size();
	polynomial ans(n + m - 1 , 0);
	
	REP(i , n){
		REP(j , m){
			ans[i + j] +=a[i] * b[j];
		}
	}

	return ans;
} 

polynomial operator +(const polynomial &a, const polynomial &b){
	Long n = a.size();
	Long m = b.size();
	polynomial ans(max(n , m) , 0);
	for(int i = 0; i < max(n , m); i++){
		Double x = 0 , y = 0;
		if(i < a.size()) x = a[i];
		if(i < b.size()) y = b[i];
		ans[i] = x + y;
	}
	return ans;
}

Double derivative(polynomial &p, Double x){
	if(p.size() == 1){
		return {0};
	}
	Double ans = 0;
	Double cur = 1;
	for(int i = 1; i < p.size(); i++){
		ans += i * p[i] * cur;
		cur *= x;
	}
	return ans;
}

polynomial ruffini(polynomial &p , Double c){
	Long n = p.size();
	polynomial ans(n - 1);
	Double r = 0;
	for(Long i = n - 2; i >= 0; i--){
		ans[i] = p[i + 1] + r;
		r = ans[i] * c;
	}
	return ans;
}

polynomial lagrange(vector<Double> &X, vector<Double> &Y){ //O(n^2)
	//hidden constant
	polynomial ans(X.size(), 0);
	polynomial f = {1};
	for(int i = 0; i < X.size(); i++){
		f = f * polynomial({- X[i] , 1});
	}
	for(int i = 0; i < X.size(); i++){
		polynomial cur = polynomial({Y[i] / derivative(f , X[i])}) * f;
		cur = ruffini(cur , X[i]);
		ans = ans + cur;
	}
	return ans;
}

Long interpolate(Double x, vector<Double> &xSample, vector<Double> &ySample){//O(n^2)
	Double y = 0;
	for(int i = 0; i < xSample.size(); i++){
		Double cur = ySample[i];
		for(int j = 0; j < xSample.size(); j++){
			if(i == j) continue;
			cur *=  (x - xSample[j]) / (xSample[i] - xSample[j]);
		}
		y = y + cur;
	}
	return y;
}

void print(string name, polynomial p){
	cout << name << " = ";
	for(Long i = (Long)p.size() - 1; i >= 0; i--){
		cout << fixed << setprecision(2) << p[i] << "x" << i;
		if(i != 0) cout << " + ";
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	vector<Double> X, Y;
	Long n;
	cin >> n;
	REP(i , n){
		Long x , y;
		cin >> x >> y;
		X.pb(x);
		Y.pb(y);
	}
	print("lagrange", lagrange(X, Y));
	
	return 0;
}

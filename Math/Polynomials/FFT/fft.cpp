#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;
typedef long double Double;
typedef complex<Double> Complex;

const Double PI = acos(-1);

void fft(vector<Complex> &a, bool invert){ //O(n log n)
	//n must be a power of 2
	Long n = a.size();
	if(n == 1){
		return;
	}
	Long sgn = 1;
	if(invert) sgn = -1;
	Complex wn = polar((Double)1 , sgn * 2.0 * PI / n);
	Complex w(1);
	vector<Complex> even(n / 2), odd(n / 2);
	for(Long i = 0; 2 * i < n; i++){
		even[i] = a[2 * i];
		odd[i] = a[2 * i + 1];
	}
	fft(even, invert);
	fft(odd, invert);
	for(Long i = 0; 2 * i < n; i++){
		a[i] = even[i] + w * odd[i];
		a[i + n / 2] = even[i] - w * odd[i];
		if(invert){
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
		w *= wn;
	}
}

typedef vector<Long> polynomial;

polynomial operator *(const polynomial &a, const polynomial &b) {
	vector<Complex> fa(a.begin(), a.end());
	vector<Complex> fb(b.begin(), b.end());
	Long n = 1;
	while(n < a.size() + b.size()){
		n <<= 1;
	}
	fa.resize(n);
	fb.resize(n);
	
	fft(fa, false);
	fft(fb, false);
	
	for(Long i = 0; i < n; i++){
		fa[i] *= fb[i];
	}
	fft(fa, true);
	
	polynomial ans(a.size() + b.size() - 1);
	for(Long i = 0; i < n; i++){
		ans[i] = round(fa[i].real());
	}
	return ans;
} 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

//MOD = 2^k * c + 1
//r = primiteve root of MOD
//wn = r^c

typedef long long Long;

const Long MOD = 998244353; //MOD = 2^23 * 19 + 1

const Long root = 3;//primitve root of MOD
const Long rootInv = 332748118;//inverse modular of root

struct Field{
	Long num;
	Field(Long num = 0) : num(num){}
	
	Field operator + (const Field &F) const {
		return (num + F.num) % MOD;
	}
	
	Field operator - (const Field &F) const {
		return (num - F.num + MOD) % MOD;
	}
	
	Field operator * (const Field &F) const {
		return (num * F.num) % MOD;
	}
	
	Field operator *= (const Field &F)  {
		num *= F.num;
		num %= MOD;
		return *this;
	}
};

const Field inv2 = Field(499122177);//mod inverse of 2

Long mult(Long a, Long b){
	return (a * b ) % MOD;
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


void ntt(vector<Field> &a, bool invert, Field wn){ //O(n log n)
	//n must be a power of 2
	Long n = a.size();
	if(n == 1){
		return;
	}

	Field w (1);
	vector<Field> even(n / 2), odd(n / 2);
	for(Long i = 0; 2 * i < n; i++){
		even[i] = a[2 * i];
		odd[i] = a[2 * i + 1];
	}

	ntt(even, invert, wn * wn);
	ntt(odd, invert, wn * wn);
	for(Long i = 0; 2 * i < n; i++){
		a[i] = even[i] + w * odd[i];
		a[i + n / 2] = even[i] - w * odd[i];
		if(invert){
			a[i] *= inv2;
			a[i + n / 2] *= inv2;
		}
		w *= wn;
	}
}

typedef vector<Long> polynomial;

polynomial operator *(const polynomial &a, const polynomial &b) {

	Long n = 1;
	vector<Field> fa(a.begin(), a.end());
	vector<Field> fb(b.begin(), b.end());
	
	while(n < a.size() + b.size()){
		n <<= 1;
	}
	fa.resize(n);
	fb.resize(n);
	
	Field wn(fastPow(root , (MOD - 1) / n));
	
	ntt(fa, false , wn );
	ntt(fb, false, wn );
	
	for(Long i = 0; i < n; i++){
		fa[i] *= fb[i];
	}
	wn = Field(fastPow(rootInv , (MOD - 1) / n));
	ntt(fa, true, wn );
	
	polynomial ans((Long)a.size() + (Long)b.size() - 1);
	for(Long i = 0; i < ans.size(); i++){
		ans[i] = fa[i].num;
	}
	return ans;
} 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T;
	cin >> T;
	REP(t, T){
		Long n;
		cin >> n;
		polynomial a(n + 1);
		polynomial b(n + 1);
		REP(i , n + 1){
			cin >> a[i];
		}
		REP(i , n + 1){
			cin >> b[i];
		}
		polynomial c = a * b;
		REP(i , 2 * n + 1){
			cout << c[i] << " ";
		}
		cout << endl;
	}
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long INF = 1e18;

struct Fraction {	
	Long num, den;
	Fraction(){
	}
	Fraction(Long n, Long d) {
		if(d == 0) {
			if(n > 0){
				num = INF;
			} else {
				num = -INF;
			}
			den = 1;
		} else {
			if(d < 0) {
				n *= -1;
				d *= -1;
			}
			num = n;
			den = d;
		}
	}
	
	void normalize() {
		if(num == 0 && den == 0) return;
		Long g = __gcd(abs(num) , abs(den));
		num /= g;
		den /= g;
	}
	
	Fraction operator + (const Fraction &F) const{
		Long g = __gcd(den , F.den);	
		return Fraction(num * (F.den / g) + F.num * (den / g), den * (F.den / g));
	}
	
	Fraction operator - (const Fraction &F) const{
		Long g = __gcd(den , F.den);
		return Fraction(num * (F.den / g) - F.num * (den / g), den * (F.den / g));
	}
	
	Fraction operator * (const Fraction &F) const{
		return Fraction(num * F.num , den * F.den);
	}
	
	Fraction operator / (const Fraction &F) const {
		return Fraction(num * F.den , den * F.num);
	}
	
	bool operator == (const Fraction &F) const {
		return num * F.den == F.num * den;
	}
	
	bool operator != (const Fraction &F) const {
		return !(*this == F);
	}
	
	bool operator < (const Fraction &F) const {
		return num * F.den < den * F.num;
	}
	
	bool operator <= (const Fraction &F) const {
		return *this < F || *this == F; 
	}
	
	bool operator >= (const Fraction &F) const {
		return *this > F || *this == F; 
	}
	
	bool operator > (const Fraction &F) const {
		return num * F.den > den * F.num;
	
	}
	
	long double getVal() {
		return 1.0 * num / den;
	}
	
	void debugFraction(string nombre) {
		cout << nombre << " = " << num << " / " << den << endl;
	}
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

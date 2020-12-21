#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

void eraseTrailing(deque<Long> &v){
	while(v.size() > 1 && v[0] == 0){
		v.pop_front();
	}
}

struct Big{
	deque<Long> digits;
	Long sgn;
	
	Big(){
		digits.pb(0);
		sgn = 1;
	}
	
	Big(Long x){
		if(x >= 0) {
			sgn = 1;
		} else {
			sgn = -1;
		}
		x = abs(x);
		if(x == 0){
			digits = {0};
		} else {
			while(x > 0){
				digits.push_front(x % 10);
				x /= 10;
			}
		}
	}
	
	Big(deque<Long> v , Long s = 1){
		deque<Long> transf;
		Long i = 0;
		while(i < v.size() && v[i] == 0){
			i++;
		}
		while(i < v.size()){
			transf.pb(v[i]);
			i++;
		}
		if(transf.size() == 0){
			transf.pb(0);   
		}
		if(transf.size()==1 && transf[0] == 0) {
			s = 1;
		}
		digits = transf;
		sgn = s;
	}

	bool operator == (const Big &P) const{
		return P.digits == digits && sgn == P.sgn;
	}
	
	bool operator < (const Big &P) const{
		if(P.sgn != sgn){
			return P.sgn == 1;
		}
		if(P.digits.size() != digits.size()){
			return digits.size() < P.digits.size();
		}
		for(Long i = 0; i < digits.size(); i++){
			if(digits[i] != P.digits[i]){
				return digits[i] < P.digits[i];
			}
		}
		return false;
	}
	
	bool operator > (const Big &P) const{
		if(P.sgn != sgn){
			return sgn == 1;
		}
		if(P.digits.size() != digits.size()){
			return digits.size() > P.digits.size();
		}
		for(Long i = 0; i < digits.size(); i++){
			if(digits[i] != P.digits[i]){
				return digits[i] > P.digits[i];
			}
		}
		return false;
	}
	
	
	friend ostream & operator << (ostream &out, const Big &c);
	
	friend Big operator +(const Big &other);
	friend Big operator -(const Big &x);
	
	Big operator +(const Big &other) const {
		deque<Long> ans;
		deque<Long> a = digits;
		deque<Long> b = other.digits;
		if(sgn * other.sgn == -1){
			if(sgn == -1){
				return other - Big(digits , 1);
			} else {
				return (*this) - Big(other.digits, 1);
			}
			
		}

		Long carry = 0;
		Long i = (Long)a.size( ) - 1, j = (Long)b.size() - 1;
		while(i >= 0 || j >= 0 || carry > 0){
			Long x , y;
			if(i >= 0) x = a[i];
			else x = 0;
	
			if(j >= 0) y = b[j];
			else y = 0;
			
			Long sum = x + y  + carry;
			carry = sum >= 10;
			if(carry) sum -= 10;
			ans.push_front(sum);
			i--;
			j--;
		}
		return Big(ans , sgn);
	}
	
	Big operator -(const Big &other) const {
		if(sgn * other.sgn == -1){
			if(sgn == 1){
				return (*this) + Big(other.digits , 1);
			} else {
				Big ans = Big(digits, 1) + Big(other.digits, 1);
				ans.sgn = -1;
				return ans;
			}
		}
		deque<Long> ans;
		deque<Long> a = digits;
		deque<Long> b = other.digits;
		Long newSgn = sgn;
		if(Big(a) < Big(b)) {
			newSgn = -other.sgn;
			
			swap(a , b);
		}
		
		Long i = (Long)a.size() - 1, j = (Long)b.size() - 1;
		
		while(i >= 0 && j >= 0){
			Long subs = a[i] - b[j] ;
		
			if( subs < 0){
				subs += 10;
				Long k = i - 1;
				while(a[k] == 0){
					a[k] = 9;
					k--;
				}
				a[k]--;
			}
			ans.push_front(subs);
			i--;
			j--;
		}
		Long k = 0;
		while(k <= i && a[k] == 0) {
			k++;
		}
		for(Long j = i; j >= k; j--){
			ans.push_front(a[j]);
		}
		return Big(ans , newSgn);
	}
	
	Big operator *(const Big &b) const {
		Big a = *this;
		Big ans;
		Long n = a.digits.size();
		Long m = b.digits.size();
		ans.digits.resize(n + m - 1 , 0);
		
		for(Long i = n - 1; i >= 0; i--){
			Long carry = 0;
			for(Long j = m - 1; j >= 0; j--){
				ans.digits[i + j] += a.digits[i] * b.digits[j] ;
			}
		}
		for(Long i = (Long)ans.digits.size() - 1; i >= 1; i--){
			Long carry = ans.digits[i] / 10;
			if(carry > 0) {
				ans.digits[i - 1] += carry;
				ans.digits[i] %= 10;
			}
		}
		while(ans.digits[0] >= 10){
			Long carry = ans.digits[0] / 10;
			ans.digits[0] %= 10;
			ans.digits.push_front(carry);
			
		}
		eraseTrailing(ans.digits);
		ans.sgn = sgn * b.sgn;
		if(ans.digits.size() == 1 && ans.digits[0] == 0){
			ans.sgn = 1;
		}
		return ans;
	}
};



string toString (const Big &number){
	string s = "";
	if(number.sgn == -1){
		s += "-";
	}
	for(Long i = 0; i < number.digits.size(); i++){
		s+= number.digits[i] + '0';
	}
	return s;
}

string toString(Long x){
	string s = "";
	if(x == 0) return "0";
	
	Long aux = abs(x);
	while(aux > 0){
		char c = (aux % 10) + '0';
		aux /= 10;
		s += c;
	}
	if(x < 0) s += "-";
	reverse(s.begin(), s.end());
	return s;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long T = 100000;
	REP(t , T){
		Long a = random(-100, 100);
		Long b = random(-100, 100);
		string x = toString(a - b);
		string y = toString(Big(a) - Big(b));
		if(x != y){
			debug(a);
			debug(b);
			debug(x);
			debug(y);
			system("pause");
		}
	}
	return 0;
}

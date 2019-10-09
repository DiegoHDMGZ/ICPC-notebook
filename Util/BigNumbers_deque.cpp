#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
 
using namespace std;
 
typedef long long Long;
 
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
	
	Big operator +(const Big &x) const {
		deque<Long> ans;
		deque<Long> a = digits;
		deque<Long> b = x.digits;
		if(sgn * x.sgn == 1){
			Long carry = 0;
			Long i = (Long)a.size( ) - 1, j = (Long)b.size() - 1;
			
			while(i >= 0 && j >= 0){
				Long sum = a[i] + b[j]  + carry;
				carry = 0;
				if( sum >= 10){
					carry = 1;
					sum = sum % 10;
				}
				ans.push_front(sum);
				i--;
				j--;
			}
			
			if( i >= 0 ){
				for(Long k = i; k >= 0 ; k--){
					Long sum = a[k] + carry;
					carry = 0;
					if( sum >= 10){
						carry = 1;
						sum = sum % 10;
					}
					ans.push_front(sum);
				}
			}
			else{
				for(Long k = j ; k >= 0; k--){
					Long sum = b[k] + carry;
					
					carry = 0;
					
					if( sum >= 10){
						carry = 1;
						sum = sum % 10;
					}
					ans.push_front(sum);
				}
			}
			
			if( carry > 0 ){
				ans.push_front(1);
			}
			return Big(ans , sgn);
		} 

		Long newSgn = sgn;
		if(Big(a) < Big(b)) {
			swap(a , b);
			newSgn = x.sgn;
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
	
	Big operator -(const Big &x) const {
		Big aux = x;
		if(aux.digits.size() > 1 || aux.digits[0] != 0){
			aux.sgn *= -1;
		}
		
		return (*this) + aux;
	}
	
	Big operator *(const Long &c) const {
		if(c == 0){
			return Big(0);
		}
		
		if(c == 1){
			return Big(digits);
		}
		
		deque<Long> ans;
		Long carry = 0;
		
		for(Long i = digits.size() - 1; i >=0; i--){
			Long mult = digits[i] * c + carry;
			
			carry = 0;
			
			if(mult >= 10){
				carry = mult / 10;
				mult = mult % 10;
			}
			
			ans.push_front(mult);
		}
		
		if(carry > 0){
			ans.push_front(carry);
		}
		return Big(ans);
	}

	void mult10(Big &num, Long pot){
		for(Long i = 0; i < pot; i++){
			num.digits.push_back(0);
		}
	}
	
	Big operator *(const Big &b) const {
		Big ans(0);
		Big a = *this;
		
		for(Long i = b.digits.size() - 1; i >= 0; i--){
			Long pot = (Long)b.digits.size() - i - 1;
			Big aux = a * b.digits[i];
			for(Long i = 0; i < pot; i++){
				aux.digits.pb(0);
			}
			ans = ans + aux;
		}
		ans.sgn = sgn * b.sgn;
		if(ans.digits.size() == 1 && ans.digits[0] == 0){
			ans.sgn = 1;
		}
		return ans;
	}


};


ostream & operator << (ostream &out, const Big &number)
{
	if(number.sgn == -1){
		cout << "-";
	}
	for(Long i = 0; i < number.digits.size(); i++){
		out << number.digits[i];
	}
    return out;
}
 
int main() {
	Long a ,b;
	cin >> a >> b;
	cout << Big(a) + Big(b) << endl;
	cout << Big(a) * Big(b) << endl;
	return 0;
}

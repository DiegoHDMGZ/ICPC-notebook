#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;

void debugDeque( deque<Long> d){
	for(Long i = 0; i < d.size() ; i++){
		cout << d[i];
	}
	cout << endl;
}

deque<Long> suma(deque<Long> a, deque<Long> b){ //O( max (|a| , |b| )  )
	Long carry = 0;
	deque<Long>  resultado;
	Long i = a.size( ) - 1, j = b.size() - 1;
	
	while(i >= 0 && j >= 0){
		Long suma = a[i] + b[j]  + carry;
		carry = 0;
		if( suma >= 10){
			carry = 1;
			suma = suma % 10;
		}
		resultado.push_front(suma);
		i--;
		j--;
	}
	
	if( i >= 0 ){
		for(Long k = i; k >= 0 ; k--){
			Long suma = a[k] + carry;
			carry = 0;
			if( suma >= 10){
				carry = 1;
				suma = suma % 10;
			}
			resultado.push_front(suma);
		}
	}
	else{
		for(Long k = j ; k >= 0; k--){
			Long suma = b[k] + carry;
			
			carry = 0;
			
			if( suma >= 10){
				carry = 1;
				suma = suma % 10;
			}
			resultado.push_front(suma);
		}
	}
	
	if( carry > 0 ){
		resultado.push_front(1);
	}
	return resultado;
}

deque<Long> multUnDigito(deque<Long> a, Long c){
	if(c == 0){
		deque<Long> resp;
		resp.push_front(0);
		return resp;
	}
	
	if(c == 1){
		return a;
	}
	
	deque<Long> resultado;
	Long carry = 0;
	
	for(Long i = a.size() - 1; i >=0; i--){
		Long mult = a[i] * c + carry;
		
		carry = 0;
		
		if(mult >= 10){
			carry = mult / 10;
			mult = mult % 10;
		}
		
		resultado.push_front(mult);
	}
	
	if(carry > 0){
		resultado.push_front(carry);
	}
	return resultado;
}

deque<Long> mult10(deque<Long> num, Long pot){
	for(Long i = 0; i < pot; i++){
		num.push_back(0);
	}
	return num;
}

deque<Long> mult(deque<Long> a, deque<Long> b){
	deque<Long> resultado;
	
	for(Long i = b.size() - 1; i >= 0; i--){
		Long pot = b.size() - i - 1;
		deque<Long> auxiliar = multUnDigito(a , b[i]);
		auxiliar = mult10(auxiliar, pot);
		resultado = suma(resultado, auxiliar);
	}
	
	return resultado;
}

int main() {
	return 0;
}

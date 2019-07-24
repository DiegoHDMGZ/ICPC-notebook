#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

string llenarConCeros(string a, int n){
	string cero = "";
	for(int i = 0; i < n ; i++){
		cero += '0';
	}
	return cero + a;
}

string suma(string a, string b){
	if( a.size() > b.size() ){
		b = llenarConCeros(b, a.size() - b.size() );
	}
	else if( a.size() < b.size() ){
		a = llenarConCeros(a, b.size() - a.size() );
	}
	
	if(a.size() != b.size()){
		cout << "BUG" << endl;
	}
	
	int llevo = 0;
	
	string resultado = "";
	for(int i = a.size() - 1; i >= 0; i-- ){
		int suma = (a[i] - '0') + ( b[i] - '0') + llevo;
		
		llevo = 0;
		
		if( suma >= 10){
			llevo = 1;
			suma = suma % 10;
		}
		resultado += char(suma + '0');
	}
	
	if( llevo > 0 ){
		resultado += '1';
	}
	
	reverse(resultado.begin(), resultado.end());
	
	return resultado;
}

string multUnDigito(string a, char c){
	if(c == '0'){
		return "0";
	}
	
	if(c == '1'){
		return a;
	}
	
	string resultado = "";
	int llevo = 0;
	
	for(int i = a.size() - 1; i >=0; i--){
		int mult = (a[i] - '0') * (c - '0') + llevo;
		llevo = 0;
		if(mult >= 10){
			llevo = mult / 10;
			mult = mult % 10;
		}
		resultado += char(mult + '0' );
	}
	
	if(llevo > 0){
		resultado += char(llevo + '0');
	}
	
	reverse(resultado.begin(), resultado.end());
	
	return resultado;
}

string mult10(string num, int pot){
	if(num == "0") {
		return "0";
	}
	
	string cero = "";
	
	for(int i = 0; i < pot; i++){
		cero += '0';
	}
	
	return num + cero;
}

string mult(string a, string b){
	string resultado = "";
	
	for(int i = b.size() - 1; i >= 0; i--){
		int pot = b.size() - i - 1;
		string auxiliar = multUnDigito(a , b[i]);
		auxiliar = mult10(auxiliar, pot);
		resultado = suma(resultado, auxiliar);
	}
	
	return resultado;
}

int main() {
	return 0;
}

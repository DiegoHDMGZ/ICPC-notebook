#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5;
vector<Long> b(MX); //b[i] es la longitud del borde más grande en la subcadena s[0...i]

void prefixFunction(string s){ //O(n)
	Long n = s.size();
	
	for(Long i = 1; i < n; i++){
		Long bordeAnterior = b[i-1];
		while(bordeAnterior >0 && s[i] != s[bordeAnterior]/*el que le sigue al borde*/ ){
			bordeAnterior = b[bordeAnterior-1];
		}
		
		if(s[i] == s[bordeAnterior]){
			bordeAnterior++;
		}
		
		b[i] = bordeAnterior;
	}
}

vector<Long> ans; //posiciones de la cadena en donde empieza una ocurrencia de un patrón

void kmp(string p, string t){ //O(n+m)
//determina si el patron p aparece en t y enumera las posiciones de ocurrencia
	Long n = p.size();
	Long m = t.size();
	
	string s = p + "#" + t;
	
	for(Long i = 1; i < (Long)s.size();i++){
		Long j = b[i-1];
		while(j > 0 && s[i] != s[j]){
			j = b[j-1];
		}
		
		if(s[i] == s[j]){
			j++;
		}
		
		b[i] = j;
		
		if(b[i] == n){
			ans.push_back(i- (n+1)-n+1);
		}
	}	
}

int main(){

	return 0;
}



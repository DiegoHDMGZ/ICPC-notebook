#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long double Double;

const Double ERROR = 1e-6;

Double f(double x){
	return x*x;
}

bool check(Double med, Double x ){
	return f(med)>=x;
}

Double search ( Double ini, Double fin, Double x){
	//precision de 10^(-6)
	
	while(fin - ini > ERROR){ //REP(i,1000)
		Double med= ( ini + fin ) / 2.0;
		
		if(check( med , x)) fin = med;
		else ini = med;
	}
	
	return fin;
}

int main(){
	return 0;
}


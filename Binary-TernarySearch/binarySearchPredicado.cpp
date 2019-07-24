#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long Long;

const Long MAX = 100000;
Long A[MAX];

bool check( Long med , Long x){
	return A[ med ] >= x;
}

Long search(  Long ini , Long fin , Long x){ //O(logn)
	// F F F... V V V
	if(!check(fin,x)) return -1; //todos F
	if(check(ini,x)) return ini; //todos V
	
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= (ini + fin) / 2;
		
		if(check( med, x )){
			fin=med;
		} 
		else {
			ini = med;
		}
	}

	//hay 2 valores ini es F y fin es V
	return fin;
}

int main(){
	return 0;
}

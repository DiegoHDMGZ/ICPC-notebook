#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long Long;


bool check( Long med ){
	return true;
}

Long search(  Long ini , Long fin ){ //O(logn)
	// F F F... V V V
	if(!check(fin)) return -1; //todos F
	if(check(ini)) return ini; //todos V
	
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= ini + (fin - ini) / 2;
		
		if(check( med )){
			fin = med;
		} 
		else {
			ini = med;
		}
	}

	//hay 2 valores ini es F y fin es V
	return fin;
}

/*Long search(  Long ini , Long fin ){ //O(logn)
	// V V V ... F F F
	if(check(fin)) return fin; //todos V
	if(!check(ini)) return -1; //todos F
	
	while(fin - ini > 1){ // hay mas de 2 valores
		Long med= ini + (fin - ini) / 2;
		
		if(check( med )){
			ini = med;
		} 
		else {
			fin = med;
		}
	}

	//hay 2 valores ini es V y fin es F
	return ini;
}*/

int main(){
	return 0;
}

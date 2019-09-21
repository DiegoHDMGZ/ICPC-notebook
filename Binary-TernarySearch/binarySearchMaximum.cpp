#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5;
Long A[MX];

Long f(Long med){
	return A[med];
}

bool check( Long med ){
	return f(med + 1) - f(med ) <= 0;
}

Long search(  Long ini , Long fin ){ //O(logn)
	// F F F... V V V
	if(!check(fin - 1)) return f(fin); //todos F
	if(check(ini)) return f(ini); //todos V
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
	return f(fin);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Long n;
	cin >> n;
	REP(i , n){
		cin >> A[i];
	}
	cout << search(0 , n - 1) << endl;
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5;
Long A[MX];

Long f(Long i){
	return A[i];
}

Long ternarySearch(Long ini, Long fin){ //O(log x)
	while(fin - ini > 2){
		Long m1 = ini + (fin-ini)/3;
		Long m2 = fin - (fin-ini)/3;
		if(f(m1) < f(m2)){ //si piden minimo se invierte
			ini = m1;
		}
		else{
			fin = m2;
		}
	}
	Long maxi = f(ini); 
	for(int i = ini; i <= fin; i++){
		maxi = max(maxi,f(i)); //si piden minimo se cambia
	}
	return maxi;
}

int main() {
	Long n;
	cin >> n;
	REP(i,n) cin >> A[i];
	
	cout << ternarySearch(0,n - 1) << endl;
	
	return 0;
}

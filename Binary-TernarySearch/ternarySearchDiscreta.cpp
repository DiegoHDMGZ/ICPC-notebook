#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
#define MAX 100000

using namespace std;

typedef long long Long;

Long n,m;

Long A[MAX],B[MAX];

Long f(Long fijo){
	Long cont = 0;
	
	REP(i,n){
		cont += max(0LL,fijo-A[i]);
	}
	
	REP(i,m){
		cont += max(0LL,B[i]-fijo);
	}
	return cont;
}

Long ternarySearch(Long ini, Long fin){ //O(log x * O(f))
	while(fin - ini > 2){
		Long m1 = ini + (fin-ini)/3;
		Long m2 = fin - (fin-ini)/3;
		if(f(m1) > f(m2)){
			ini = m1;
		}
		else{
			fin = m2;
		}
	}
	
	Long mini = f(ini);
	for(int i = ini; i <= fin; i++){
		mini = min(mini,f(i));
	}
	
	return mini;
}

int main() {
	cin >> n >> m;
	REP(i,n) cin >> A[i];
	REP(i,m) cin >> B[i];
	
	cout << ternarySearch(1,1e9) << endl;
	
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;

typedef long long Long;
typedef long double Double;
const Long MAX = 3000;
const Double ERROR = 1e-6;

Double f(Double x){
    return 3*x*x - 5 *x+7;
}

Double ternarySearch(Double ini, Double fin){ //O(log x)
	
    while(abs(fin-ini) > ERROR){
        Double m1 = ini + (fin-ini)/3.0;
        Double m2 = fin - (fin-ini)/3.0;
	
        if(f(m1) < f(m2)){ //si piden maximo se invierte
            fin = m2; 
        }
        else{
            ini= m1;
        }
    }
    
    return f((ini+fin)/2.0);
}

int main(){
    cout << fixed << setprecision(6) << ternarySearch(-200000,200000) << endl;
}

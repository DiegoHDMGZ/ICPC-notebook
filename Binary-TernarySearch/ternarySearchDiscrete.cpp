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

Long ternarySearch(Long low, Long high){ //O(log n)
	while(high - low > 2){
		Long m1 = low + (high-low)/3;
		Long m2 = high - (high-low)/3;
		if(f(m1) < f(m2)){ //if minimum is needed, change to >
			low = m1;
		}
		else{
			high = m2;
		}
	}
	Long maxi = f(low); 
	for(Long i = low; i <= high; i++){
		maxi = max(maxi,f(i)); //if minimum is needed, change to min
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

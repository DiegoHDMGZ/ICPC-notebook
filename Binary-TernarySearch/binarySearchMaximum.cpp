#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

const Long MX = 1e5;
Long A[MX];

Long f(Long mid) {
	return A[mid];
}

bool check(Long mid) {
	return f(mid + 1) - f(mid) <= 0;
}

Long search(Long low, Long high) { //O(logn)
	// F F F... V V V
	if(!check(high - 1)) return f(high); //all F
	if(check(low)) return f(low); //all V
	while (high - low > 1) { 
		Long mid = low + (high - low) / 2;
		if (check(mid)) high = mid;
		else low = mid;
	}
	//2 values low -> F and high -> V
	return f(high);
}

int main(){
	return 0;
}

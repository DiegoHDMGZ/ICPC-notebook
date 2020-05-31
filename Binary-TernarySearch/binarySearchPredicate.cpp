#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long Long;

bool check( Long mid ){
	return true;
}

Long search(  Long low , Long high ){ //O(logn)
	// F F F... V V V
	if(!check(high)) return -1; //all F
	if(check(low)) return low; //all V
	
	while(high - low > 1){
		Long mid= low + (high - low) / 2;
		
		if(check( mid )){
			high = mid;
		} 
		else {
			low = mid;
		}
	}

	//2 values low -> F and high->V
	return high;
}

/*Long search(  Long low , Long high ){ //O(logn)
	// V V V ... F F F
	if(check(high)) return high; //all V
	if(!check(low)) return -1; //all F
	
	while(high - low > 1){ 
		Long mid= low + (high - low) / 2;
		
		if(check( mid )){
			low = mid;
		} 
		else {
			high = mid;
		}
	}
	//2 values low -> V and high-> F
	return low;
}*/

int main(){
	return 0;
}

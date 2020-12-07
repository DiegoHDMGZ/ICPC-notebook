#include <bits/stdc++.h>
#define REP(i , n) for(Long i = 0; i < (Long)n; i++)
#define debug(x) cout << #x << " = " << x << endl;
#define pb push_back

using namespace std;
 
typedef long long Long;

Long mult(Long a, Long b, Long mod){
	return (a * b) % mod;
}
 
Long add(Long a, Long b, Long mod){
	return (a + b) % mod;
}
 
Long sub(Long a , Long b, Long mod){
	return (a - b + mod) % mod;
}

Long minChar = (Long)'0';

const Long MX = 1e6;
struct Hashing{
	Long MOD;
	Long BASE;
	Long pot[MX];
	Long hPref[MX];
	Long hSuf[MX];
	
	Hashing() { 
		MOD = 1e9 + 7; //1e9 + 1269
		BASE = 67;
	}
	
	void setData(Long b, Long mod) {
		BASE = b;
		MOD = mod;
	}
	
	Long hash(Long i, Long j) { //O(1)
		if(i == 0) return hPref[j];
		return sub(hPref[j] , mult(hPref[i - 1] , pot[j - i + 1], MOD) , MOD);
	}

	Long hashInverse(Long i, Long j) { //O(1)
		return sub(hSuf[i] , mult(hSuf[j + 1] , pot[j - i + 1], MOD) , MOD);
	}
	
	bool isPalindrome(Long i, Long j) { //O(1)
		return hash(i , j) == hashInverse(i , j);
	}

	void precalc() {
		pot[0] = 1;
		for (int i = 1; i < MX; i++) {
			pot[i] = mult(pot[i - 1] , BASE , MOD);
		}
	}

	void precalc(string &s) { //O(size)
		Long sz = s.size();
		hPref[0] = s[0] - minChar + 1;
		for (int i = 1; i < sz; i++) {
			hPref[i] = add( mult(hPref[i - 1] , BASE, MOD) , s[i] - minChar + 1, MOD);
		}
		hSuf[sz] = 0;
		hSuf[sz - 1] = s[sz - 1]- minChar + 1;
		for (int i = sz - 2; i >= 0; i--) {
			hSuf[i] = add(mult( hSuf[i + 1] , BASE, MOD) ,  s[i] - minChar + 1 , MOD);
		}
	}
}hs;
 
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);

	
	return 0;
}

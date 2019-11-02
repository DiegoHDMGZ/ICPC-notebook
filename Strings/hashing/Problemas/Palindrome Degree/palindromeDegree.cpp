#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

//https://codeforces.com/contest/7/problem/D

Long mult(Long a, Long b, Long mod){
	return (a * b) % mod;
}
 
Long add(Long a, Long b, Long mod){
	return (a + b) % mod;
}
 
Long subs(Long a , Long b, Long mod){
	return (a - b + mod) % mod;
}

const Long MX = 5e6 + 2;
struct Hashing{
	Long MOD;
	Long B;
	Long minChar;

	int pot[MX];
	int hPref[MX];
	int hSuf[MX];
	
	Hashing(){
		MOD = 1e9 + 7;
		B = 67;
		minChar = (Long)'0';
	}
	
	void setData(Long b, Long mod){
		B = b;
		MOD = mod;
	}
	
	Long hSub(Long i, Long j){ //O(1)
		if(i == 0) return hPref[j];
		return subs(hPref[j] , mult(hPref[i - 1] , pot[j - i + 1], MOD) , MOD);
	}

	Long hSub2(Long i, Long j){ //O(1)
		return subs(hSuf[i] , mult(hSuf[j + 1] , pot[j - i + 1], MOD) , MOD);
	}


	bool isPalindrome(Long i, Long j){ //O(1)
		return hSub(i , j) == hSub2(i , j);
	}

	void precalc(){
		pot[0]= 1;
		for(int i = 1; i<MX;i++){
			pot[i] = mult(pot[i - 1] , B , MOD);
		}
	}

	void precalc(string &s){ //O(size)
		Long sz = s.size();
		hPref[0] = s[0] - minChar + 1;
		for(int i = 1; i < s.size(); i++){
			hPref[i] = add( mult(hPref[i - 1] , B, MOD) , s[i] - minChar + 1, MOD);
		}
		
		hSuf[sz] = 0;
		hSuf[sz-1] = s[sz - 1]- minChar + 1;
		for(int i = s.size()-2; i>=0; i--){
			hSuf[i] = add(mult( hSuf[i + 1] , B, MOD) ,  s[i] - minChar + 1 , MOD);
		}
	}
}hs1 , hs2;

Long dp[MX];
bool used[MX];

Long kPalindrome(Long endPos){
	if(used[endPos]){
		return dp[endPos];
	}
	used[endPos] = true;
	Long i = 0;
	Long j = endPos;
	Long limInf = (j - i - 1) / 2;
	Long limSup = (j - i + 1) % 2 == 0 ? limInf + 1 : limInf + 2;
	
	if(!hs1.isPalindrome(0 , endPos) || !hs2.isPalindrome(0 , endPos)) {
		return dp[endPos] = 0;
	}
	
	Long nextPos = (endPos - 1 ) / 2;
	
	return dp[endPos] = 1 + kPalindrome(nextPos);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string s;
	cin >> s;
	hs2.setData(67 , 1e9 + 1269);
	hs1.precalc();
	hs1.precalc(s);
	hs2.precalc();
	hs2.precalc(s);
	
	Long ans = 0;
	REP(i , s.size()){
		ans += kPalindrome(i);
	}
	cout << ans << endl;
	return 0;
}

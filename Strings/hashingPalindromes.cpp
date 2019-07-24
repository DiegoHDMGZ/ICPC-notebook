#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

using namespace std;
typedef long long Long;

const Long MAX = 5000000;
Long B = 67; //Utilizamos el caso extremo en que se trabajo con digitos, letras ( minus y mayus)
//en caso se quiera restringir, cambiar en todos los hashing 
Long mod = 1e9+7;
Long pot[MAX];
Long hPref[MAX];
Long hSuf[MAX];
Long minChar = (Long)('0');

Long hSub(Long i, Long j){ //O(1)
	if(i == 0) return hPref[j];
	
	return ( hPref[j] - (hPref[i - 1] * pot[j - i + 1] ) % mod+mod)%mod;
}

Long hSub2(Long i, Long j){ //O(1)
	return (hSuf[i] - (hSuf[ j + 1] * pot[ j - i + 1] ) % mod+mod)%mod;
}


bool isPalindrome(Long i, Long j){ //O(1)
	return hSub(i , j) == hSub2(i , j);
}

void precalc(){
	pot[0]= 1;
	for(int i = 1; i<MAX;i++){
		pot[i] = (pot[i-1]*B)%mod;
	}
}

void precalc(string &s){ //O(size)
	Long sz = s.size();
	
	hPref[0] = s[0] - minChar + 1;
    for(int i = 1; i < s.size(); i++){
    	hPref[i] = ( (hPref[i - 1] * B) % mod + (s[i] - minChar + 1)) %mod;
	}
	
	hSuf[sz] = 0;
	hSuf[sz-1] = s[sz - 1]- minChar + 1;
	
	for(int i = s.size()-2; i>=0; i--){
		hSuf[i] = ( (hSuf[i + 1] * B ) % mod + ( s[i] - minChar + 1) ) %mod;
	}
}

int main(){
	precalc();
	string s;
	cin >> s;
	precalc(s);
	while(true){
		Long i,j;
		cin >> i >> j;
		if(isPalindrome(i,j)){
			cout << "palindroma" << endl;
		}
		else{
			cout << "no es palindroma" << endl;
		}
	}

	return 0;
}

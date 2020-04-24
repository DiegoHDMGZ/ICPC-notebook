#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i , n) for(Long i = 0; i < (Long)n ; i++)
#define pb push_back

using namespace std;

typedef long long Long;

//https://www.codechef.com/AUG19A/problems/ENCODING

const Long MAX = 1e5 + 5;
Long pot10[MAX];
const Long MOD = 1e9 + 7;

Long add(Long a , Long b){
	return (a + b) % MOD;
}

Long mult(Long a, Long b){
	return (a * b) % MOD;	
}

Long subs(Long a, Long b){
	return (a - b + MOD) % MOD;
}


Long dp2[MAX][2];
bool used2[MAX][2];

string s;

Long cnt(Long pos, bool lower){
	if(pos >= s.size()){
		return 1;
	}
	if(used2[pos][lower]){
		return dp2[pos][lower];
	}
	used2[pos][lower] = true;
	
	Long ans = 0;
	Long d = s[pos] - '0';
	
	if(lower){
		d = 10;
	} 
	for(Long i = 0; i < d; i++){
		ans = add(ans , cnt(pos + 1 , true));
	}
	if(!lower){
		ans = add(ans , cnt(pos + 1 , false));
	}
	return dp2[pos][lower] = ans;
}

Long dp[MAX][2][11];
bool used[MAX][2][11];

Long f(Long pos = 0, bool lower = false, Long ant = 10){
	if(pos == s.size()){
		return 0;
	}
	if(used[pos][lower][ant]){
		return dp[pos][lower][ant];
	}
	used[pos][lower][ant] = true;
	
	Long ans = 0;
	
	Long d = s[pos] - '0';
	if(lower){
		d = 10;
	}
	Long p = (Long) s.size() - pos - 1;
	for(Long i = 0; i < d; i++){
		if(i != ant){
			ans = add(ans , mult( mult(pot10[p] , i), cnt(pos + 1, true) )) ;
		}
		ans = add(ans , f(pos + 1 , true , i));
	}
	if(!lower){
		if(d != ant){
			ans = add(ans , mult(mult (pot10[p] , d) , cnt(pos + 1 , false) ) );
		}
		ans = add(ans , f(pos + 1, false , d));
	}
	
	return dp[pos][lower][ant] = ans;
	
}

void prePow(){
	pot10[0] = 1;
	for(Long i = 1; i < MAX; i++){
		pot10[i] = mult(pot10[i - 1] , 10);
	}
}

void clear(){
	REP(i , MAX){
		REP(j , 2){
			REP(k , 11){
				used[i][j][k] = false;
			}
			used2[i][j] = false;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	prePow();
	
	Long T;
	cin >> T;
	REP(q , T){
		Long x;
		string L;
		cin >> x >> L;
	
		Long y ;
		string R;
		cin >> y >> R;
		
		clear();
		s = R;
		

		Long ans = f();
		
		clear();
		
		s = "";
		Long sz = L.size();
		Long i = sz - 1;
		
		while(L[i] == '0'){
			s = "9" + s;
			i--;
		}
		if(! (i == 0 && L[i] == '1' )){
			Long d = L[i] - '0';
			d--;
			char c = '0' + d;
			s = c + s;
			
			i--;
			while(i >= 0){
				s = L[i] + s;
				i--;
			}
		}
		

		ans = subs(ans , f());	
		cout << ans << endl;
	}
	return 0;
}

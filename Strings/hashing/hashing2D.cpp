#include <bits/stdc++.h>
#define REP(i , n) for(Long i = 0; i < (Long)n; i++)
#define debug(x) cout << #x << " = " << x << endl;
#define pb push_back

using namespace std;

//incompleto
 
typedef long long Long;

Long mult(Long a, Long b, Long mod){
	return (a * b) % mod;
}
 
Long add(Long a, Long b, Long mod){
	return (a + b) % mod;
}
 
Long subs(Long a , Long b, Long mod){
	return (a - b + mod) % mod;
}

Long minChar = (Long)'0';

const Long MX = 1e3;

typedef vector<vector<char>> Matrix;
struct Hashing{
	Long MOD;
	Long B;

	Long pot[MX * MX];
	Long hPref[MX][MX];
	
	Hashing(){
		MOD = 1e9 + 7; //1e9 + 1269
		B = 67;
	}
	
	void setData(Long b, Long mod){
		B = b;
		MOD = mod;
	}
	
	Long hSub(Long x, Long y){
		if(x < 0 || y < 0) return 0;
		return hPref[x][y];
	}
	
	Long hSub(Long x1, Long y1, Long x2 , Long y2){ //O(1)
		Long ans = subs( hSub(x2 , y2) , hSub(x2, y1 - 1) , MOD); 
		ans = subs(ans , mult( hSub(x1 - 1 , y2) , pot[(x2 - x1 + 1) * (y2 - y1)], MOD) , MOD  );
		ans = add(ans , mult( hSub(x1 - 1 , y1 - 1) , pot[(x2 - x1 + 1) * y1] , MOD) , MOD);
		return ans;
	}

	void precalc(){
		pot[0]= 1;
		for(int i = 1; i<MX * MX;i++){
			pot[i] = mult(pot[i - 1] , B , MOD);
		}
	}

	void precalc(Matrix &A){ //O(size)
		Long n = A.size();
		Long m = A[0].size();
		REP(i , n) {
			Long acum = 0;
			REP(j , m){
				acum = add( mult(acum , B , MOD) , A[i][j] - minChar + 1 , MOD);
				
				hPref[i][j] = acum;
				if(i > 0) {
					hPref[i][j] = add(hPref[i][j] , mult(hPref[i - 1][j] , pot[j + 1] , MOD) , MOD);
				}
			}
		}
	}
}hs;
 
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);

	
	return 0;
}

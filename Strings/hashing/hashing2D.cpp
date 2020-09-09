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

const Long MX = 1e3;

typedef vector<vector<char>> Matrix;
struct Hashing{
	Long MOD;
	Long B;
 
	int pot[MX * MX];
	int hPref[MX][MX];
	
	Hashing(){
		MOD = 1e9 + 7; //1e9 + 1269
		B = 67;
	}
	
	void setData(Long b, Long mod){
		B = b;
		MOD = mod;
	}
	
	Long hSub(Long x, Long y){ //O(1)
		if(x < 0 || y < 0) return 0;
		return hPref[x][y];
	}
	
	Long hSub(Long x1, Long y1, Long x2 , Long y2){ //O(1)
		Long ans = hSub(x2 , y2);
		ans = sub(ans , mult(hSub(x2, y1 - 1) , pot[y2 - y1 + 1] , MOD)  , MOD); 
		ans = sub(ans , mult( hSub(x1 - 1 , y2) , pot[MX * (x2 - x1 + 1)], MOD) , MOD  );
		ans = add(ans , mult( hSub(x1 - 1 , y1 - 1) , pot[MX * (x2 - x1 + 1) + (y2 - y1 + 1)] , MOD) , MOD);
		return ans;
	}
 
	void precalc(){ //O(MX * MX)
		pot[0]= 1;
		for(int i = 1; i<MX * MX;i++){
			pot[i] = mult(pot[i - 1] , B , MOD);
		}
	}
 
	void precalc(Matrix &A){ //O(n * m)
		Long n = A.size();
		Long m = A[0].size();
		
		REP(i , n) {
			REP(j , m){
				
				hPref[i][j] = A[i][j] - minChar + 1;
				
				if(i > 0) {
					hPref[i][j] = add(hPref[i][j] , mult(hPref[i - 1][j] , pot[MX] , MOD) , MOD);
				}
				if(j > 0){
					hPref[i][j] = add(hPref[i][j] , mult(hPref[i][j - 1] , B, MOD) , MOD);
				}
				if(i > 0 && j > 0){
					hPref[i][j] = sub(hPref[i][j] , mult(mult(B , pot[MX] , MOD), hPref[i - 1][j - 1] , MOD) , MOD);
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

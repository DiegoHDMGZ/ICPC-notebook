#include <bits/stdc++.h>
#define REP(i , n) for(Long i = 0; i < (Long)n; i++)
#define debug(x) cout << #x << " = " << x << endl;
#define pb push_back
 
using namespace std;
 
typedef long long Long;

//https://codeforces.com/gym/100783
 
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
 
const Long MX = 2e3 + 20;
 
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
		ans = subs(ans , mult(hSub(x2, y1 - 1) , pot[y2 - y1 + 1] , MOD)  , MOD); 
		ans = subs(ans , mult( hSub(x1 - 1 , y2) , pot[MX * (x2 - x1 + 1)], MOD) , MOD  );
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
					hPref[i][j] = subs(hPref[i][j] , mult(mult(B , pot[MX] , MOD), hPref[i - 1][j - 1] , MOD) , MOD);
				}
			}
		}
	}
}hs11, hs12, hs21, hs22;
 
mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());
 
Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}
 
 
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n1 , m1 , n2 , m2;
	cin >> n1 >> m1 >> n2 >> m2;
	
	Long MOD1 = 1e9 + 7;
	Long MOD2 = 1e9 + 1269;
	Long B1 = random(3, MOD1 - 1);
	Long B2 = random(3, MOD2 - 1);
	hs11.setData( B1, MOD1 );
	hs12.setData(B2 , MOD2);
	hs21.setData(B1 , MOD1);
	hs22.setData(B2 , MOD2);
	
	hs11.precalc();
	hs12.precalc();
	hs21.precalc();
	hs22.precalc();
	
	
	
	
	Matrix A;
	REP(i , n1){
		vector<char> v;
		REP(j , m1){
			char c;
			cin >> c;
			if(c == 'x') v.pb('1');
			else v.pb('0');
		}
		cin.ignore();
		A.pb(v);
	}
	hs11.precalc(A);
	hs12.precalc(A);
	
	Matrix B;
	REP(i , n2){
		vector<char> v;
		REP(j , m2){
			char c;
			cin >> c;
			if(c == 'x') v.pb('1');
			else v.pb('0');
		}
		cin.ignore();
		B.pb(v);
	}
	hs21.precalc(B);
	hs22.precalc(B);
	
	Long ans = 0;
	for(Long i = 0; i + n1 - 1 < n2; i++){
		for(Long j = 0; j + m1 - 1 < m2; j++){
			if(hs11.hSub(0 , 0 , n1 - 1, m1 - 1) == hs21.hSub(i , j , i + n1 -1, j + m1 - 1) && hs12.hSub(0 , 0 , n1 - 1, m1 - 1) == hs22.hSub(i , j , i + n1 -1, j + m1 - 1) ){
				ans++;
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}

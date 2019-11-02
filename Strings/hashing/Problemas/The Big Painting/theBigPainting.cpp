#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
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

Long minChar = 0;

const Long MX = 1e3;

typedef vector<vector<char>> Matrix;
struct Hashing{
	Long MOD;
	Long B;

	Long pot[MX * MX];
	Long hPref[MX][MX];
	
	Hashing(){
		MOD = 1e9 + 7; //1e9 + 1269
		B = 13;
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
		Long ans = subs( hSub(x2 , y2) , mult( hSub(x2, y1 - 1) , pot[y2 - y1 + 1], MOD) , MOD); 
		ans = subs(ans , mult( hSub(x1 - 1 , y2) , pot[(x2 - x1 + 1) * y2], MOD) , MOD  );
		ans = add(ans , mult( hSub(x1 - 1 , y1 - 1) , pot[(y2 - y1 + 1) * (x2 - x1 + 1) * y2] , MOD) , MOD);
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
}hs11 , hs12 , hs21, hs22;
 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Long n1,m1,n2,m2;
	cin >> n1 >> m1 >> n2 >> m2;
	
	Matrix A;
	REP(i , n1){
		vector<char> v;
		REP(j , m1){
			char c;
			cin >> c;
			if(c == 'x') v.pb('0');
			else v.pb('1');
		}
		cin.ignore();
		A.pb(v);
	}
	
	
	Matrix B;
	REP(i , n2){
		vector<char> v;
		REP(j , m2){
			char c;
			cin >> c;
			if(c == 'x') v.pb('0');
			else v.pb('1');
		}
		cin.ignore();
		B.pb(v);
	}
	hs11.setData(13, 1e9 + 7);
	hs12.setData(7 ,1e9 + 1269 );
	
	hs21.setData(13, 1e9 + 7);
	hs22.setData(7 ,1e9 + 1269 );
	
	hs11.precalc();
	hs12.precalc( );
	hs21.precalc();
	hs22.precalc( );
	
	hs11.precalc(A);
	hs12.precalc(A);
	hs21.precalc(B);
	hs22.precalc(B);
	
	Long ans = 0;
	for(Long i = 0; i + n1 - 1 < B.size(); i++){
		for(Long j = 0; j + m1 - 1 < B[i].size(); j++){
			bool ok1 = false;
			if(hs21.hSub(i , j , i + n1 - 1, j + m1 - 1) == hs11.hSub(0, 0 , n1 - 1, m1 - 1) ){
				ok1 = true;
			}
			bool ok2 = false;
			if(hs22.hSub(i , j , i + n1 - 1, j + m1 - 1) == hs12.hSub(0, 0 , n1 - 1, m1 - 1) ){
				ok2 = true;
			}
			if(ok1 && ok2){
				ans++;
			}
		}
	}
	
	
	cout << ans << endl;
	

	return 0;
}

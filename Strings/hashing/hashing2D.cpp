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

const int MX = 1000;
struct Hash{
	Long mod, base;
	vector<Long> pot;
	vector<vector<Long>> hashPref;
	
	Hash(Long mod = 1e9 + 7 , Long base = 67) {
		//other mod 1e9 + 1269
		this->mod = mod;
		this->base = base;
		hashPref = vector<vector<Long>>(MX, vector<Long>(MX));
		pot = vector<Long>(MX * MX);
		pot[0] = 1;
		for (int i = 1; i < MX * MX; i++) {
			pot[i] = mult(pot[i - 1] , base , mod);
		}
	}
	
	Long hash(Long x, Long y){ //O(1)
		if(x < 0 || y < 0) return 0;
		return hashPref[x][y];
	}
	
	Long hash(Long x1, Long y1, Long x2 , Long y2){ //O(1)
		Long sz = hashPref.size();
		Long ans = hash(x2 , y2);
		ans = sub(ans , mult(hash(x2, y1 - 1) , pot[y2 - y1 + 1] , mod)  , mod); 
		ans = sub(ans , mult(hash(x1 - 1 , y2) , pot[sz * (x2 - x1 + 1)], mod) , mod  );
		ans = add(ans , mult(hash(x1 - 1 , y1 - 1) , pot[sz * (x2 - x1 + 1) + (y2 - y1 + 1)] , mod) , mod);
		return ans;
	}

	void precalc(vector<vector<char>> &A){ //O(n * m)
		Long n = A.size();
		Long m = A[0].size();
		Long sz = hashPref.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++){
				hashPref[i][j] = A[i][j] - minChar + 1;
				if(i > 0) {
					hashPref[i][j] = add(hashPref[i][j] , mult(hashPref[i - 1][j] , pot[sz] , mod) , mod);
				}
				if(j > 0){
					hashPref[i][j] = add(hashPref[i][j] , mult(hashPref[i][j - 1] , base, mod) , mod);
				}
				if(i > 0 && j > 0){
					hashPref[i][j] = sub(hashPref[i][j] , mult(mult(base , pot[sz] , mod), hashPref[i - 1][j - 1] , mod) , mod);
				}
			}
		}
	}
};

struct MultiHash{
	vector<Hash> hashes;
	
	MultiHash(vector<Long> mods, vector<Long> bases) {
		for (Long i = 0; i < mods.size(); i++) {
			hashes.push_back(Hash(mods[i], bases[i]));
		}
	}
	
	void precalc(vector<vector<char>> &s) {
		for (int i = 0; i < hashes.size(); i++) {
			hashes[i].precalc(s);
		}
	}
	
	vector<Long> hash(Long x1, Long y1, Long x2, Long y2) {
		vector<Long> ans;
		for (Long i = 0; i < hashes.size(); i++) {
			ans.push_back(hashes[i].hash(x1, y1, x2, y2));
		}
		return ans;
	}
};

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

vector<Long> getBases(vector<Long> mods) {
	vector<Long> ans;
	for (Long m : mods) {
		Long base = 2 * random(33, m / 2) + 1; //odd base
		ans.push_back(base);
	}
	return ans;
}

int main(){
	return 0;
}

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

struct Hash{
	Long mod, base;
	vector<Long> pot, hashPref, hashSuf;
	
	Hash(Long mod = 1e9 + 7 , Long base = 67) {
		//other mod 1e9 + 1269
		this->mod = mod;
		this->base = base;
	}
	
	Long hash(Long l, Long r) { //O(1)
		if(l == 0) return hashPref[r];
		return sub(hashPref[r] , mult(hashPref[l - 1] , pot[r - l + 1], mod) , mod);
	}

	Long hashInverse(Long l, Long r) { //O(1)
		return sub(hashSuf[l], mult(hashSuf[r + 1], pot[r - l + 1], mod) , mod);
	}
	
	bool isPalindrome(Long l, Long r) { //O(1)
		return hash(l , r) == hashInverse(l , r);
	}

	void precalc(string &s) { //O(n)
		Long n = s.size();
		pot = hashPref = vector<Long>(n);
		hashSuf = vector<Long>(n + 1);
		pot[0] = 1;
		hashPref[0] = s[0] - minChar + 1;
		for (int i = 1; i < n; i++) {
			hashPref[i] = add(mult(hashPref[i - 1], base, mod), s[i] - minChar + 1, mod);
			pot[i] = mult(pot[i - 1] , base , mod);
		}
		hashSuf[n] = 0;
		hashSuf[n - 1] = s[n - 1] - minChar + 1;
		for (int i = n - 2; i >= 0; i--) {
			hashSuf[i] = add(mult(hashSuf[i + 1] , base, mod),  s[i] - minChar + 1, mod);
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
	
	void precalc(string &s) {
		for (int i = 0; i < hashes.size(); i++) {
			hashes[i].precalc(s);
		}
	}
	
	vector<Long> hash(Long l, Long r) {
		vector<Long> ans;
		for (Long i = 0; i < hashes.size(); i++) {
			ans.push_back(hashes[i].hash(l, r));
		}
		return ans;
	}
	
	bool isPalindrome(Long l, Long r) {
		for (Long i = 0; i < hashes.size(); i++) {
			if (!hashes[i].isPalindrome(l , r)) {
				return false;
			}
		}
		return true;
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

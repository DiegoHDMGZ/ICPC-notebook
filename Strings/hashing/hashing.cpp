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
	
	Hash(Long n, Long mod = 1e9 + 7 , Long base = 67) {
		//other mod 1e9 + 1269
		this->mod = mod;
		this->base = base;
		pot = hashPref = hashSuf = vector<Long>(n);
		pot[0] = 1;
		for (int i = 1; i < n; i++) {
			pot[i] = mult(pot[i - 1] , base , mod);
		}
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
		Long sz = s.size();
		hashPref[0] = s[0] - minChar + 1;
		for (int i = 1; i < sz; i++) {
			hashPref[i] = add(mult(hashPref[i - 1], base, mod), s[i] - minChar + 1, mod);
		}
		hashSuf[sz] = 0;
		hashSuf[sz - 1] = s[sz - 1]- minChar + 1;
		for (int i = sz - 2; i >= 0; i--) {
			hashSuf[i] = add(mult(hashSuf[i + 1] , base, mod),  s[i] - minChar + 1, mod);
		}
	}
};

mt19937_64  rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) {
	return uniform_int_distribution<Long>(a , b)(rng);
}

struct MultipleHash{
	vector<Hash> hashes;
	
	MultipleHash(Long n , vector<Long> mods) {
		for (Long m : mods) {
			hashes.push_back(Hash(n, m, 2 * random(33, m / 2) + 1));
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
};
 
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);

	
	return 0;
}

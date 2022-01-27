#include <bits/stdc++.h>
#define REP(i , n) for(Long i = 0; i < (Long)n; i++)
#define debug(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long Long;

Long MOD;

struct ModInt {
	Long val;
	ModInt(Long val = 0) : val(val){}
	ModInt operator +(const ModInt &other) const {
		if (val + other.val < MOD) return val + other.val;
		return val + other.val - MOD;
	}
	ModInt operator -(const ModInt &other) const {
		if (val - other.val >= 0) return val - other.val;
		return val - other.val + MOD;
	}
	ModInt operator *(const ModInt &other) const {
		return (val * other.val) % MOD;
	}
};

Long minChar = (Long)'0';

int toInt(char c) {
	return c - minChar + 1;
}

struct Hash{
	Long mod, base;
	vector<ModInt> power, hashPref, hashSuf;
	
	Hash(Long mod, Long base, string &s) {
		this->mod = mod;
		this->base = base;
		build(s);
	}
	
	Long hash(int l, int r) { //O(1)
		MOD = mod;
		if (l == 0) return hashPref[r].val;
		return (hashPref[r] - hashPref[l - 1] * power[r - l + 1]).val;
	}

	Long hashInverse(int l, int r) { //O(1)
		MOD = mod;
		return (hashSuf[l] - hashSuf[r + 1] * power[r - l + 1]).val;
	}
	
	bool isPalindrome(int l, int r) { //O(1)
		return hash(l , r) == hashInverse(l , r);
	}

	void build(string &s) { //O(n)
		MOD = mod;
		Long n = s.size();
		power = hashPref = vector<ModInt>(n);
		hashSuf = vector<ModInt>(n + 1);
		power[0] = 1;
		hashPref[0] = toInt(s[0]);
		for (int i = 1; i < n; i++) {
			hashPref[i] = hashPref[i - 1] * base + toInt(s[i]);
			power[i] = power[i - 1] * base;
		}
		hashSuf[n] = 0;
		hashSuf[n - 1] = toInt(s[n - 1]);
		for (int i = n - 2; i >= 0; i--) {
			hashSuf[i] = hashSuf[i + 1] * base + toInt(s[i]);
		}
	}
};

struct MultiHash{
	static vector<Long> mods;
	static vector<Long> bases;
	vector<Hash> hashes;
	
	MultiHash(string &s) {
		for (int i = 0; i < mods.size(); i++) {
			hashes.push_back(Hash(mods[i], bases[i], s));
		}
	}
	
	vector<Long> hash(int l, int r) {
		vector<Long> ans;
		for (int i = 0; i < hashes.size(); i++) {
			ans.push_back(hashes[i].hash(l, r));
		}
		return ans;
	}
	
	bool isPalindrome(int l, int r) {
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
vector<Long> MultiHash::mods = {(Long)1e9 + 7 , (Long)1e9 + 1269};
vector<Long> MultiHash::bases = getBases(mods);

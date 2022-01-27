#include <bits/stdc++.h>
#define REP(i , n) for(Long i = 0; i < (Long)n; i++)
#define debug(x) cout << #x << " = " << x << endl;
#define pb push_back

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
	ModInt operator +=(const ModInt &other) {
		*this = *this + other;
		return *this;
	}
	ModInt operator -=(const ModInt &other) {
		*this = *this - other;
		return *this;
	}
};

Long minChar = (Long)'0';

int toInt(char c) {
	return c - minChar + 1;
}

const int MX = 1000;
struct Hash{
	Long mod, base;
	vector<ModInt> power;
	vector<vector<ModInt>> hashPref;
	
	Hash(Long mod, Long base) {
		this->mod = mod;
		this->base = base;
		MOD = mod;
		hashPref = vector<vector<ModInt>>(MX, vector<ModInt>(MX));
		power = vector<ModInt>(MX * MX);
		power[0] = 1;
		for (int i = 1; i < MX * MX; i++) {
			power[i] = power[i - 1] * base;
		}
	}
	
	Long hash(int x, int y){ //O(1)
		if (x < 0 || y < 0) return 0;
		return hashPref[x][y].val;
	}
	
	Long hash(int x1, int y1, int x2 , int y2){ //O(1)
		MOD = mod;
		int sz = hashPref.size();
		ModInt ans = hash(x2 , y2);
		ans -= power[y2 - y1 + 1] * hash(x2, y1 - 1); 
		ans -= power[sz * (x2 - x1 + 1)] * hash(x1 - 1, y2);
		ans += power[sz * (x2 - x1 + 1) + (y2 - y1 + 1)] * hash(x1 - 1, y1 - 1);
		return ans.val;
	}

	void build(vector<string> &A){ //O(n * m)
		MOD = mod;
		int n = A.size();
		int m = A[0].size();
		int sz = hashPref.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++){
				hashPref[i][j] = toInt(A[i][j]);
				if (i > 0) {
					hashPref[i][j] += hashPref[i - 1][j] * power[sz];
				}
				if (j > 0){
					hashPref[i][j] += hashPref[i][j - 1] * base;
				}
				if (i > 0 && j > 0){
					hashPref[i][j] -= power[sz] * hashPref[i - 1][j - 1] * base;
				}
			}
		}
	}
};

struct MultiHash{
	static vector<Long> mods;
	static vector<Long> bases;
	vector<Hash> hashes;

	MultiHash() {
		for (int i = 0; i < mods.size(); i++) {
			hashes.push_back(Hash(mods[i], bases[i]));
		}
	}
	
	void build(vector<string> &s) {
		for (int i = 0; i < hashes.size(); i++) hashes[i].build(s);
	}
	
	vector<Long> hash(int x1, int y1, int x2, int y2) {
		vector<Long> ans;
		for (int i = 0; i < hashes.size(); i++) {
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
vector<Long> MultiHash::mods = {(Long)1e9 + 7 , (Long)1e9 + 1269};
vector<Long> MultiHash::bases = getBases(mods);

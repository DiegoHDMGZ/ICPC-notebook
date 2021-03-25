#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const Long MX = 1e5; //sum of length of all words + 1 
const Long ALPH = 26; // alphabet size

struct Trie{
	Long memo[MX][ALPH];
	bool term[MX]; //terminal node
	Long nodes = 1;
	
	void clear() {
		for (Long i = 0; i < nodes; i++) {
			term[i] = 0;
			for (int j = 0; j < ALPH; j++) {
				memo[i][j] = 0;
			}
		}
		nodes = 1;
	}
	
	void addWord(string &s) { //O(n)
		int n = s.size();
		int u = 0;
		for (Long i = 0; i < n; i++) {
			Long c = s[i] - 'a';
			if (memo[u][c] == 0) {
				memo[u][c] = nodes++;
			}
			u = memo[u][c];
		}
		term[u] = true;
	}
	
	bool isPrefix(string &s) { //O(n)
		Long n = s.size();
		Long u = 0;
		for (Long i = 0; i < n; i++) {
			Long c = s[i] - 'a';
			if (memo[u][c] == 0) {
				return false;
			}
			u = memo[u][c];
		}
		return true;
	}
	
	bool isWord(string &s) { //O(n)
		Long n = s.size();
		Long u = 0;
		
		for (Long i = 0; i < n; i++) {
			Long c = s[i] - 'a';
			if (memo[u][c] == 0) {
				return false;
			}
			u = memo[u][c];
		}
		return term[u]; 
	}
}trie;

int main() {
	return 0;
}

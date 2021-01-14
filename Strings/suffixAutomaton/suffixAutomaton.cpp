#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

const int MX = 2e5;
struct SuffixAutomaton{
	int len[2 * MX];
	int link[2 * MX];
	map<int, int> to[2 * MX]; //<= 3n - 4 transitions 
	int last;
	int sz;
	
	SuffixAutomaton() {
		last = 0;
		sz = 1;
		link[0] = -1;
		len[0] = 0;
	}
	
	void addLetter(char c) { //Overall O(n)
		int p = last;
		last = sz++; 
		len[last] = len[p] + 1;
		while (p != -1 && to[p][c] == 0) {
			to[p][c] = last;
			p = link[p];
		}
		if (p == -1) {
			link[last] = 0;
			return;
		}
		int q = to[p][c];
		if (len[q] == len[p] + 1) {
			link[last] = q;
			return;
		}
		int clone = sz++;
		to[clone] = to[q];
		link[clone] = link[q];
		link[last] = link[q] = clone;
		len[clone] = len[p] + 1;
		while (p != -1 && to[p][c] == q) {
			to[p][c] = clone;
			p = link[p];
		}
	}
	
	void build(string &s) {
		for (char c : s) addLetter(c);
	}
	
	Long countSubstrings() {
		Long ans = 0;
		for (int i = 1; i < sz; i++) {
			ans += len[i] - len[link[i]];
		}
		return ans;
	}
}automaton;

int main() {
	return 0;
}

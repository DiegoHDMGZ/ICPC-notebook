#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
Properties:
-If the string s is the longest string in state u
then all suffixes of s of length [len[link[u]] + 1, len[u]] are in state u
-The transitions form a DAG
-All substrings in some state, appears with the same ending position
-Each path represent a unique substring
-The size of the ending positions (the number of occurrences) of a state
is the number of paths from that state to some terminal state
*/

const int MX = 2e5;
struct SuffixAutomaton{
	int len[2 * MX]; //the longest length of the substrings of this state
	int link[2 * MX]; //the state with the maximum suffix not contain in current state
	map<int, int> to[2 * MX]; //<= 3n - 4 transitions 
	bool terminal[2 * MX];
	int last;
	int sz;
	
	SuffixAutomaton() {
		last = 0;
		sz = 1;
		link[0] = -1;
		len[0] = 0;
	}
	
	void clear() {
		for (int i = 0; i < sz; i++) {
			len[i] = 0;
			link[i] = -1;
			to[i].clear();
			terminal[i] = false;
		}
		last = 0;
		sz = 1;
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
	
	void markTerminal() {
		int u = last;
		while (u != 0) {
			terminal[u] = true;
			u = link[u];
		}
	}
	
	void build(string &s) {
		for (char c : s) addLetter(c);
		markTerminal();
	}
	
	int feed(string &t) {
		int u = 0;
		for (int i = 0; i < t.size(); i++) {
			if (to[u].find(t[i]) == to[u].end()) return -1;
			u = to[u][t[i]];
		}
		return u;
	}
	
	bool isSuffix(string &t) {
		int u = feed(t);
		return u != -1 && terminal[u];
	}
	
	bool find(string &t) {
		return feed(t) != -1;
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

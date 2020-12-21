#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const int ALPH = 256;

vector<int> sortCyclic(string &s) { //O(n log n)
	int n = s.size();
	vector<int> p(n), c(n), cnt(max(ALPH , n), 0);
	//p[] : sorted array with the starting index of substrings of length 2^k 
	//c[] : equivalence class
	//counting sort
	for (int i = 0; i < n; i++) cnt[s[i]]++;
	for (int i = 1; i < ALPH; i++) cnt[i] += cnt[i - 1];
	for (int i = 0 ; i < n; i++) {
		p[--cnt[s[i]]] = i;
	}
	c[p[0]] = 0;
	int classes = 1;
	for (int i = 1; i < n; i++) {
		if (s[p[i]] != s[p[i - 1]]) {
			classes++;
		}
		c[p[i]] = classes - 1;
	}
	// radix sort
	vector<int> pNew(n) , cNew(n);
	for (int k = 0; (1 << k) < n ; k++) {
		//sort pNew by the second substring
		for (int i = 0; i < n; i++) {
			pNew[i] = p[i] - (1 << k);
			if (pNew[i] < 0) pNew[i] += n;
			cnt[i] = 0;
		}
		//counting sort in the first substring
		for (int i = 0; i < n; i++) cnt[c[pNew[i]]]++;
		for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
		for (int i = n - 1 ; i >= 0; i--) {
			p[--cnt[c[pNew[i]]]] = pNew[i];
		}
		cNew[p[0]] = 0;
		classes = 1;
		for(int i = 1; i < n; i++) {
			int x = p[i] + (1 << k);
			if (x >= n) x -= n;
			int y = (p[i - 1] + (1 << k));
			if (y >= n) y -= n;
			pair<int, int> cur = {c[p[i]], c[x]};
			pair<int, int> prev = {c[p[i - 1]], c[y]};
			if(cur != prev) {
				classes++;
			}
			cNew[p[i]] = classes - 1;	
		}
		c = cNew;
	}
	return p;
}

//Suffix array: contain starting indexes of the all the suffixes (sorted)
vector<int> suffixArray(string &s) {
	char minChar = 'a' - 1;
	s += minChar;
	vector<int> v = sortCyclic(s);
	v.erase(v.begin());
	s.pop_back();
	return v;
}

int main() {
	return 0;
}

#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

const int ALPH = 256;

struct SuffixArray {
	vector<int> suffixArray;
	vector<int> lcp;
	
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

	void buildLCP(string &s) { //O(n)
		int n = s.size();
		vector<int> pos(n);
		lcp = vector<int>(n - 1, 0);
		for (int i = 0; i < n; i++) {
			pos[suffixArray[i]] = i;
		}
		int k = 0;
		for (int r = 0; r < n; r++) {
			if (pos[r] == 0) continue;
			int l = suffixArray[pos[r] - 1];
			while (s[l + k] == s[r + k]) {
				k++;
			}
			lcp[pos[r] - 1] = k;
			k = max(0, k - 1);
		}
	}

	//Suffix array: contain starting indexes of the all the suffixes (sorted)
	void build(string &s) { //O(n log n)
		int n = s.size();
		suffixArray = vector<int>(n, 0);
		char minChar = 'a' - 1;
		s += minChar;
		suffixArray = sortCyclic(s);
		suffixArray.erase(suffixArray.begin());
		s.pop_back();
		buildLCP(s);
	}
};

int main() {
	return 0;
}

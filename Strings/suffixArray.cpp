#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

char minChar = 'a' - 1;

vector<Long> sortCyclic(string &s) { //O(n log n)

	Long n = s.size();
	Long alphabet = 26 + 1;
	vector<Long> p(n) , c(n) , cnt(max(alphabet , n));
	
	//p[] : sorted array with the starting index of substrings of length 2^k 
	//c[] : equal substrings have equal c[], c[i] correspond to the substring with starting index i
	
	//zero iteration
	//counting sort
	for(Long i = 0; i < n; i++) {
		cnt[s[i] - minChar]++;
	}
	for(Long i = 1; i < alphabet; i++) {
		cnt[i] += cnt[i - 1];
	}
	for(Long i = n - 1 ; i >= 0; i--) {
		Long x = s[i] - minChar;
		p[--cnt[x]] = i;
	}
	
	c[p[0]] = 0;
	Long classes = 1;
	for(Long i = 1; i < n; i++) {
		if(s[p[i]] != s[p[i - 1]]) {
			classes++;
		}
		c[p[i]] = classes - 1;
	}
	
	//in each iteration "k", it sorts for all substrings of length 2 ^ k
	// radix sort
	// we first sort the second substring of length 2 ^ ( k - 1) and then by the first
	vector<Long> pAux(n) , cAux(n);
	for(Long k = 0; (1LL << k) < n ; k++ ) {

		for(Long i = 0; i < n; i++) {
			//pAux is sorted by the second substring
			pAux[i] = p[i] - (1LL << k);
			if(pAux[i] < 0) {
				pAux[i] += n;
			}
			if(i < (Long)(cnt.size())) {
				cnt[i] = 0;
			}
		}
	
		//counting sort in the first substring
		for(Long i = 0; i < n; i++) {
			cnt[c[pAux[i]]]++;
		}
		for(Long i = 1; i < classes; i++) {
			cnt[i] += cnt[i - 1];
		}
		for(Long i = n - 1 ; i >= 0 ; i--) {
			//pAux[i] is pointing at the first substring 
			p[--cnt[c[pAux[i]]]] = pAux[i];
		}
		cAux[p[0]] = 0;
		classes = 1;
		for(Long i = 1; i < n; i++) {
			Long x = p[i] + (1LL << k);
			if(x > n) {
				x -= n; 
			}
			Long y = p[i - 1] + (1LL << k);
			if(y > n) {
				y -= n; 
			}
			pair<Long, Long> cur = {c[p[i]], c[x]};
            pair<Long, Long> prev = {c[p[i - 1]], c[y]};
            if(cur != prev) {
            	classes++;
			}
			cAux[p[i]] = classes - 1;	
		}
		c = cAux;
	}
	return p;
}

//A suffix array will contain integers that represent the starting indexes of the all the suffixes of a given string,
// after the aforementioned suffixes are sorted.
vector<Long> suffixArray(string &s) {
	s += minChar;
	vector<Long> v = sortCyclic(s);
	v.erase(v.begin());
	s.pop_back();
	return v;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string s;
	cin >> s;
	vector<Long> v = suffixArray(s);
	

	REP(i, v.size()) {
		cout << i << " : ";
		for(Long j = v[i]; j < s.size(); j++) {
			cout << s[j];
		}
		cout << endl;
	}
	return 0;
}


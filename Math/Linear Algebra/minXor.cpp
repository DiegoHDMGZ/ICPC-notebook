#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i, n) for (Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

//Problem: You are given an array A of n integers and Q queries
//In each query you will be given an integer X. Find the minimum value
//Find the minimum value of the xor of X and the xor 
//of any subsequence of A

//Solution:
//Treat every integer as a binary vector with d bits
//Use gaussian elimination to obtain the basis of size O(d)
//Each query can be answer in O(d)

int getBit(Long mask, int pos) {
	return (mask >> pos) & 1;
}

struct Basis{
	vector<Long> basis;
	
	//gauss elimination
	vector<Long> getBasis(vector<Long> &A) { //O(n * d), d = O(log A_i)
		int n = A.size();
		if (A.empty()) return {};
		vector<Long> ans;
		vector<bool> blocked(n, false);
		for (int i = 0; i < n; i++) {
			Long best = -1;
			for (int j = 0; j < n; j++) {
				if (blocked[j]) continue;
				if (best == -1 || A[j] > A[best]) {
					best = j;
				}
			}
			if (A[best] == 0) break;
			ans.push_back(A[best]);
			blocked[best] = true;
			int pos = 63 - __builtin_clzll(A[best]);
			for (int j = 0; j < n ;j++) {
				if (blocked[j]) continue;
				if (A[j] == 0) continue;
				int pos2 = 63 - __builtin_clzll(A[j]);
				if (pos == pos2) {
					A[j] ^= A[best];
				}
			}
		}
		for (int i = (int)ans.size() - 1; i >= 0; i--) {
			int pos = 63 - __builtin_clzll(ans[i]);
			for (int j = i - 1; j >= 0; j--) {
				if (getBit(ans[j], pos) == 1) {
					ans[j] ^= ans[i];
				}
			}
		}
		
		return ans;
	}

	Basis(vector<Long> A) {
		basis = getBasis(A);
	}
	
	Long minXor(Long x) { //O(d) = O(log A_i)
		for (Long c : basis) {
			x = min(x ^ c, x);
		}
		return x;
	}
};

int main() {
	return 0;
}

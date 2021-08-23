#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct MaxStack{
	stack<Long> s;
	
	Long f(Long a, Long b) {
		return max(a, b);
	}

	Long get() { //O(1) amortized
		if (s.empty()) return 0;
		return s.top();
	}
	
	void add(Long val) { //O(1) amortized
		Long ans = s.empty() ? val : f(val, s.top());
		s.push(ans);
	}
	
	void pop() { //O(1) amortized
		s.pop();
	}
	
	void clear() {
		while (!s.empty()) s.pop();
	}
}ms;

int main() {
	return 0;
}

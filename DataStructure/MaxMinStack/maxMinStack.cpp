#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct MaxStack{
	stack<pair<Long, Long>> s; // ( value , maximum)
	
	Long f(Long a, Long b) {
		return max(a, b);
	}

	Long get() { //O(1) amortized
		if (s.empty()) return 0;
		return s.top().second;
	}
	
	void add(Long newElement) { //O(1) amortized
		Long newVal = s.empty() ? newElement : min(newElement, s.top().second);
		s.push({newElement , newVal});
	}
	
	void pop() { //O(1) amortized
		s.pop();
	}
	
	void clear() {
		while (!s.empty()) {
			s.pop();
		}
	}
}ms;

int main() {
	return 0;
}

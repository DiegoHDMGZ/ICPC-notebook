#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

struct MaxQueue{
	stack<pair<Long, Long>> s1, s2; // (value , answer)
	
	Long f(Long a, Long b) {
		return max(a, b);
	}

	Long get() { //O(1) amortized
		if (s1.empty() && s2.empty()) return 0;
		if (s1.empty() || s2.empty()) {
			return s1.empty() ? s2.top().second : s1.top().second;
		} else {
			return f(s1.top().second, s2.top().second);
		}
	}
	
	void add(Long val){ //O(1) amortized
		Long ans = s1.empty() ? val : f(val, s1.top().second);
		s1.push(make_pair(val, ans));
	}
	
	void pop(){ //O(1) amortized
		if (s2.empty()) {
			//s2 = reverse(s1)
			while (!s1.empty()) {
				Long val = s1.top().first;
				s1.pop();
				Long ans = s2.empty() ? val : f(val, s2.top().second);
				s2.push(make_pair(val, ans));
			}
		}
		s2.pop();
	}
	
	void clear() {
		while (!s1.empty()) s1.pop();
		while (!s2.empty()) s2.pop();
	}
}mq;

int main() {
	return 0;
}

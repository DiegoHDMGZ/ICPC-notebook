#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Let f(x, y) be any function, and let also define f(x) = x
Operations:
- Push: Add a new element to the top of the stack
- Pop: Delete the most recently added element from the top of stack
- Get: Let S be the elements of the stack (from oldest to newest), 
it returns the result of f(...f(f(f(S_1, S_2), S_3), ... ), S_n)
This is equivalent to ans = f(ans, S_i) for all i

It's also possible to change the behaviour of the get function and
returns f(S_n, f(S_{n-1}, ... f(S_2, f(S_1))...))
This is equivalent to ans = f(S_i, ans) for all i.
To do that just swap the operands in f
*/

struct MaxStack{
	stack<Long> s;
	
	Long f(Long a, Long b) {
		return max(a, b);
	}

	Long get() { //O(1) amortized
		if (s.empty()) return 0;
		return s.top();
	}
	
	void push(Long val) { //O(1) amortized
		Long ans = s.empty() ? val : f(s.top(), val);
		s.push(ans);
	}
	
	void pop() { //O(1) amortized
		s.pop();
	}
	
	void clear() {
		while (!s.empty()) s.pop();
	}
}ms;

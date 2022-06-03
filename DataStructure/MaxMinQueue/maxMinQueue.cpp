#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
Let f(x, y) be any associative function, and let also define f(x) = x
Operations:
- Push: Add a new element to the end of the queue
- Pop: Delete the first element (oldest) from the queue
- Get: Let Q be the elements of the queue in the order they enter,
it returns the result of f(Q_1, Q_2, ..., Q_n)

It's also possible to change the behaviour of the get function and
returns f(Q_n, Q_{n-1}, ..., Q_2, Q_1)
To do that just swap the operands in f
*/

struct MaxQueue {
    stack<pair<Long, Long>> s1, s2; //<value, answer>

    Long f(Long a, Long b) { return max(a, b); }

    Long get() { // O(1) amortized
        if (s1.empty() && s2.empty()) return 0;
        if (s1.empty() || s2.empty()) {
            return s1.empty() ? s2.top().second : s1.top().second;
        } else {
            return f(s2.top().second, s1.top().second);
        }
    }

    void push(Long val) { // O(1) amortized
        Long ans = s1.empty() ? val : f(s1.top().second, val);
        s1.push(make_pair(val, ans));
    }

    void pop() { // O(1) amortized
        if (s2.empty()) {
            // s2 = reverse(s1)
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
} mq;

#include <bits/stdc++.h>
using namespace std;

using Long = long long;

/*
Min array partition cost of any size
dp[i]: Min cost to divide the array [0 ... i]
dp[-1] = 0
dp[i] = min{dp[p] + cost(p + 1, i) , -1 <= p < i}
Condition: opt[i] <= opt[i + 1]
A sufficient condition in cost is Quadrangle Inequality:
For all a <= b <= c <= d
cost(a, d) - cost(b, d) >= cost(a, c) - cost(b, c)
(For maximization is the opposite sign)
--------------------------------------------------
Ways of proving that that cost satisfies Quadrangle Inequality:
(see D&C dp)
*/

Long cost(int l, int r);

struct Range {
    int l, r, opt;
    Range(int l, int r, int opt) : l(l), r(r), opt(opt) {}
};

Long minCost(int n) { // O(n log n)
    vector<Long> dp(n);
    dp[0] = cost(0, 0);
    deque<Range> ranges = {Range(1, n - 1, -1)};
    auto getOptimum = [&](int i, int opt) {
        if (opt == -1) return cost(0, i);
        assert(opt + 1 <= i);
        return dp[opt] + cost(opt + 1, i);
    };
    for (int i = 0; i + 1 < n; i++) {
        assert(ranges.front().l == i + 1);
        auto improve = [&](int pos, int opt) {
            return getOptimum(pos, i) < getOptimum(pos, opt);
        };
        while (!ranges.empty() && improve(ranges.back().l, ranges.back().opt)) {
            ranges.pop_back();
        }
        if (ranges.empty()) ranges.push_back(Range(i + 1, n - 1, i));
        else {
            int low = ranges.back().l;
            int high = ranges.back().r;
            int opt = ranges.back().opt;
            if (!improve(high, opt)) low = high++;
            // F F F ... T T T
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (improve(mid, opt)) high = mid;
                else low = mid;
            }
            ranges.back().r = low;
            if (high < n) ranges.push_back(Range(high, n - 1, i));
        }
        dp[i + 1] = getOptimum(i + 1, ranges.front().opt);
        ranges.front().l++;
        if (ranges.front().l > ranges.front().r) ranges.pop_front();
    }
    return dp[n - 1];
}

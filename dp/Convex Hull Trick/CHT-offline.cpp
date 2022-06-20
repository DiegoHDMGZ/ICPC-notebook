#include <bits/stdc++.h>
using namespace std;

using Long = long long;

/*
We have "n" linear functions yi = mi x + bi
There are queries for the maximum y for a given x among all the functions.
Trick: Construct the lower envelope hull

For minimum just put the negative of mi and bi.
Or change the comparator sign in cmp, and in check and in same slope case
*/

struct Line {
    Long m, b;
    Line() {}
    Line(Long m, Long b) : m(m), b(b) {}
    bool operator<(const Line &other) const {
        if (m == other.m) return b > other.b;
        return m < other.m;
    }
    Long getVal(Long x) {
        return m * x + b;
    }
};

struct CHT {
    vector<Line> envelope;

    bool check(Long mid, Long x) {
        return envelope[mid + 1].getVal(x) - envelope[mid].getVal(x) <= 0;
    }

    Long search(Long low, Long high, Long x) { // O(log n)
        if (!check(high - 1, x)) return envelope[high].getVal(x);
        if (check(low, x)) return envelope[low].getVal(x);
        while (high - low > 1) {
            Long mid = low + (high - low) / 2;
            if (check(mid, x)) high = mid;
            else low = mid;
        }
        return envelope[high].getVal(x);
    }

    Long div(Long a, Long b) { // floored division
        // CAREFUL ! this won't produced the right convex envelope
        // but the maxY function will still work for integers
        // if you need the correct convex envelope, use double division
        // or multiplication in "bad" function
        assert(b != 0);
        return a / b - ((a ^ b) < 0 && a % b);
    }

    Long intersect(Line l1, Line l2) {
        return div(l1.b - l2.b, l2.m - l1.m);
    }

    bool bad(Line l1, Line l2, Line l3) {
        // tells if l2 is bad an can be eliminated by l3
        return intersect(l2, l3) <= intersect(l1, l2);
    }

    void addLine(Line l3) {
        if (envelope.empty()) {
            envelope.push_back(l3);
            return;
        }
        if (l3.m == envelope.back().m) return;
        if (envelope.size() <= 1) {
            envelope.push_back(l3);
            return;
        }
        Long sz = envelope.size();
        Line l1 = envelope[sz - 2];
        Line l2 = envelope[sz - 1];
        while (bad(l1, l2, l3)) {
            envelope.pop_back();
            if (envelope.size() == 1) break;
            sz = envelope.size();
            l1 = envelope[sz - 2];
            l2 = envelope[sz - 1];
        }
        envelope.push_back(l3);
    }

    void build(vector<Line> &lines) { // O(n log n)
        sort(lines.begin(), lines.end());
        for (Line l : lines) addLine(l);
    }

    Long maxY(Long x) { // O(log n)
        assert(!envelope.empty());
        if (envelope.size() == 1) return envelope[0].getVal(x);
        return search(0, (Long)envelope.size() - 1, x);
    }
};

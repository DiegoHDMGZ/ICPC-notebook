#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

/*
We have linear functions yi = mi x + bi that will be added
in increasing order of m.

There are queries for the maximum y for a given x among all the functions. 
The queries are sorted in increasing/decreasing order of x

For minimum just put the negative of mi and bi.
Or change the comparator sign in cmp, and in check and in same slope case
*/

struct Line{
	Long m, b;
	Line() {}
	Line(Long m, Long b): m(m), b(b) {}
	Long getVal(Long x) {return m * x + b;}
};

struct CHT{
	deque<Line> envelope;

	Long div(Long a, Long b) { //floored division
		//CAREFUL ! this won't produced the right convex envelope
		//but the maxY function will still work for integers
		//if you need the correct convex envelope, use double division
		//or multiplication in "bad" function
		assert(b != 0);
		return a / b - ((a ^ b) < 0 && a % b); 
	}
	
	Long intersect(Line l1, Line l2) {
		return div(l1.b - l2.b, l2.m - l1.m);
	}
	
	bool bad(Line l1, Line l2, Line l3) {
		//tells if l2 is bad an can be eliminated by l3
		return intersect(l2 , l3) <= intersect(l1, l2);
	}

	void addLine(Line l3) { 
		if (envelope.empty()) {
			envelope.push_back(l3);
			return;
		}
		if (l3.m == envelope.back().m) {
			if (l3.b > envelope.back().b) envelope.pop_back();
			else return;
		}
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
	
	Long maxY(Long x) { //O(1) amortized
		assert(!envelope.empty());
		//x increasing
		while (envelope.size() >= 2 && envelope[0].getVal(x) < envelope[1].getVal(x)) {
			envelope.pop_front();
		}
		return envelope[0].getVal(x);
		
		//x decreasing
		/*int sz = envelope.size();
		while (sz >= 2 && envelope[sz - 1].getVal(x) < envelope[sz - 2].getVal(x)) {
			envelope.pop_back();
			sz--;
		}
		return envelope.back().getVal(x);*/
	}
};

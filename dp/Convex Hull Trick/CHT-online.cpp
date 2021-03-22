#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
using namespace std;

typedef long long Long;

/*
We have "n" linear functions yi = mi x + bi
There are queries for the maximum y for a given x among all the functions. 
Trick: Construct the lower envelope hull

For minimum just put the negative of mi and bi.
Or change the comparator sign in cmp, in check function and in same slope case
*/

const Long INF = 1e18;

struct Line {
	mutable Long m , b , r;
	//mx + b, intersect with next line at r (rounded down)
	Line() {}
	Line(Long m , Long b) : m(m), b(b) , r(0) {}
	
	bool operator < (const Line &other) const {
		return m < other.m;
	}
	
	bool operator < (const Long &x) const {
		return r < x;
	}
	
	Long getVal(Long x) {
		return m * x + b;
	}
};

struct CHT{
	set<Line , less<>> envelope;
	
	Long div(Long a, Long b) { //floored division
		//CAREFUL ! this won't produced the right convex envelope
		//but the maxY function will still work for integers
		//if you need the correct convex envelope, use double division
		return a / b - ((a ^ b) < 0 && a % b); 
	}
	
	Long intersect(Line l1, Line l2) {
		return div(l1.b - l2.b , l2.m - l1.m );
	}
	
	bool bad(Line l1, Line l2, Line l3) {
		//tells if l2 is bad an can be eliminated by l3
		return intersect(l2 , l3) <= intersect(l1, l2);
	}
	
	void addLine(Line L) { //O(log n)
		L.r = INF;
		auto it = envelope.lower_bound(L);
		if (it != envelope.end() && it->m == L.m) { //same slope
			if (it->b >= L.b) return;
			else it = envelope.erase(it);
		}
		if (it != envelope.begin()) {
			if (it != envelope.end() && bad(*prev(it), L , *it)) {
				//L is not necessary
				return;
			}
			it--;
			while (it != envelope.begin()) { //left elimination
				if (bad(*prev(it), *it, L)) {
					it = envelope.erase(it);
					it--;
				} else break;
			}
			it->r = intersect(*it, L);
		} 
		it = envelope.upper_bound(L);
		if (it != envelope.end()) {
			while (next(it) != envelope.end()) { //right elimination
				if (bad(L , *it, *next(it))) it = envelope.erase(it);
				else break;
			}
			L.r = intersect(L , *it);
		}
		envelope.insert(L);
	}
	
	Long maxY(Long x) { //O(log n)
		assert(!envelope.empty());
		Line L = *envelope.lower_bound(x);
		return L.getVal(x);
	}
	
};

int main() {
	return 0;
}

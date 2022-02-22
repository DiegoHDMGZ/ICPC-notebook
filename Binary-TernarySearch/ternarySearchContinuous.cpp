#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;
const Double EPS = 1e-6;

Double f(Double x);

Double ternarySearch(Double low, Double high) { //O(log n)
	while (high - low > EPS) { //for(int i = 0; i < 200 ; i++) {
		Double m1 = low + (high - low) / 3.0;
		Double m2 = high - (high - low) / 3.0;
		//if minimum is needed, change to >
		if (f(m1) < f(m2)) low = m1;
		else high = m2;
	}
	return f((low + high) / 2.0);
}

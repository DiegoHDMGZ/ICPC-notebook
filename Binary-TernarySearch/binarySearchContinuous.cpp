#include <bits/stdc++.h>
using namespace std;
typedef long double Double;

const Double EPS = 1e-6;

bool check(Double mid);

Double search(Double low, Double high, Double x) {
    // F F ... T T
    while (high - low > EPS) { // for (int i = 0; i < 1000; i++) {
        Double mid = (high + low) / 2.0;
        if (check(mid))
            high = mid;
        else
            low = mid;
    }
    return high;
}

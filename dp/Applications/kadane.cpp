#include <bits/stdc++.h>
using namespace std;

using Long = long long;

const Long INF = 1e18;
Long kadane(vector<Long> &v) {
    Long maxSoFar = -INF;
    Long maxEndingHere = 0;
    for (Long x : v) {
        maxEndingHere = max(x, maxEndingHere + x);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}
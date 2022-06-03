#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long kadane(vector<Long> &v, Long L) {
    Long n = v.size();
    vector<Long> acum(n + 1, 0);
    for (Long i = 0; i < n; i++) {
        acum[i + 1] = acum[i] + v[i];
    }
    Long maxSoFar = acum[L];
    Long maxEndingHere = acum[L];

    for (Long i = L; i < n; i++) {
        maxEndingHere = max(acum[i + 1] - acum[i + 1 - L], maxEndingHere + v[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

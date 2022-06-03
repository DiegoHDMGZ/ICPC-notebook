#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long f(Long i);

Long ternarySearch(Long low, Long high) { // O(log n)
    while (high - low > 2) {
        Long m1 = low + (high - low) / 3;
        Long m2 = high - (high - low) / 3;
        // if minimum is needed, change to >
        if (f(m1) < f(m2))
            low = m1;
        else
            high = m2;
    }
    Long maxi = f(low);
    for (Long i = low + 1; i <= high; i++) {
        maxi = max(maxi, f(i)); // if minimum is needed, change to min
    }
    return maxi;
}

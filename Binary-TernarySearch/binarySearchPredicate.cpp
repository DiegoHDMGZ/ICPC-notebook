#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

bool check(Long mid);

Long search(Long low, Long high) { // O(logn)
    // F F F... T T T
    if (!check(high)) return -1; // all F
    if (check(low)) return low;  // all T
    while (high - low > 1) {
        Long mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    // 2 values low -> F and high-> T
    return high;
}

/*
Long search(Long low, Long high) { // O(logn)
    // T T T ... F F F
    if (check(high)) return high; // all T
    if (!check(low)) return -1;   // all F
    while (high - low > 1) {
        Long mid = low + (high - low) / 2;
        if (check(mid))
            low = mid;
        else
            high = mid;
    }
    // 2 values low -> T and high-> F
    return low;
}
*/

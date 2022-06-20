#include <bits/stdc++.h>
using namespace std;

using Long = long long;

pair<Long, Long> getBest(Long lambda); // returns <P(lambda), g(x)>

bool check(Long lambda) {
    return getBest(lambda).second <= 0;
}

const Long INF = 1e18;
Long minimize() { // binary search
    Long low = -INF;
    Long high = INF;
    if (check(high)) return getBest(high).first;
    while (high - low > 1) {
        Long mid = low + (high - low) / 2;
        if (check(mid)) low = mid;
        else high = mid;
    }
    return getBest(low).first;
}

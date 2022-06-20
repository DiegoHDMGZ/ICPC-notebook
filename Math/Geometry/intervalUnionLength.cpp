#include <bits/stdc++.h>
using namespace std;
using Long = long long;

Long segmentUnion(const vector<pair<Long, Long>> &a) { // O(nlogn)
    Long n = a.size();
    vector<pair<Long, bool>> endpoint(n * 2);
    for (int i = 0; i < n; i++) {
        endpoint[2 * i] = make_pair(a[i].first, false);
        endpoint[2 * i + 1] = make_pair(a[i].second, true);
    }
    sort(endpoint.begin(), endpoint.end());
    Long result = 0;
    Long c = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (c > 0) result += (endpoint[i].first - endpoint[i - 1].first);
        if (endpoint[i].second) c--;
        else c++;
    }
    return result;
}

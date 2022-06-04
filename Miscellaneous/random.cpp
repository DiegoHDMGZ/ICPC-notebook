#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

int main() {
    vector<Long> v;
    shuffle(v.begin(), v.end(), rng);
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

long double getTime() {
    auto time = chrono::steady_clock::now().time_since_epoch();
    return chrono::duration_cast<chrono::milliseconds>(time).count();
}
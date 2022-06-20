#include <bits/stdc++.h>
using namespace std;

using Long = long long;

long double getTime() {
    auto time = chrono::steady_clock::now().time_since_epoch();
    return chrono::duration_cast<chrono::milliseconds>(time).count();
}
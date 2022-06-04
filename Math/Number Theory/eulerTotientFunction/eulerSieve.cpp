#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 1e6;
Long phi[MX];

void calculate() { // O(n log log n)
    for (int i = 0; i < MX; i++) phi[i] = i;
    for (int i = 2; i < MX; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MX; j += i) phi[j] -= phi[j] / i;
        }
    }
}

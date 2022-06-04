#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

// (x ^ k) % mod  = rem, mod prime
// Use discreteLog and primiteRoot files

Long fastPow(Long a, Long b, Long mod);
Long primitiveRoot(Long mod);
Long discreteLog(Long base, Long rem, Long mod);

Long discreteRoot(Long k, Long rem, Long mod) {
    if (rem == 0) {
        // Assumption: 0^0 = 1
        if (k != 0 || mod == 1) return 0;
        else return -1;
    }
    Long root = primitiveRoot(mod);
    Long y = discreteLog(fastPow(root, k, mod), rem, mod);
    if (y == -1) return -1;
    return fastPow(root, y, mod);
}

#include <bits/stdc++.h>
using namespace std;

using Long = long long;

Long phi(Long n) { // O(sqrt(n))
    Long ans = n;
    Long i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            ans -= ans / i;
        }
        i++;
    }
    if (n > 1) ans -= ans / n;
    return ans;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long add(Long a, Long b) { return a + b; }

Long sub(Long a, Long b) { return a - b; }

Long operate(Long a, Long b, Long (*op)(Long, Long)) { return op(a, b); }

int main() {
    cout << operate(5, 7, add) << endl;
    cout << operate(5, 7, sub) << endl;
    return 0;
}

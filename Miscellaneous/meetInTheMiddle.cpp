#include <bits/stdc++.h>
using namespace std;
using Long = long long;

// You are given an array of n numbers.
// In how many ways can you choose a subset of the numbers with sum x?

int getBit(int mask, int pos) {
    return (mask >> pos) & 1;
}

vector<Long> merge(vector<Long> &L, vector<Long> &R) {
    vector<Long> ans;
    int l = 0;
    int r = 0;
    while (l < L.size() || r < R.size()) {
        if (l == L.size()) {
            ans.push_back(R[r]);
            r++;
        } else if (r == R.size()) {
            ans.push_back(L[l]);
            l++;
        } else {
            if (L[l] < R[r]) {
                ans.push_back(L[l]);
                l++;
            } else {
                ans.push_back(R[r]);
                r++;
            }
        }
    }
    return ans;
}

vector<Long> generate(vector<Long> &v) {
    vector<Long> allSums = {0};
    for (int i = 0; i < v.size(); i++) {
        vector<Long> R = allSums;
        for (int j = 0; j < R.size(); j++) {
            R[j] += v[i];
        }
        allSums = merge(allSums, R);
    }
    return allSums;
}

int main() {
    Long n, target;
    cin >> n >> target;
    vector<Long> left;
    vector<Long> right;
    for (int i = 0; i < n / 2; i++) {
        Long x;
        cin >> x;
        left.push_back(x);
    }
    for (int i = n / 2; i < n; i++) {
        Long x;
        cin >> x;
        right.push_back(x);
    }

    vector<Long> L = generate(left);
    vector<Long> R = generate(right);

    Long ans = 0;
    int r = R.size();
    r--;
    int l = 0;
    while (l < L.size() && r >= 0) {
        while (L[l] + R[r] > target && r >= 0) {
            r--;
        }
        if (r >= 0 && L[l] + R[r] == target) {
            Long cntL = 1;
            l++;
            while (l < L.size() && L[l] == L[l - 1]) {
                l++;
                cntL++;
            }
            Long cntR = 1;
            r--;
            while (r >= 0 && R[r] == R[r + 1]) {
                r--;
                cntR++;
            }
            ans += cntL * cntR;
        } else {
            l++;
        }
    }
    cout << ans << "\n";
    return 0;
}

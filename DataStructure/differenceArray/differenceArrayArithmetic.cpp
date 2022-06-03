#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MX = 1e5;

struct DifferenceArray {
    Long A[MX];
    Long difConst[MX + 1];
    Long difArith[MX + 1];

    void clear(int n) {
        for (int i = 0; i < n; i++) {
            difConst[i] = 0;
            difArith[i] = 0;
            A[i] = 0;
        }
    }

    void build(vector<Long> &v) {
        difConst[0] = 0;
        difArith[0] = 0;
        for (int i = 0; i < v.size(); i++) {
            difConst[i + 1] = 0;
            difArith[i + 1] = 0;
            updateConstant(i, i, v[i]);
        }
    }

    void updateConstant(int l, int r, Long delta) { // O(1)
        // a[i] += delta
        difConst[l] += delta;
        difConst[r + 1] -= delta;
    }

    void updateIncreasing(int l, int r, Long delta, Long c = 0) { // O(1)
        // a[i] += delta * (i - l + 1) + c
        difArith[l] += delta;
        difArith[r + 1] -= delta;
        updateConstant(l, r, c);
        difConst[r + 1] -= delta * (r - l + 1);
    }

    void updateDecreasing(int l, int r, Long delta, Long c = 0) { // O(1)
        // a[i] += delta * (r - i + 1) + c
        updateConstant(l, r, delta * (r - l + 2));
        updateIncreasing(l, r, -delta);
        updateConstant(l, r, c);
    }

    void update(int n) { // O(n)
        // last update before answering queries
        Long acumConst = 0;
        Long cntArith = 0;
        Long acumArith = 0;
        for (int i = 0; i < n; i++) {
            acumConst += difConst[i];
            cntArith += difArith[i];
            acumArith += cntArith;
            A[i] = acumConst + acumArith;
        }
    }

    Long query(int pos) { // O(1)
        return A[pos];
    }
} df;

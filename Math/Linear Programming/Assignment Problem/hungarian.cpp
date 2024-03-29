#include <bits/stdc++.h>
using namespace std;

// source : https://www.youtube.com/watch?v=ZMnDVv67wug

using Long = long long;
using Matrix = vector<vector<Long>>;
const Long INF = 1e18;
const Long MX = 1e3;
const Long dummy = 1e10;

/*
Problem : You are given an integer matrix. You should choose n cells in
such a way that each row and each column contain exactly one chosen cell,
and the sum of values of all chosen cells is as small as possible.
*/

/*if the objective function is max , change dummy for -INF
and multiply the matrix by -1*/

struct Hungarian {
    Long matchRow[MX];
    Long matchCol[MX];

    void makeSquare(Matrix &A) {
        Long n = A.size();
        Long m = A[0].size();
        for (Long i = 0; i < n; i++) {
            for (Long j = 0; j < n - m; j++) {
                A[i].push_back(dummy);
            }
        }
    }

    Long assign(Matrix A) { // O(n^3)
        Long n = A.size();
        Long m = A[0].size();
        if (n > m) {
            makeSquare(A);
            m = n;
        }

        vector<Long> colAdd(m, 0);
        vector<Long> rowAdd(n, 0);
        fill(matchRow, matchRow + n, -1); // match for i-th row
        fill(matchCol, matchCol + m, -1); // match for i-th col

        for (Long i = 0; i < n; i++) {
            vector<bool> forbidden(m, false); // forbidden column
            vector<Long> parent(n, -1);       // parent in conflict tree
            vector<Long> minVal(m, INF);      // minVal in column
            vector<Long> minPos(m, -1);       // row where the min value is achieved
            Long cur = i;
            while (true) {
                Long minCol = -1;
                // update minVal and minPos and find minCol
                for (Long j = 0; j < m; j++) {
                    if (!forbidden[j]) {
                        Long val = A[cur][j] + rowAdd[cur] + colAdd[j];
                        if (val < minVal[j]) {
                            minVal[j] = val;
                            minPos[j] = cur;
                        }
                        if (minCol == -1 || minVal[j] < minVal[minCol]) {
                            minCol = j;
                        }
                    }
                }
                // decrease every considered row
                // increase every forbidden col
                Long x = minVal[minCol];
                for (Long j = 0; j < m; j++) {
                    if (forbidden[j]) {
                        colAdd[j] += x;
                        rowAdd[matchCol[j]] -= x;
                    } else {
                        minVal[j] -= x;
                    }
                }
                rowAdd[i] -= x;
                if (matchCol[minCol] == -1) {
                    // solve conflicts
                    Long curRow = minPos[minCol];
                    Long oldMatch = matchRow[curRow];
                    matchCol[minCol] = curRow;
                    matchRow[curRow] = minCol;

                    while (curRow != i) {
                        curRow = parent[curRow];
                        Long assigned = oldMatch;
                        oldMatch = matchRow[curRow];
                        matchCol[assigned] = curRow;
                        matchRow[curRow] = assigned;
                    }
                    break;
                } else {
                    forbidden[minCol] = true;
                    cur = matchCol[minCol];       // transition
                    parent[cur] = minPos[minCol]; // create conflict
                }
            }
        }

        Long ans = 0;
        for (Long i = 0; i < n; i++) {
            Long j = matchRow[i];
            if (j != -1 && A[i][j] < dummy / 2) {
                ans += A[i][j];
            }
        }
        return ans;
    }
} hg;

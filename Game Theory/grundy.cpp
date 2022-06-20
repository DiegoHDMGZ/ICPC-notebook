#include <bits/stdc++.h>
using namespace std;

using Long = long long;

// In any impartial game , let define an state "v" in the game that can reach other states "vi"
// this is equivalent to the game of Nim with one pile of size mex(set of vi)
// this number is call grundy

// A position is a winner position iff grundy(pos) > 0

// For sum of games : grundy(A + B) = grundy(A) xor grundy(B)

/*Long mex(set<Long> &s){
        Long ans = 0;
        for(Long x : s){
                if(ans != x){
                        return ans;
                }
                ans++;
        }
        return ans;
}*/

Long mex(vector<Long> &s) {
    Long n = s.size();
    vector<bool> marked(n, false);
    for (Long x : s) {
        if (x < n) marked[x] = true;
    }
    for (Long x = 0; x < n; x++) {
        if (!marked[x]) return x;
    }
    return n;
}

Long grundy(Long n) {
    // dp
    vector<Long> s;
    for (all transitions) {
        Long g = 0;
        for (all splitted games) {
            g = g xor grundy(game);
        }
        s.push_back(g);
    }
    return mex(s);
}

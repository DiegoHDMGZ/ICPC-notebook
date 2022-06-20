#include <bits/stdc++.h>
using namespace std;

using Long = long long;

vector<Long> parse(string &s) {
    Long tokens;
    stringstream in(s);
    vector<Long> out;
    while (in >> tokens) {
        out.push_back(tokens);
    }
    return out;
}
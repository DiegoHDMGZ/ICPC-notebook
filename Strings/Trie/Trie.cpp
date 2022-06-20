#include <bits/stdc++.h>
using namespace std;
using Long = long long;

const int MX = 1e5;  // sum of length of all words + 1
const int ALPH = 26; // alphabet size

struct Trie {
    int to[MX][ALPH];
    bool terminal[MX];
    int nodes = 1;

    void clear() {
        for (int i = 0; i < nodes; i++) {
            terminal[i] = 0;
            for (int j = 0; j < ALPH; j++) {
                to[i][j] = 0;
            }
        }
        nodes = 1;
    }

    void addWord(string &s) { // O(|s|)
        int n = s.size();
        int u = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (to[u][c] == 0) to[u][c] = nodes++;
            u = to[u][c];
        }
        terminal[u] = true;
    }

    int feed(string &s) { // O(|s|)
        int n = s.size();
        int u = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (to[u][c] == 0) return -1;
            u = to[u][c];
        }
        return u;
    }
    bool isPrefix(string &s) { // O(|s|)
        return feed(s) != -1;
    }

    bool isWord(string &s) { // O(|s|)
        int u = feed(s);
        return u != -1 && terminal[u];
    }
} trie;

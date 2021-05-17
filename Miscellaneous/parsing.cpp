#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

vector<Long> parse(string &s) {
	Long tokens;  
	stringstream in(s);
	vector<Long> out;
	while (in >> tokens) {
		out.push_back(tokens);
	}
	return out;
}

int main() {
	return 0;
}

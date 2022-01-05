#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

Long segmentUnion(const vector<pair<Long, Long>> &a){ //O(nlogn)
	Long n = a.size();
	vector<pair<Long, bool>> endpoint(n * 2);
	REP (i , n) {
		endpoint[2 * i] = make_pair(a[i].first , false);
		endpoint[2 * i + 1] = make_pair(a[i].second , true);
	}
	sort(endpoint.begin(),endpoint.end());
	Long result = 0;
	Long c = 0;
	REP (i , 2 * n) {
		if (c > 0) result += (endpoint[i].first - endpoint[i - 1].first);
		if(endpoint[i].second) c--;
		else c++;
	}
	return result;
}

int main() {

	return 0;
}



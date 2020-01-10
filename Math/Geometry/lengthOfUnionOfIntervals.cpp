#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

typedef long long Long;

struct Segment{
	Long left,right;
};

Long segmentUnion(const vector<pair <Long,Long> > &a){ //O(nlogn)
	Long n = a.size();
	
	vector< pair< Long, bool > > x(n * 2);
	
	REP (i , n) {
		x[2 * i] = make_pair(a[i].first , false);
		x[2 * i + 1] = make_pair(a[i].second , true);
	}
	
	sort(x.begin(),x.end());
	
	Long result = 0;
	Long c = 0;
	
	REP (i , 2 * n) {
		if(c > 0){
			result += (x[i].first - x[i - 1].first);
		}
		
		if(x[i].second) c--;
		else c++;
	}

	return result;
}

int main() {

	return 0;
}



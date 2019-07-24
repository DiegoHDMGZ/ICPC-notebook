#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;

typedef tree<Long, null_type, less<Long> , rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set s;
//find_by_order(k) -> return iterator to the k-th largest element (0-indexed)
//order_of_key(num) -> # of items strictly smaller than num 
int main() {
	
	s.insert(15);
	s.insert(7);
	s.insert(-5);
	s.insert(6);
	s.insert(0);
	
	debug(*s.find_by_order(0));
	debug(*s.find_by_order(3));
	
	debug(s.order_of_key(5));
	
	debug(*s.lower_bound(6));
	debug(*s.lower_bound(7));
	
	return 0;
}




#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;

typedef tree<Long, null_type, less_equal<Long> , rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set s;
//find_by_order(k) -> return iterator to the k-th element (0-indexed) - O(log n)
//order_of_key(num) -> # of items strictly smaller than num - O(log n)

//using less_equal cause that lower_bound works as upper_bound and viceversa
//also you can only erase by iterator now
int main() {
	
	s.insert(15);
	s.insert(7);
	s.insert(5);
	s.insert(5);
	s.insert(6);
	s.insert(-3);
	//s.erase(5);
	cout << "s = " ;
	for(Long x : s){
		cout << x << " ";
	}
	cout << endl;
	
	for(Long i= 0 ;i < s.size(); i++){
		debug(*s.find_by_order(i));
	}
	cout << endl;
	debug(s.order_of_key(6));
	debug(s.order_of_key(5));
	debug(*s.upper_bound(4));
	debug(*s.upper_bound(5));
	
	return 0;
}




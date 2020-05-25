#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
#define REP(i,n) for(Long i = 0; i < (Long)n; i++)
#define pb push_back
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;

typedef tree<Long, null_type, less<Long> , rb_tree_tag, tree_order_statistics_node_update> ordered_set;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	ordered_set s;
	Long Q;
	cin >> Q;
	REP(q, Q){
		char op;
		cin >> op;
		if(op == 'I'){
			Long x;
			cin >> x;
			s.insert(x);
		} else if(op == 'D'){
			Long x;
			cin >> x;
			s.erase(x);
		} else if(op == 'K'){
			Long k;
			cin >> k;
			
			if(k > s.size()){
				cout << "invalid\n";
			} else{
			   k--;
				cout << *s.find_by_order(k) << "\n";
			}
		} else{
			Long x;
			cin >> x;
			cout << s.order_of_key(x) << "\n";
		}
	}
	return 0;
}

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;
typedef tree<Long, null_type, less_equal<Long>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set;

ordered_set s;
// find_by_order(k) -> return iterator to the k-th element (0-indexed) - O(log n)
// order_of_key(num) -> # of items strictly smaller than num - O(log n)

// using less_equal cause that lower_bound works as upper_bound and viceversa
// also .find() does not work and you can only erase by iterator now
// using for example erase(upper_bound(x))

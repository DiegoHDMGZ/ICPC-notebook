#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long Long;
typedef tree<Long, null_type, less<Long>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set;

ordered_set s;
// find_by_order(k) -> return iterator to the k-th element (0-indexed) - O(log n)
// order_of_key(num) -> # of items strictly smaller than num - O(log n)

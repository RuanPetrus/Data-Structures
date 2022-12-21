# Set
```c++
set<int> set1;

set1.insert(1);       // O(log(n))
set1.erase(1);        // O(log(n))

set1.upper_bound(1);  // O(log(n))
set1.lower_bound(1);  // O(log(n))
set1.find(1);         // O(log(n))
set1.count(1);        // O(log(n))

set1.size();          // O(1)
set1.empty();         // O(1)

set1.clear()          // O(1)
```

# Multiset
Same as set but you can have multiple elements with same values
```c++
multiset<int> set1;
```

# Ordered Set
Set but you can look witch elements is in position (k)
```c++
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

int32_t main(){
    o_set.insert(5);
    o_set.insert(1);
    o_set.insert(2);
    // o_set = {1, 2, 5}
    5 == *(o_set.find_by_order(2));
    2 == o_set.order_of_key(4); // {1, 2}
}
```

# Note of `Sort`

1. `Insert sort` => Actually the upgrade of bubble sort (may not run through all the array)

2. `Merge sort` => 2 functions, one is merge_sort, the other is merge. The former was used for recursion, the latter was the key, it contains the `two finger algorithm`

3. `Two finger algorithm` => two `sorted` array must can be `merged into one sorted one`, place two pointers to each array, check which pointed value is bigger/smaller, `choose the right one` (to push) and `move` the correct pointer to the next position, and remain the other one. When two pointers `have equally moved through their own array`, the algorithm is over.

// Pseudo code for binary search template
// Given range [l, r), return index of the element that satisfy f(m), or return the index of first element that satisfy g(m)
// For lower_bound(), g(m) ==> array[m]>=target
// For upper_bound(), g(m) ==> array[m]>target
int binary_search(int l, int r, func f, func g)
{
    while(l < r) {
        int m = l + (r-l)/2;  // this is better than (l+2)/2 so as to avoid integer overflow
        if(f(m))  // optional, when we need to find exact match
            return m;
        if(g(m))  // first element that satisfy g(m) is on the left, or at m (if nothing is found on the left, eventually the l index points to current m when exits the while loop)
            r = m;
        else
            l = m+1;
    }

    return l;  // index of first element that satisfy g(m), or r if no such element exists
}



// possible [l,r] range template 1
while(l < r) {
    int m = l + (r-l)/2;
    if(some condition)
        r = m;   // this will not cause infinit loop, since loop ends when l==r
    else
        l = m + 1;
}

// possible [l,4] range template 2
while(l <= r) {
    int m = l + (r-l)/2;
    if(some condition)
        r = m-1;
    else
        r = m+1;
}

/*
Nearly everyone has used the Multiplication Table. The multiplication table of size m x n is an integer matrix mat where mat[i][j] == i * j (1-indexed).

Given three integers m, n, and k, return the kth smallest element in the m x n multiplication table.

 

Example 1:


Input: m = 3, n = 3, k = 5
Output: 3
Explanation: The 5th smallest number is 3.
Example 2:


Input: m = 2, n = 3, k = 6
Output: 6
Explanation: The 6th smallest number is 6.
 

Constraints:

1 <= m, n <= 3 * 10^4
1 <= k <= m * n
*/

// binar search: find first number that the matrix has K numbers smaller or equal to it
// time complexity: O(min(M,N)*lg(MN))
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int l = 1;
        int r = m*n+1;
        while(l < r) {
            int mid = l + (r-l)/2;
            if(countSmallerOrEqual(m, n, mid) >= k)
                r = mid;
            else
                l = mid + 1;
        }
        
        return l;
    }
    
private:
    // count number of matrix elements that is smaller or equal to val
    // O(min(M,N)) time complexity
    int countSmallerOrEqual(int m, int n, int val) {
        int count = 0;
        if(m > n)
            swap(m,n);
        for(int i=1; i<=m; ++i) {
            int idx = val/i;
            if(idx == 0)  // since i monotonically increase, we no longer need to proceed further
                break;
            count += min(n, val/i);

            // another potential pruning: if count is already >=k, we can exit early also
        }
        return count;
    }
};

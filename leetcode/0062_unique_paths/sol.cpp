/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

 

Example 1:


Input: m = 3, n = 7
Output: 28
Example 2:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
Example 3:

Input: m = 7, n = 3
Output: 28
Example 4:

Input: m = 3, n = 3
Output: 6
 

Constraints:

1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 10^9.
*/

// Solution 1: DP
class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[i][j]: # ways to reach grid (i,j)
        // dp[i][j] == dp[i][j-1] + dp[i-1][j]
        vector<int> dp(n, 1);  // the i-dimension can be reduced
        for(int i=1; i<m; ++i) {
            for(int j=1; j<n; ++j) {
                dp[j] = dp[j-1] + dp[j];
            }
        }
        
        return dp[n-1];
    }
};

// Solution 2: math
/*
The problem is a classical combinatorial problem: there are h+v moves to do from start to finish, h=m−1 horizontal moves, and v=n−1 vertical ones. One could choose when to move to the right, i.e. to define h horizontal moves, and that will fix vertical ones. Or, one could choose when to move down, i.e. to define v vertical moves, and that will fix horizontal ones.

Answer = C(h+v,h) = C(h+v,v)
*/
// However, below does not pass becuase truncation issue
class Solution {
public:
    int uniquePaths(int m, int n) {
        // Math solution: totoal move is m+n-2, and among them choose either m-1 vertical
        // or n-1 horizental moves. One such choise is a given unique path.
        // Answer = C(m+n-2, m-1) = C(m+n-2, n-1)
        
        double M = m + n -2;
        double N = n - 1;
        // compute C(M,N) = M*(M-1)*...*(M-N+1)/N!
        double ans = 1;
        for(int i=1; i<=N; ++i)
            ans *= (M-N+i)/i;
        return ans;

    }
};

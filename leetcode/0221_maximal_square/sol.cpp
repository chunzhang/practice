/*
  Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

  For example, given the following matrix:

  1 0 1 0 0
  1 0 1 1 1
  1 1 1 1 1
  1 0 0 1 0
  Return 4.
*/

// DP solution using two 1-D arrays
class Solution {
public:
    // Define dp(i,j) as the side edge length of max square with (i,j) being the bottom-right corner
    // -- dp(i,j) = min(dp(i-1,j), dp(i-1,j-1), dp(i,j-1)) + 1
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = m ? matrix[0].size() : 0;
        int ans = 0;
        // According to the dependency, only 1-D array is needed
        // In addition, we have dp[0]=0 as the dummy boundary
        vector<int> dp(n+1, 0);
        vector<int> dpNext = dp;
        for(int i=1; i<=m; ++i) {
            for(int j=1; j<=n; ++j) {
                if(matrix[i-1][j-1] == '0') {
                    dpNext[j] = 0;
                }
                else {
                    dpNext[j] = min(min(dp[j-1], dp[j]), dpNext[j-1]) + 1;
                    ans = max(ans, dpNext[j]);
                }
            }
            dp.swap(dpNext);
        }
        
        return ans*ans;
    }
};

// DP solution using only one 1-D array
class Solution {
public:
    // Define dp(i,j) as the side edge length of max square with (i,j) being the bottom-right corner
    // -- dp(i,j) = min(dp(i-1,j), dp(i-1,j-1), dp(i,j-1)) + 1
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = m ? matrix[0].size() : 0;
        int ans = 0;
        // According to the dependency, only 1-D array is needed
        // In addition, we have dp[0]=0 as the dummy boundary
        vector<int> dp(n+1, 0);
        int prev = 0;  // keep dp(i-1,j-1)
        for(int i=1; i<=m; ++i) {
            for(int j=1; j<=n; ++j) {
                int temp = dp[j];
                if(matrix[i-1][j-1] == '0') {
                    dp[j] = 0;
                }
                else {
                    dp[j] = min(min(dp[j-1], dp[j]), prev) + 1;
                    ans = max(ans, dp[j]);
                }
                prev = temp;
            }
        }
        
        return ans*ans;
    }
};


// Reference code using temp var to save most space (in Java)
public class Solution {
    public int maximalSquare(char[][] matrix) {
        int rows = matrix.length, cols = rows > 0 ? matrix[0].length : 0;
        int[] dp = new int[cols + 1];
        int maxsqlen = 0, prev = 0;
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                int temp = dp[j];
                if (matrix[i - 1][j - 1] == '1') {
                    dp[j] = Math.min(Math.min(dp[j - 1], prev), dp[j]) + 1;
                    maxsqlen = Math.max(maxsqlen, dp[j]);
                } else {
                    dp[j] = 0;
                }
                prev = temp;
            }
        }
        return maxsqlen * maxsqlen;
    }
}

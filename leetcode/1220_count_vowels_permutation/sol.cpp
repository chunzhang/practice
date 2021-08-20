/*
Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
Example 2:

Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
Example 3: 

Input: n = 5
Output: 68
 

Constraints:

1 <= n <= 2 * 10^4
*/

// DP O(N) time complexity, O(1) space complexity
class Solution {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9+7;
        vector<vector<int>> rules = {{1}/*'a' can only be followed by 'e'*/,{0,2},{0,1,3,4},{2,4},{0}};
        // dp(n, i): number of strings that ends with vowel i
        int dp[5] = {1,1,1,1,1};  // dp[0]-->'a', dp[1]-->'e', ...
        while(--n) {
            int dpn[5] = {0,0,0,0,0};
            // push style
            for(int from=0; from<rules.size(); ++from) {
                for(int to : rules[from]) {
                    dpn[to] = (dpn[to] + dp[from]) % MOD;
                }
            }
            swap(dp, dpn);
        }
        
        int ans = 0;
        for(int num : dp)
            ans = (ans + num) % MOD;
        return ans;
    }
};


// O(lgN) algorithm based on matrix multiplication
class Solution {
public:
    int countVowelPermutation(int n) {
        // transition matrix
        // using first row as an exmpple, it means 'e', 'i', 'u' can be followed by 'a'
        const MATRIX M = {{0,1,1,0,1}/*transition to 'a'*/, 
                          {1,0,1,0,0}/*transition to 'e'*/, 
                          {0,1,0,1,0}/*transition to 'i'*/, 
                          {0,0,1,0,0}/*transition to 'o'*/, 
                          {0,0,1,1,0}/*transition to 'u'*/};
        MATRIX ans = {{1}, {1}, {1}, {1}, {1}};  // starting point when n==1, i.e., first row is the number of strings that end with 'a'
        // length-n string needs (n-1) transitions, so it is just to compute power(M, n-1)*ans
        MATRIX base = M;
        --n;
        while(n) {  // leetcode-50: pow(x,n), O(lgN) time complexity
            if(n & 0x1)
                ans = matrixMultiply(base, ans);
            base = matrixMultiply(base, base);
            n /= 2;
        }
        
        return (ans[0][0]+ans[1][0]+ans[2][0]+ans[3][0]+ans[4][0]) % MOD;
        
    }

private:
    typedef vector<vector<long>> MATRIX;
    const int MOD = 1e9 + 7;
    MATRIX matrixMultiply(const MATRIX &a/*MxN matrix*/, const MATRIX &b/*NxP matrix*/) {
        const int M = a.size();
        const int N = a[0].size();
        const int P = b[0].size();
        MATRIX res(M, vector<long>(P, 0));
        for(int i=0; i<M; ++i)
            for(int j=0; j<P; ++j) {
                for(int k=0; k<N; ++k)
                    res[i][j] += a[i][k]*b[k][j];
                res[i][j] %= MOD;
            }
        return res;
    }
};

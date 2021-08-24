/*
A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times. 

Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls.

Two sequences are considered different if at least one element differs from each other. Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: n = 2, rollMax = [1,1,2,2,2,3]
Output: 34
Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.
Example 2:

Input: n = 2, rollMax = [1,1,1,1,1,1]
Output: 30
Example 3:

Input: n = 3, rollMax = [1,1,1,2,2,3]
Output: 181
 

Constraints:

1 <= n <= 5000
rollMax.length == 6
1 <= rollMax[i] <= 15
*/

// DP O(6*6*15*N) time complexity
class Solution {
public:
    int dieSimulator(int N, vector<int>& rollMax) {
        // dp(num,count,n): number of distinct sequences of n rolls that ends up in consecutive count number of num
        const int MOD = 1e9+7;
        vector<vector<int>> dp(7, vector<int>(16,0));  // reduce the n dimension
        for(int i=1; i<=6; ++i) {  // base case of n==1
            dp[i][1] = 1;
        }
                
        // bottom-up DP
        for(int n=2; n<=N; ++n) {  // O(N)
            vector<vector<int>> dpn(7, vector<int>(16,0));
            for(int num=1; num<=6; ++num) {
                for(int count=1; count<=15; ++count) {
                    int times = dp[num][count];
                    for(int next=1; next<=6; ++next) {  // PUSH
                        if(num != next) {
                            dpn[next][1] = (dpn[next][1]+times)%MOD;
                        }
                        else if(count<rollMax[num-1]) {
                            dpn[next][count+1] = (dpn[next][count+1]+times)%MOD;
                        }
                    }
                }
            }
            dp.swap(dpn);
        }
        
        int ans = 0;
        for(int num=1; num<=6; ++num)
            for(int count=1; count<=15; ++count)
                ans = (ans+dp[num][count])%MOD;
        return ans;
            
    }
};


// A very smart O(6*N) time complexity solution from HuaHua
class Solution {
public:
    int dieSimulator(int N, vector<int>& rollMax) {
        const int MOD = 1e9+7;
        // dp(i,n): after n rolls, number of sequences that ends with number i
        // idea is to first over calculate all possibility (over counting), and then remove invalid ones
        vector<vector<unsigned>> dp(7, vector<unsigned>(N+1, 0));
        vector<unsigned> sum(N+1, 0);
        for(int i=1; i<=6; ++i) {  // first roll as base case
            dp[i][1] = 1;
            sum[1] += 1;
        }
        
        for(int n=2; n<=N; ++n) {
            for(int i=1; i<=6; ++i) {
                dp[i][n] = sum[n-1];   // first, always over-counting which may include invalid scenarios
                int k = n - rollMax[i-1];
                unsigned invalid = 0;
                if(k == 1)
                    invalid = 1;  // when k==1, there's only one possible way to lead to future invalid scenarios
                else if(k > 1)
                    invalid = sum[k-1] - dp[i][k-1];  // dp[i][k-1] leads to valid since it guarantees the (n-1)-th roll number IS NOT i
                dp[i][n] = (dp[i][n]+MOD-invalid)%MOD;  // we always add MOD to make sure it is a positive number after removing invalid 
                sum[n] = (sum[n]+dp[i][n])%MOD;
            }
        }
        
        return sum[N];
    }
};

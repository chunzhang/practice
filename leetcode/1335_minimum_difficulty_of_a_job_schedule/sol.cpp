/*
You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.

Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

 

Example 1:


Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7 
Example 2:

Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
Example 3:

Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.
Example 4:

Input: jobDifficulty = [7,1,7,1,7,1], d = 3
Output: 15
Example 5:

Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
Output: 843
 

Constraints:

1 <= jobDifficulty.length <= 300
0 <= jobDifficulty[i] <= 1000
1 <= d <= 10
*/

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        // partition the array into d sub-arrays, we want to get the min sum of max val of each partition
        // dp(i,p): answer in array [0:i) with p partitions
        // dp(i,p) = min{dp(k,p-1)+rollingMax}, for d-1<=k<i
        const int N = jobDifficulty.size();
        vector<vector<int>> dp(N+1, vector<int>(d+1, INT_MAX/2));  // denote INT_MAX/2 as invalid value to avoid overflow
        dp[0][0] = 0;
        for(int i=1; i<=N; ++i) {
            for(int p=1; p<=d; ++p) {
                int maxVal = INT_MIN;  // running max
                for(int len=1; len<=i; ++len) {
                    maxVal = max(maxVal, jobDifficulty[i-len]);
                    dp[i][p] = min(dp[i][p], dp[i-len][p-1]+maxVal);
                }
            }
        }
        
        return (dp[N][d]>=INT_MAX/2 ? -1 : dp[N][d]);
    }
};


// HuaHua's solution using PUSH, which saves one loop of computing running max
class Solution {
public:
  int minDifficulty(vector<int>& jobs, int d) {
    const int n = jobs.size();
    if (d > n) return -1;    
    vector<vector<int>> dp(n + 1, vector<int>(d + 1, INT_MAX / 2));
    
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i)      
      for (int j = i - 1, md = 0; j >= 0; --j) {
        md = max(md, jobs[j]);
        for (int k = 1; k <= min(i, d); ++k)                    
          dp[i][k] = min(dp[i][k], dp[j][k - 1] + md);
      }
    
    return dp[n][d];
  }
};

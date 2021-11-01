/*
We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

 

Example 1:



Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job. 
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
Example 2:



Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job. 
Profit obtained 150 = 20 + 70 + 60.
Example 3:



Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6
 

Constraints:

1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
1 <= startTime[i] < endTime[i] <= 10^9
1 <= profit[i] <= 10^4
*/

// DP with std::lower_bound
// time complexity: O(NlgN)
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        // sort the interval by (start, end) time, then use DP
        // dp(i): max profit from (sorted) job[i:], and dp(i) is the max of
        // -- dp(i+1), i.e., when i is not taken
        // -- p(i)+dp(lower_bound(e(i))), when i is taken; s(i), e(i), p(i) is the start/end/profit of i-th job

        // sort job by start time
        const int N = startTime.size();
        vector<vector<int>> jobs(N, vector<int>(3));
        for(int i=0; i<N; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        
        // NO NEED to write my own comparator -- use default comparator for vector<int> is same
        /*
        auto comp = [](const vector<int> &job1, const vector<int> &job2) {
            if(job1[0] != job2[0])
                return job1[0] < job2[0];  // sort by start time
            else
                return job1[1] < job2[1];  // tie break by end time
        };
        */
        sort(jobs.begin(), jobs.end());
        
        // DP
        jobs.push_back({INT_MAX,INT_MAX,0});  // sentinel
        vector<int> dp(N+1, 0);
        for(int i=N-1; i>=0; --i) {
            int skipJob = dp[i+1];
            vector<int> target = {jobs[i][1],jobs[i][1],0};  // next valid job must >= target
            int takeJob = jobs[i][2] + dp[distance(jobs.begin(), lower_bound(jobs.begin()+i, jobs.end(), target))];
            dp[i] = max(skipJob, takeJob);
        }
        
        return dp[0];
    }
};


// DP with my own version of binary search
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        // sort the interval by (start, end) time, then use DP
        // dp(i): max profit from (sorted) job[i:], and dp(i) is the max of
        // -- dp(i+1), i.e., when i is not taken
        // -- p(i)+dp(lower_bound(e(i))), when i is taken; s(i), e(i), p(i) is the start/end/profit of i-th job

        // sort job by start time
        const int N = startTime.size();
        vector<vector<int>> jobs(N, vector<int>(3));
        for(int i=0; i<N; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        sort(jobs.begin(), jobs.end());
        
        // DP
        vector<int> dp(N, 0);
        for(int i=N-1; i>=0; --i) {
            // binary search to find first job with start time >= current job end time
            int l = i;
            int r = N;
            while(l < r) {
                int mid = l + (r-l)/2;
                if(jobs[mid][0] >= jobs[i][1])
                    r = mid;
                else
                    l = mid + 1;
            }
            int takeJob = jobs[i][2] + (l<N?dp[l]:0);
            int skipJob = i<N-1?dp[i+1]:0;
            dp[i] = max(skipJob, takeJob);
        }
        
        return dp[0];
    }
};

/*
You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose any two stones and smash them together. Suppose the stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the smallest possible weight of the left stone. If there are no stones left, return 0.

 

Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation:
We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0, so the array converts to [1], then that's the optimal value.
Example 2:

Input: stones = [31,26,33,21,40]
Output: 5
Example 3:

Input: stones = [1,2]
Output: 1
 

Constraints:

1 <= stones.length <= 30
1 <= stones[i] <= 100
*/

// DP: similar to 0494--Target Sum problem
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // Divide stones into two non-overlapping subset, i.e., P and Q;
        // ==> the min last sone left is min(abs(sum(P)-sum(Q))), for all possible P and Q
        // ==> this can be thought as assigning + and - to each of the stone, and then DP computing all possible sum
        // dp(i,n): whether stones[0:1) can add up to n with +/- assignment
        // ==> final answer is min(abs(n)) for all dp(i,n)==True
        unordered_set<int> dp;  // reduce deminsion i, and user hash-table since I expect the possible to be sparse
        dp.insert(0);
        for(int stone : stones) {
            unordered_set<int> dpn;  // next i
            for(int sum : dp) {  // use push-style
                dpn.insert(sum+stone);
                dpn.insert(sum-stone);
            }
            dp.swap(dpn);
        }
        
        int ans = INT_MAX;
        for(int sum : dp)
            ans = min(ans, abs(sum));
        return ans;
    }
};


// Another DP solution: similar to 0416--Partition Equal Subset Sum problem
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // Divide stones into two non-overlapping subset, i.e., P and Q;
        // ==> the min last sone left is min(abs(sum(P)-sum(Q))), for all possible P and Q
        // Define P to be the larger subset, i.e., sum(P)>=sum(Q)
        // ==> sum(P)-sum(Q) = total_sum-2*sum(Q)
        // ==> min(sum(P)-sum(Q)) = total_sum-max(sum(Q)), where sum(Q)<=total_sum/2, since it is defined as the smaller part
        // ==> we can convert it to a 0/1 knapsack problem, i.e., from all stones, find the sub-set Q that has max sum<=totoal_sum/2
        // dp[i][n]: True if there's subset of stones[0:i] that add up to n
        int total_sum = accumulate(stones.begin(), stones.end(), 0);
        int half_sum = total_sum/2;  // sum(Q) must be <=limit because it's defined as the smaller sub-set
        unordered_set<int> dp;
        dp.insert(0);
        for(int stone : stones) {
            unordered_set<int> dpn = dp;  // must copy since the stone may not get selected
            for(int sum : dp) {
                int next_sum = sum + stone;  // push style
                if(next_sum <= half_sum)
                    dpn.insert(next_sum);
            }
            dp.swap(dpn);
        }
        
        int sum_q = INT_MIN;
        for(int sum : dp)
            sum_q = max(sum_q, sum);
        return total_sum - 2*sum_q;
    }
};

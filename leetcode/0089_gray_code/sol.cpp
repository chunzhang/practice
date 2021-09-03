/*
An n-bit gray code sequence is a sequence of 2n integers where:

Every integer is in the inclusive range [0, 2n - 1],
The first integer is 0,
An integer appears no more than once in the sequence,
The binary representation of every pair of adjacent integers differs by exactly one bit, and
The binary representation of the first and last integers differs by exactly one bit.
Given an integer n, return any valid n-bit gray code sequence.

 

Example 1:

Input: n = 2
Output: [0,1,3,2]
Explanation:
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
[0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
- 00 and 10 differ by one bit
- 10 and 11 differ by one bit
- 11 and 01 differ by one bit
- 01 and 00 differ by one bit
Example 2:

Input: n = 1
Output: [0,1]
 

Constraints:

1 <= n <= 16
*/

// DFS O(N*2^N) time complexity
// recursive depth is 2^N, and at each recursion, need O(N) to flip each bit
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        vector<int> used(1<<n, 0);
        used[0] = 1;
        res.push_back(0);
        dfs(used, n, 1/*nUsed*/, 0/*prev num*/, res);
        return res;
    }
    
private:
    bool dfs(vector<int> &used, const int n, int nUsed, int prev, vector<int> &res) {
        if(nUsed == 1<<n) {
            // determine whether last number differs from 0 by only one bit
            int ones = 0;
            for(int i=0; i<n; ++i)
                if((prev>>i)&0x1)
                    ++ones;
            return ones==1;
        }
        
        for(int i=0; i<n; ++i) {  // try flip one bit as the next candidate number
            int next = prev ^ (0x1<<i);
            if(used[next])
                continue;
            used[next] = 1;
            res.push_back(next);
            if(dfs(used, n, nUsed+1, next, res))
                return true;
            used[next] = 0;
            res.pop_back();
        }
        
        return false;
    }
};


// DP bottom up
class Solution {
public:
    vector<int> grayCode(int n) {
        // Bottom-up DP: dp(n) is the gray code for n-bit binary, so we can build dp(n) from dp(n-1) in this way
        // -- First half, add MSB 0 to all codes in dp(n-1), i.e., essentially copy of dp(n-1)
        // ---- [0,1] ==> [00, 01]
        // -- Second half, reverse dp(n-1), and att MSB 1
        // ---- [0,1] ==> [1,0] ==> [11,10]
        // -- So the gray code is first half + second half, i.e., [00,01,11,10]
        
        // since dp(n) only depends on dp(n-1), we can reduce space needed
        vector<int> dp(1,0);  // dp(0)
        for(int i=1; i<=n; ++i) {
            vector<int> dp2 = dp;  // first half
            dp2.resize(dp.size()*2);
            int msb = 0x1<<(i-1);  // msb of second half
            for(int j=dp.size(), k=dp.size()-1; j<dp2.size(); ++j, --k) {  // second half
                dp2[j] = msb | (dp[k]) /*in reverse order*/;
            }
            dp.swap(dp2);
        }
        
        return dp;
    }
};


// DP bottom up, with smart in-place upate
class Solution {
public:
    vector<int> grayCode(int n) {
        // Bottom-up DP: dp(n) is the gray code for n-bit binary, so we can build dp(n) from dp(n-1) in this way
        // -- First half, add MSB 0 to all codes in dp(n-1), i.e., essentially copy of dp(n-1)
        // ---- [0,1] ==> [00, 01]
        // -- Second half, reverse dp(n-1), and att MSB 1
        // ---- [0,1] ==> [1,0] ==> [11,10]
        // -- So the gray code is first half + second half, i.e., [00,01,11,10]
        
        // since dp(n) only depends on dp(n-1), we can reduce space needed;
        // even smarter, we can update the gray code in place
        vector<int> dp(0x1<<n, 0);
        for(int i=1; i<=n; ++i) {
            int msb = 0x1<<(i-1);  // msb of second half
            int start = 0x1<<(i-1);  // starting index of second half
            int end = 0x1<< i;       // end index of second half
            for(int j=start,k=j-1; j<end; ++j,--k)
                dp[j] = msb | dp[k];
        }
        
        return dp;
    }
};

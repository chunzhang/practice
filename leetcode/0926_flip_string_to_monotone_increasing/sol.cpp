/*
A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).

You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.

Return the minimum number of flips to make s monotone increasing.

 

Example 1:

Input: s = "00110"
Output: 1
Explanation: We flip the last digit to get 00111.
Example 2:

Input: s = "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.
Example 3:

Input: s = "00011000"
Output: 2
Explanation: We flip to get 00000000.
 

Constraints:

1 <= s.length <= 105
s[i] is either '0' or '1'.
*/

// O(N) DP bassed on constant states, i.e., whether the mono-increase string ends with 0 or 1
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        // dp0[i]: min flips to make s[0:i] mono-increase and keep i-th bit as 0
        // dp1[i]: min flips to make s[0:i] mono-increase and keep i-th bit as 1
        const int N = s.size();
        vector<int> dp0(N, INT_MAX);
        vector<int> dp1(N, INT_MAX);
        dp0[0] = (s[0]=='0'?0:1);
        dp1[0] = (s[0]=='1'?0:1);
        for(int i=1; i<N; ++i) {
            dp0[i] = dp0[i-1] + (s[i]=='0'?0:1);
            dp1[i] = min(dp0[i-1],dp1[i-1]) + (s[i]=='1'?0:1);
        }
        
        return min(dp0[N-1], dp1[N-1]);
    }
};


// another O(N) DP based on pre-fix sum
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        // any mono-increase string is broken into two halves: first half has all zeros, and second half has all ones
        // as such, we can try all such breakings, and number of ones in first half + number of zeros in second half is the number of flips needed for such breaking
        // use prefix sum to book-keep number of ones in s[i:j)
        const int N = s.size();
        vector<int> csum(N+1, 0);
        for(int i=1; i<=N; ++i) {  // csum[i] is number of ones in s[0:i)
            csum[i] = csum[i-1] + (s[i-1]=='1'?1:0);
        }
        
        // try all breaking points
        int ans = INT_MAX;
        for(int i=0; i<=N; ++i) {  // [0,i) is first half, [i,N) is second half
            int ones = csum[i];  // number of ones in first half
            int zeros = N - i - (csum[N]-csum[i]);  // number of zeros in second half
            ans = min(ans, ones+zeros);
        }
        
        return ans;
    }
};

/*
Alice and Bob continue their games with piles of stones.  There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].  The objective of the game is to end with the most stones. 

Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).

The game continues until all the stones have been taken.

Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.

 

Example 1:

Input: piles = [2,7,9,4,4]
Output: 10
Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get 2 + 4 + 4 = 10 piles in total. If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger. 
Example 2:

Input: piles = [1,2,3,4,5,100]
Output: 104
 

Constraints:

1 <= piles.length <= 100
1 <= piles[i] <= 10^4

*/

// DP with memoization
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        // dp(i,m): max one can take by starting at index i with m opportunities
        // dp(i,m) = max{sum[i:i+k-1]+sum[i+k:]-dp(i+k,max(m,k))} for 1<=k<=2*m
        N = piles.size();
        _mem = vector(N, vector<int>(64, 0));  // since piles.size()<-=100, m cannot go beyond 64
        _csum = piles;
        for(int i=1; i<N; ++i)
            _csum[i] = _csum[i-1] + piles[i];
        
        return dp(piles, 0, 1);
    }
    
private:
    vector<vector<int>> _mem;
    vector<int> _csum;
    int N;
    int dp(const vector<int> &piles, int i, int m) {
        if(i >= N)
            return 0;
        if(_mem[i][m])
            return _mem[i][m];
        if(N-i <= 2*m) {  // pruning: all stones can be taken, which is always optimal
            _mem[i][m] = _csum[N-1] - (i>0?_csum[i-1]:0);
            return _mem[i][m];

        int ans = 0;
        int curGain = 0;
        for(int k=1; k<=2*m&&i+k<=N; ++k) {
            curGain += piles[i+k-1];  // what I can take in current round
            int remaining = _csum[N-1]-_csum[i+k-1]-dp(piles, i+k, max(m,k));  // total remaining stones -  what opponent can take optimally == what I can take in the remaining stones
            ans = max(ans, curGain+remaining);
        }
        
        _mem[i][m] = ans;
        return ans;
    }
};

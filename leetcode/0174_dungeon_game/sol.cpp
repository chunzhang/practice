/*
The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of m x n rooms laid out in a 2D grid. Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Return the knight's minimum initial health so that he can rescue the princess.

Note that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

 

Example 1:


Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
Example 2:

Input: dungeon = [[0]]
Output: 1
 

Constraints:

m == dungeon.length
n == dungeon[i].length
1 <= m, n <= 200
-1000 <= dungeon[i][j] <= 1000
*/

// DP solution with simplified code
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // dp[i][j]: min health needed right before reaching (i,j) for the knight to be able to reach (m-1,n-1);
        // dp[i][j] = min(dp[i][j+1], dp[i+1][j]) - dungeon[i][j];
        // Note dp[i][j] must >= 1, so if dp[i][j] < 1, make it 1
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));  // padding one additional row and column for simplifying code
        dp[m-1][n] = dp[m][n-1] = 1;  // for computing dp[m-1][n-1]
        for(int i=m-1; i>=0; --i) {
            for(int j=n-1; j>=0; --j) {
                dp[i][j] = min(dp[i][j+1], dp[i+1][j]) - dungeon[i][j];
                if(dp[i][j] < 1)
                    dp[i][j] = 1;
            }
        }
        
        return dp[0][0];
    }
};


// DP solution
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // dp[i][j]: min health needed right "before reaching" (i,j) for the knight to be able to reach (m-1,n-1);
        // dp[i][j] = min(dp[i][j+1], dp[i+1][j]) - dungeon[i][j];
        // Note dp[i][j] must >= 1;; so if dp[i][j] < 1, make it 1
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 1));
        dp[m-1][n-1] = (dungeon[m-1][n-1]>=0 ? 1 : 1-dungeon[m-1][n-1]);  // initialize bottom-right grid's cost
        for(int i=m-1; i>=0; --i) {
            for(int j=n-1; j>=0; --j) {
                if(i==m-1 && j==n-1)
                    continue;
                else if(i==m-1)
                    dp[i][j] = dp[i][j+1] - dungeon[i][j];
                else if(j==n-1)
                    dp[i][j] = dp[i+1][j] - dungeon[i][j];
                else
                    dp[i][j] = min(dp[i][j+1], dp[i+1][j]) - dungeon[i][j];
                
                if(dp[i][j] < 1)
                    dp[i][j] = 1;
            }
        }
        
        return dp[0][0];
    }
};

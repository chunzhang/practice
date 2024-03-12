/*
Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:


Example 1:

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
Example 2:

Input: numRows = 1
Output: [[1]]
 

Constraints:

1 <= numRows <= 30
*/


// time: O(N^2)
// space: O(N^2)
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);
        for(int r=0; r<numRows; ++r) {
            res[r].resize(r+1, 1);
            for(int i=1; i<res[r].size()-1; ++i)
                res[r][i] = res[r-1][i-1] + res[r-1][i];
        }

        return res;
    }
};

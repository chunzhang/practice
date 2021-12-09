/*
A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.

Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].

You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.

You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.

 

Example 1:



Input: mat = [[1,4],[3,2]]
Output: [0,1]
Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.
Example 2:



Input: mat = [[10,20,15],[21,30,14],[7,16,32]]
Output: [1,1]
Explanation: Both 30 and 32 are peak elements so [1,1] and [2,2] are both acceptable answers.
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 500
1 <= mat[i][j] <= 10^5
No two adjacent cells are equal.
*/


// binary search -- use HuaHua template
// find first column of which the column max is bigger than the right column
// time complexity: O(MlgN)
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        const int M = mat.size();
        const int N = mat[0].size();
        
        // below assume N>M, so we divide by column
        int lo = 0;
        int hi = N;
        int maxi = -1;
        int maxj = -1;
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            
            // find max val among columns mid-1, mid, mid+1
            int maxv = INT_MIN;
            for(int i=0; i<M; ++i) {
                for(int j=(mid>0?mid-1:mid); j<=(mid+1<N?mid+1:mid); ++j) {
                    if(mat[i][j] > maxv) {
                        maxv = mat[i][j];
                        maxi = i;
                        maxj = j;
                    }
                }
            }
            
            if(maxj != mid+1)  // g(m): column_max(mid) > column_max(mid+1)
                hi = mid;
            else
                lo = mid + 1;            
        }
        
        return {maxi, maxj};
    }
    
};


// binary search -- a different impl
// time complexity: O(MlgN)
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        const int M = mat.size();
        const int N = mat[0].size();
        
        // below assume N>M, so we divide by column
        int lo = 0;
        int hi = N - 1;
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            
            // find max val among columns mid-1, mid, mid+1
            int maxv = INT_MIN;
            int maxi = -1;
            int maxj = -1;
            for(int i=0; i<M; ++i) {
                for(int j=(mid>0?mid-1:mid); j<=(mid+1<N?mid+1:mid); ++j) {
                    if(mat[i][j] > maxv) {
                        maxv = mat[i][j];
                        maxi = i;
                        maxj = j;
                    }
                }
            }
            
            if(maxj == mid-1)  // max val on the column left to mid  ==> peak exists on left half
                hi = mid - 1;
            else if(maxj == mid+1)  //  max val on the column right to mid  ==> peak exists on right half
                lo = mid + 1;
            else  // mid column has max val ==> find peak
                return {maxi,maxj};
        }
        
        return {-1,-1};  // should not reach here
    }
    
};

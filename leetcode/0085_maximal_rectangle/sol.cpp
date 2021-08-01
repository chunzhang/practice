/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
 

Example 1:

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:

Input: matrix = []
Output: 0

Example 3:

Input: matrix = [["0"]]
Output: 0

Example 4:

Input: matrix = [["1"]]
Output: 1

Example 5:

Input: matrix = [["0","0"]]
Output: 0
 

Constraints:

rows == matrix.length
cols == matrix[i].length
0 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
*/

// DP solution 1: O(m*n*m)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = (m ? matrix[0].size() : 0);
        if(!m || !n)
            return 0;
        
        // DP solution 1: O(m*n*m)
        // For each (i,j), I compute dp[i][j] as the totoal number of continuous 1's from left
        // -- dp[i][j] = matrix[i][j]==1 ? dp[i][j-1]+1 : 0
        // Then, the max rect area with (i,j) is among all the above rows until matrix[k][j] becomes 0
        int ans = 0;
        vector<vector<int>> dp(m, vector<int>(n,0));
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(matrix[i][j] == '0') {
                    dp[i][j] = 0;
                    continue;
                }
                dp[i][j] = (j==0 ? 1 : dp[i][j-1]+1);
                
                int h = 1;
                int w = dp[i][j];
                ans = max(ans, h*w);
                for(int k=i-1; k>=0&&matrix[k][j]=='1'; --k) {
                    ++h;
                    w = min(w, dp[k][j]);
                    ans = max(ans, h*w);
                }
            }
        }
        
        return ans;
    }
};


// Solution that converts the problem to 0084--Largest rectangle in histogram: O(m*n)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        // In this solution, the idea is to convert it to max-rect area in histogram problem (0084);
        // For each row, everything on and above the row forms a histogram, and the max area must be among all such histograms
        int m = matrix.size();
        int n = (m ? matrix[0].size() : 0);
        if(!m || !n)
            return 0;
        
        int ans = 0;
        vector<int> his(n+1, 0); 
        his[n] = -1;  // pad -1 to the end of the histogram for simplicity of code
        for(int i=0; i<m; ++i) {
            // to form histogram for current row
            for(int j=0; j<n; ++j) {
                his[j] = (matrix[i][j]=='1' ? his[j]+1 : 0);
            }
            ans = max(ans, maxHistogram(his));
        }
        
        return ans;
    }
    
private:
    int maxHistogram(const vector<int> his) {
        // assume his is always padded with -1 in the end for code simplicity
        int ans = 0;
        stack<int> st;  // to keep index of histograms
        st.push(-1);    // pad -1 index for code simplicity
        for(int i=0; i<his.size(); ++i) {
            // keep the stack strictly non-decreasing so we know the first left and right historam that is lower then current top histogram
            while(st.top()!=-1 && his[st.top()]>his[i]) {
                int h = his[st.top()];
                st.pop();
                // since stack is padded with -1 as the first element, it is guaranteed to be non-empty
                int l = st.top();  // first left histogram that is lower than h
                int r = i;         // first right histogram that is lower than h
                ans = max(ans, h*(r-l-1)); // [l+1, r-1] is the width
            }
            st.push(i);
        }
        
        // since his is always padded with -1 in the end, we guarantee all valid histograms are popped out upon reaching this point
        return ans;
    }
};


// DP solution 2: O(m*n)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        // DP solution: O(m*n)
        // For each (i,j), we compute the area of rectangle formed by h(i,j), l(i,j) and r(i,j)
        // -- h(i,j) is the max height from (i,j) and up until reaches an '0'
        // -- l(i,j) is index to left most boundary where we can keep h(i,j)
        // -- r(i,j) is the index to the right most boundary where we can keep h(i,j)
        // -- area(i,j) = h(i,j) * (r(i,j)-l(i,j)+1)
        // -- Answer to the problem is among area(i,j) for all (i,j)
        // We can use DP to populate h, l, and r in O(m*n) time complexity
        // -- h(i,j) = matrix[i][j]==1 ? h(i-1,j)+1 : 0
        // -- l(i,j): 
        //             If matrix[i][j]==0, then reset l(i,j) to -1 so if won't be factored into the computation of next row
        //             If matrix[i][j]==1, then l(i,j)=min(l(i-1,j), current_left), where current_left is left starting index of 1's in current row
        // -- r(i,j): we can compute it in the similar way as l(i,j), i.e., just from the right end
        // We can reduce the i-th dimension to save some space
        
        int m = matrix.size();
        int n = (m ? matrix[0].size() : 0);
        if(!m || !n)
            return 0;
        
        int ans = 0;
        vector<int> h(n, 0);
        vector<int> l(n, 0);
        vector<int> r(n, n-1);  // since this is right boundary, it must be initialized to n-1
        for(int i=0; i<m; ++i) {
            // compute height
            for(int j=0; j<n; ++j) {
                h[j] = (matrix[i][j]=='1' ? h[j]+1 : 0);
            }
            
            // compute left boundary
            int cur_left = 0;  // left starting index of of continuous 1's in current row
            for(int j=0; j<n; ++j) {
                if(matrix[i][j] == '1') {
                    l[j] = max(l[j], cur_left);
                }
                else {
                    l[j] = -1;  // reset so it doesn't affect computation of next row, one can set it to any number <=0
                    cur_left = j+1;  // maybe next right is one
                }
            }
            
            // compute right boundary
            int cur_right = n-1;  // right starting index of of continuous 1's in current row
            for(int j=n-1; j>=0; --j) {
                if(matrix[i][j] == '1') {
                    r[j] = min(r[j], cur_right);
                }
                else {
                    r[j] = n;  // reset so it doesn't affect computation of next row, one can set it to any number >=n-1
                    cur_right = j-1;  // maybe next left is one
                }
            }
            
            // compute area
            for(int j=0; j<n; ++j)
                ans = max(ans, h[j]*(r[j]-l[j]+1));
        }
        
        return ans;
    }
};

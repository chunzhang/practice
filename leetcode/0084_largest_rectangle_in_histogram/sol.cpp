/*
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:

Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:

Input: heights = [2,4]
Output: 4
 
Constraints:

1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4
*/

// Use stack: straightforward but with more lines of code
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // For each histogram h, if we know the first histogram on the left and right that is smaller than h, we can compute the max rect area with h being the highest;
        // -- If we compute such area for every h, the max rect area is among one of them -- this can be done in a brute-force way in O(N^2)
        // -- A smarter idea is to use stack to keep track of monotonically no-decreasing histgorams. Whenever we encouter a histogram that is smaller than current top h, it means we can 
        //    compute the max rect for h, i.e., we know what is h's first left and right histogram that is smaller than h
        // -- Be careful about boundary condidtions such as when the stack is empty
        
        int ans = 0;
        
        stack<int> st;  // to keep index to histograms
        for(int i=0; i<heights.size(); ++i) {
            // find the first histogram on the right that is smaller than current top h
            while(!st.empty() && heights[st.top()]>heights[i]) {
                int h = heights[st.top()];
                st.pop();
                int l = (st.empty() ? -1 : st.top());
                int r = i;
                ans = max(ans, h*(r-l-1));  // [l+1, r-1] is the width of the rectangle held by h
            }
            
            st.push(i);
        }
        
        // process remaining elements in the stack
        while(!st.empty()) {
            int h = heights[st.top()];
            st.pop();
            int l = (st.empty() ? -1 : st.top());
            int r = heights.size();
            ans = max(ans, h*(r-l-1));
        }
        
        return ans;
    }
};


// Use stack: simplified by padding
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // For each histogram h, if we know the first histogram on the left and right that is smaller than h, we can compute the max rect area with h being the highest;
        // -- If we compute such area for every h, the max rect area is among one of them -- this can be done in a brute-force way in O(N^2)
        // -- A smarter idea is to use stack to keep track of monotonically no-decreasing histgorams. Whenever we encouter a histogram that is smaller than current top h, it means we can 
        //    compute the max rect for h, i.e., we know what is h's first left and right histogram that is smaller than h
        // -- Be careful about boundary condidtions such as when the stack is empty
        
        int ans = 0;
        
        stack<int> st;  // to keep index to histograms
        st.push(-1);    // to simplify code
        heights.push_back(-1);  // to simplify code
        for(int i=0; i<heights.size(); ++i) {
            // find the first histogram on the right that is smaller than current top h
            while(st.top()!=-1 && heights[st.top()]>heights[i]) {
                int h = heights[st.top()];
                st.pop();
                ans = max(ans, h*(i-st.top()-1));  // [st.top()+1, i-1] is the width of the rectangle held by h
            }            
            st.push(i);
        }
        
        // since we add -1 to the end of heights, it is guaranteed that all histograms are popped out upon here
        return ans;
    }
};


// Divide and conquer solution -- TLE
// Time complexity can degrade from O(NlgN) to O(N^2) when the histograms are fully sorted
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // -- This time, we try to divide and conquer the problem
        return maxArea(heights, 0, heights.size());
    }
    
private:
    // Divide and conquer to find the max rect area within [l, r);
    // the max area can only be one of the three: rect held by heights[mid], or max rect from [l, mid), or max rect from [mid+1, r)
    int maxArea(const vector<int> &heights, int l, int r) {
        if(l >= r)
            return 0;
        
        // Note that I can only compute the max rect area for min histogram in current [l,r), so choose it as the mid point to divide
        int mid = l;
        for(int i=l+1; i<r; ++i)
            if(heights[i] < heights[mid])
                mid = i;
        
        return max({heights[mid]*(r-l), maxArea(heights, l, mid), maxArea(heights, mid+1,r)});
    }
};

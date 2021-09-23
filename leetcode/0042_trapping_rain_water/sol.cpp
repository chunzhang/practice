/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 

Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5
*/

// DP: the water that can be trapped at i is bounded by the max bar on its left and right
// time complexity: O(N), space complexity: O(N)
class Solution {
public:
    int trap(vector<int>& height) {
        // left[i], right[i]: max bar height in [0,...,i] and [i,...,N-1]
        vector<int> left = height;
        vector<int> right = height;
        for(int i=1; i<height.size(); ++i)
            left[i] = max(left[i-1], height[i]);
        for(int i=height.size()-2; i>=0; --i)
            right[i] = max(right[i+1], height[i]);
        
        int ans = 0;
        for(int i=0; i<height.size(); ++i) {
            ans += min(left[i],right[i]) - height[i];
        }
        
        return ans;
    }
};

// use mono stack -- keep non-increasing order of heights
// time complexity: O(N); space complexity: O(N)
class Solution {
public:
    int trap(vector<int>& height) {
        // use mono-stack: keep non-increasing order
        // whenever a higher height is encountered, we have some additional water to trap
        // we store index in the stack so as to compute width
        int ans = 0;
        stack<int> st;
        for(int j=0; j<height.size(); ++j) {
            // stack cannot be empty
            while(st.size() && height[st.top()] < height[j]) {
                int cur = st.top();
                st.pop();
                if(st.empty())
                    break;
                int i = st.top();
                int bound = min(height[i], height[j]);
                ans += (bound-height[cur])*(j-i-1);
            }
            
            st.push(j);
        }
        
        return ans;
    }
};


// use two pointers
// time complexity: O(N), space complexity: O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int l = 0;
        int r = height.size() - 1;
        int maxLeft = height[l];
        int maxRight = height[r];
        while(l < r) {
            if(maxLeft < maxRight) {  // water trapped at l is bounded by left max height, we don't need to know right max height between (l,r)
                ans += maxLeft - height[l];
                ++l;
                maxLeft = max(maxLeft, height[l]);
            }
            else {  // water traped at r is bounded by right max height
                ans += maxRight - height[r];
                --r;
                maxRight = max(maxRight, height[r]);
            }
        }
        
        return ans;
    }
};
